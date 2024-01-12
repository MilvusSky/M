#include "../FunctionIncludes.h"
#include "../../GUI/mutil.h"
#include "ESP.h"

namespace cheat
{
	static constexpr int _fontSizeStep = 1;
	static constexpr int _fontSizeMax = 64;
	static constexpr int _fontsCount = _fontSizeMax / _fontSizeStep;
	static std::array<ImFont*, _fontsCount> _fonts;

	ImFont* GetFontBySize(float fontSize)
	{
		int fontSizeInt = static_cast<int>(fontSize);
		int fontIndex = fontSizeInt / _fontSizeStep +
			(fontSizeInt % _fontSizeStep > (_fontSizeStep / 2) ? 1 : 0) - 1;
		fontIndex = std::clamp(fontIndex, 0, _fontsCount - 1);
		return _fonts[fontIndex];
	}
	static app::Camera* s_Camera = nullptr;
	static ImVec2 s_ResolutionScale = ImVec2(0, 0);
	static ImVec2 s_ScreenResolution = ImVec2(0, 0);
	static ImVec2 s_AvatarPosition = ImVec2(0, 0);

	float CalcContrastRatio(const ImU32& backgroundColor, const ImU32& foreGroundColor)
	{
		float sa0 = static_cast<float>((backgroundColor >> IM_COL32_A_SHIFT) & 0xFF);
		float sa1 = static_cast<float>((foreGroundColor >> IM_COL32_A_SHIFT) & 0xFF);
		static float sr = 0.2126f / 255.0f;
		static float sg = 0.7152f / 255.0f;
		static float sb = 0.0722f / 255.0f;
		const float contrastRatio =
			(sr * sa0 * ((backgroundColor >> IM_COL32_R_SHIFT) & 0xFF) +
				sg * sa0 * ((backgroundColor >> IM_COL32_G_SHIFT) & 0xFF) +
				sb * sa0 * ((backgroundColor >> IM_COL32_B_SHIFT) & 0xFF) + 0.05f) /
			(sr * sa1 * ((foreGroundColor >> IM_COL32_R_SHIFT) & 0xFF) +
				sg * sa1 * ((foreGroundColor >> IM_COL32_G_SHIFT) & 0xFF) +
				sb * sa1 * ((foreGroundColor >> IM_COL32_B_SHIFT) & 0xFF) + 0.05f);
		if (contrastRatio < 1.0f)
			return 1.0f / contrastRatio;
		return contrastRatio;
	}

	ImColor CalcContrastColor(const ImColor& foreground, float maxContrastRatio, const ImColor& background, const ImColor& inverted)
	{
		return CalcContrastRatio(background, foreground) < maxContrastRatio ? inverted : background;
	}

	static void UpdateMainCamera()
	{
		UPDATE_DELAY(1000);

		s_Camera = nullptr;

		SAFE_BEGIN();
		auto camera = app::Camera_get_main();
		if (camera == nullptr)
			return;

		if (!app::Behaviour_get_isActiveAndEnabled(reinterpret_cast<app::Behaviour*>(camera)))
			return;

		s_Camera = camera;
		SAFE_EEND();
	}

	static void UpdateResolutionScale()
	{
		UPDATE_DELAY(1000);

		SAFE_BEGIN();
		s_ResolutionScale = { 0, 0 };

		if (s_Camera == nullptr)
			return;

		auto pixelWidth = app::Camera_get_pixelWidth(s_Camera);
		auto pixelHeight = app::Camera_get_pixelHeight(s_Camera);

		if (pixelWidth == 0 || pixelHeight == 0)
			return;

		auto screenWidth = app::Screen_get_width(nullptr);
		auto screenHeight = app::Screen_get_height(nullptr);

		if (screenWidth == 0 || screenHeight == 0)
			return;

		if (screenHeight == pixelHeight && screenWidth == pixelWidth)
			return;

		s_ScreenResolution.x = static_cast<float>(screenWidth);
		s_ScreenResolution.y = static_cast<float>(screenHeight);

		s_ResolutionScale.x = s_ScreenResolution.x / static_cast<float>(pixelWidth);
		s_ResolutionScale.y = s_ScreenResolution.y / static_cast<float>(pixelHeight);
		SAFE_EEND();
	}

	static app::Vector3 WorldToScreenPosScalled(const app::Vector3& relPosition)
	{
		if (s_Camera == nullptr)
			return {};

		auto screenPos = app::Camera_WorldToScreenPoint(s_Camera, relPosition);

		if (s_ResolutionScale.x != 0)
		{
			screenPos.x *= s_ResolutionScale.x;
			screenPos.y *= s_ResolutionScale.y;
		}

		screenPos.y = app::Screen_get_height(nullptr) - screenPos.y;
		return screenPos;
	}

	struct Rect
	{
		float xMin, xMax;
		float yMin, yMax;

		bool empty() const
		{
			return xMin == 0 && xMax == 0 && yMin == 0 && yMax == 0;
		}
	};

	struct BoxScreen
	{
		ImVec2 lowerTopLeft;
		ImVec2 lowerTopRight;
		ImVec2 lowerBottomLeft;
		ImVec2 lowerBottomRight;

		ImVec2 upperTopLeft;
		ImVec2 upperTopRight;
		ImVec2 upperBottomLeft;
		ImVec2 upperBottomRight;
	};

#undef min
#undef max

	static ImVec2 FromVec3(const app::Vector3& vec3)
	{
		return { vec3.x, vec3.y };
	}

	static app::Bounds GetEntityMinBounds(game::Entity* entity, float minSize = 0.1)
	{
		auto entityPosition = entity->relativePosition();
		return { entityPosition, { minSize, minSize, minSize } };
	}

	static app::Bounds GetObjectBounds(game::Entity* entity)
	{
		auto& esp = ESP::getInstance();
		auto gameObject = entity->gameObject();
		if (gameObject == nullptr)
			return GetEntityMinBounds(entity);

		SAFE_BEGIN();

		auto bounds = app::GetBounds(gameObject);
		/*if (bounds.m_Extents.x < esp.f_MinSize.getValue() &&
			bounds.m_Extents.y < esp.f_MinSize.getValue() &&
			bounds.m_Extents.z < esp.f_MinSize.getValue())
			bounds.m_Extents = { esp.f_MinSize.getValue(), esp.f_MinSize.getValue(), esp.f_MinSize.getValue() };*/

		auto min = bounds.m_Center - bounds.m_Extents;
		auto max = bounds.m_Center + bounds.m_Extents;

		if ((min.x == 0 || min.y == 0 || min.z == 0))
			return GetEntityMinBounds(entity, 1);

		return bounds;

		SAFE_ERROR();

		return GetEntityMinBounds(entity);

		SAFE_END();
	}

	static std::optional<BoxScreen> GetEntityScreenBox(game::Entity* entity)
	{
		if (s_Camera == nullptr)
			return {};

		app::Bounds bounds = GetObjectBounds(entity);

		auto min = bounds.m_Center - bounds.m_Extents;
		auto max = bounds.m_Center + bounds.m_Extents;

		BoxScreen box;
		app::Vector3 temp;
#define BOX_FIELD_SET(field, px, py, pz) temp = app::Camera_WorldToScreenPoint(s_Camera, { px, py, pz });\
			if (temp.z < 1) return {};\
			box.##field = FromVec3(temp);

		BOX_FIELD_SET(lowerTopLeft, min.x, min.y, max.z);
		BOX_FIELD_SET(lowerTopRight, max.x, min.y, max.z);
		BOX_FIELD_SET(lowerBottomLeft, min.x, min.y, min.z);
		BOX_FIELD_SET(lowerBottomRight, max.x, min.y, min.z);

		BOX_FIELD_SET(upperTopLeft, min.x, max.y, max.z);
		BOX_FIELD_SET(upperTopRight, max.x, max.y, max.z);
		BOX_FIELD_SET(upperBottomLeft, min.x, max.y, min.z);
		BOX_FIELD_SET(upperBottomRight, max.x, max.y, min.z);

#undef BOX_FIELD_SET

		return box;
	}

	static void ScaleBoxScreen(BoxScreen& boxScreen)
	{
		if (s_ResolutionScale.x != 0)
		{

#define SCALE_FIELD(field) boxScreen.##field##.x *= s_ResolutionScale.x; boxScreen.##field##.y *= s_ResolutionScale.y

			SCALE_FIELD(lowerTopLeft);
			SCALE_FIELD(lowerTopRight);
			SCALE_FIELD(lowerBottomLeft);
			SCALE_FIELD(lowerBottomRight);

			SCALE_FIELD(upperTopLeft);
			SCALE_FIELD(upperTopRight);
			SCALE_FIELD(upperBottomLeft);
			SCALE_FIELD(upperBottomRight);

#undef SCALE_FIELD

		}

		auto screenHeight = app::Screen_get_height(nullptr);

#define FIX_Y(field) boxScreen.##field##.y = screenHeight - boxScreen.##field##.y

		FIX_Y(lowerTopLeft);
		FIX_Y(lowerTopRight);
		FIX_Y(lowerBottomLeft);
		FIX_Y(lowerBottomRight);

		FIX_Y(upperTopLeft);
		FIX_Y(upperTopRight);
		FIX_Y(upperBottomLeft);
		FIX_Y(upperBottomRight);

#undef FIX_Y

	}

	static Rect GetEntityScreenRect(const BoxScreen& box, bool scalling = true)
	{
		Rect boxRect{};

		boxRect.xMin = std::min({ box.lowerTopLeft.x, box.lowerTopRight.x, box.lowerBottomLeft.x, box.lowerBottomRight.x,
			box.upperTopLeft.x, box.upperTopRight.x, box.upperBottomRight.x, box.upperBottomLeft.x });
		boxRect.xMax = std::max({ box.lowerTopLeft.x, box.lowerTopRight.x, box.lowerBottomLeft.x, box.lowerBottomRight.x,
			box.upperTopLeft.x, box.upperTopRight.x, box.upperBottomRight.x, box.upperBottomLeft.x });

		boxRect.yMin = std::max({ box.lowerTopLeft.y, box.lowerTopRight.y, box.lowerBottomLeft.y, box.lowerBottomRight.y,
			box.upperTopLeft.y, box.upperTopRight.y, box.upperBottomRight.y, box.upperBottomLeft.y });
		boxRect.yMax = std::min({ box.lowerTopLeft.y, box.lowerTopRight.y, box.lowerBottomLeft.y, box.lowerBottomRight.y,
			box.upperTopLeft.y, box.upperTopRight.y, box.upperBottomRight.y, box.upperBottomLeft.y });

		if (!scalling)
		{
			std::swap(boxRect.yMin, boxRect.yMax);
			return boxRect;
		}

		if (s_ResolutionScale.x != 0)
		{
			boxRect.xMin *= s_ResolutionScale.x;
			boxRect.xMax *= s_ResolutionScale.x;

			boxRect.yMin *= s_ResolutionScale.y;
			boxRect.yMax *= s_ResolutionScale.y;
		}

		auto screenHeight = app::Screen_get_height(nullptr);
		boxRect.yMin = screenHeight - boxRect.yMin;
		boxRect.yMax = screenHeight - boxRect.yMax;
		return boxRect;
	}

	static void DrawQuadLines(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, ImU32 col, float thicc)
	{
		auto draw = ImGui::GetBackgroundDrawList();

		draw->AddLine(p1, p2, col, thicc);
		draw->AddLine(p2, p3, col, thicc);
		draw->AddLine(p3, p4, col, thicc);
		draw->AddLine(p4, p1, col, thicc);
	}

	static bool HasCenter(const Rect& rect)
	{
		ImVec2 centerPoint = ImVec2(s_ScreenResolution.x / 2, s_ScreenResolution.y / 2);

		return rect.xMin < centerPoint.x && centerPoint.x < rect.xMax &&
			rect.yMin < centerPoint.y && centerPoint.y < rect.yMax;
	}

	static Rect DrawBox(game::Entity* entity, const ImColor& color)
	{
		auto box = GetEntityScreenBox(entity);
		if (!box)
			return {};

		ScaleBoxScreen(*box);
		auto& esp = ESP::getInstance();
		auto draw = ImGui::GetBackgroundDrawList();

		ImColor newColor = color;
		newColor.Value.w = 1.0f - esp.f_FillTransparency.getValue();

		float threshold = 2.0f;
#define ADD_FIXED_QUAD(p1, p2, p3, p4, col) {\
						ImVec2 p13 { std::abs(p3.x - p1.x), std::abs(p3.y - p1.y) };\
						ImVec2 p24 { std::abs(p2.x - p4.x), std::abs(p2.y - p4.y) };\
						if ((p13.x > threshold && p13.y > threshold) || \
						    (p24.x > threshold && p24.y > threshold) || \
						    (p13.x > threshold && p24.y > threshold) || \
						    (p24.x > threshold && p13.y > threshold))\
							draw->AddQuadFilled(p1, p2, p3, p4, newColor);\
			}

		ADD_FIXED_QUAD(box->lowerBottomLeft, box->lowerTopLeft, box->lowerTopRight, box->lowerBottomRight, newColor);
		ADD_FIXED_QUAD(box->upperBottomLeft, box->upperTopLeft, box->upperTopRight, box->upperBottomRight, newColor);

		ADD_FIXED_QUAD(box->lowerBottomLeft, box->upperBottomLeft, box->upperBottomRight, box->lowerBottomRight, newColor);
		ADD_FIXED_QUAD(box->lowerTopLeft, box->upperTopLeft, box->upperTopRight, box->lowerTopRight, newColor);

		ADD_FIXED_QUAD(box->lowerBottomLeft, box->lowerTopLeft, box->upperTopLeft, box->upperBottomLeft, newColor);
		ADD_FIXED_QUAD(box->lowerBottomRight, box->lowerTopRight, box->upperTopRight, box->upperBottomRight, newColor);

#undef ADD_FIXED_QUAD

		DrawQuadLines(box->lowerBottomLeft, box->lowerTopLeft, box->lowerTopRight, box->lowerBottomRight, color, esp.f_OutlineThickness.getValue());
		DrawQuadLines(box->upperBottomLeft, box->upperTopLeft, box->upperTopRight, box->upperBottomRight, color, esp.f_OutlineThickness.getValue());

		draw->AddLine(box->lowerBottomLeft, box->upperBottomLeft, color, esp.f_OutlineThickness.getValue());
		draw->AddLine(box->lowerTopLeft, box->upperTopLeft, color, esp.f_OutlineThickness.getValue());
		draw->AddLine(box->lowerTopRight, box->upperTopRight, color, esp.f_OutlineThickness.getValue());
		draw->AddLine(box->lowerBottomRight, box->upperBottomRight, color, esp.f_OutlineThickness.getValue());
		// top<->bottom lines

		auto rect = GetEntityScreenRect(*box, false);
		return rect;
	}

	static void UpdateAvatarPosition()
	{
		SAFE_BEGIN();
		auto& manager = game::EntityManager::getInstance();
		auto avatarPos = WorldToScreenPosScalled(manager.avatar()->relativePosition());

		s_AvatarPosition = ImVec2(avatarPos.x, avatarPos.y);
		SAFE_EEND();
	}

	static std::optional<ImVec2> GetEntityScreenPos(game::Entity* entity)
	{
		auto targetPos = WorldToScreenPosScalled(entity->relativePosition());
		if (targetPos.z < 1)
			return {};

		return ImVec2(targetPos.x, targetPos.y);
	}

	static void DrawLine(game::Entity* entity, const ImColor& color)
	{
		auto screenPos = GetEntityScreenPos(entity);
		if (!screenPos)
			return;

		auto draw = ImGui::GetBackgroundDrawList();

		auto& esp = ESP::getInstance();
		ImRect screen_rect = { 0.0f, 0.0f, ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y };
		auto screen_center = screen_rect.GetCenter();

		//LOG_DEBUG("screen_center = %f %f", screen_center.x, screen_center.y);
		//LOG_DEBUG("screenPos = %f %f", screenPos.value().x, screenPos.value().y);

		draw->AddLine(screen_center, *screenPos, color, esp.f_TracerSize.getValue());
	}

	static void DrawName(const Rect& boxRect, game::Entity* entity, const std::string& name, const ImColor& color, const ImColor& contrastColor)
	{
		auto& esp = ESP::getInstance();
		auto& manager = game::EntityManager::getInstance();

		std::string text;
		if (esp.f_DrawName.getValue() && esp.f_DrawDistance.getValue()) {
			double distance = manager.avatar()->distance(entity);
			std::ostringstream oss;
			oss << name << " | " << std::fixed << std::setprecision(1) << distance << "m";
			text = oss.str();
		}
		else if (esp.f_DrawDistance.getValue()) {
			double distance = manager.avatar()->distance(entity);
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(1) << distance << "m";
			text = oss.str();
		}
		else {
			text = name;
		}

		//LOG_DEBUG("text = %s", text.c_str());

		ImVec2 namePosition;
		if (!boxRect.empty())
			namePosition = { boxRect.xMin, boxRect.yMin - esp.f_FontSize.getValue() };
		else
		{
			auto screenPos = GetEntityScreenPos(entity);
			if (!screenPos)
				return;
			namePosition = *screenPos;

			// Might need to be aware of performance hit but there shouldn't be any.
			ImGuiContext& g = *GImGui;
			ImFont* font = g.Font;
			auto textSize = font->CalcTextSizeA(static_cast<float>(esp.f_FontSize.getValue()), FLT_MAX, FLT_MAX, text.c_str());
			namePosition.x -= (textSize.x / 2.0f);
			namePosition.y -= esp.f_FontSize.getValue();
		}


		auto draw = ImGui::GetBackgroundDrawList();
		auto font = GetFontBySize(static_cast<float>(esp.f_FontSize.getValue()));
		draw->AddText(font, static_cast<float>(esp.f_FontSize.getValue()), namePosition, color, text.c_str());
	}

	bool DrawEntity(const std::string& name, game::Entity* entity, const ImColor& contrastColor)
	{
		SAFE_BEGIN();
		auto& esp = ESP::getInstance();

		Rect rect;
		if (esp.f_DrawBox) {
			rect = DrawBox(entity, esp.GlobalBoxColor);
		}

		if (esp.f_DrawTracer) {
			DrawLine(entity, esp.GlobalLineColor);
		}

		if (esp.f_DrawName.getValue() || esp.f_DrawDistance.getValue())
			DrawName(rect, entity, name, esp.GlobalTextColor,
				esp.m_FontContrastColor);

		return HasCenter(rect);
		SAFE_ERROR();
		return false;
		SAFE_END();
	}

	void PrepareFrame()
	{
		UpdateMainCamera();
		UpdateResolutionScale();

		auto& esp = ESP::getInstance();
		if (esp.f_DrawTracer)
			UpdateAvatarPosition();
	}
}
