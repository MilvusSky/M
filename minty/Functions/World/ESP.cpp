#include "ESPRender.h"

namespace cheat 
{
	void DrawExternal();
	static int boxItemCurrent;
	static int tracerItemCurrent;
	ImColor CalcContrastColor(const ImColor& foreground, float maxContrastRatio = 2.0f, const ImColor& background = ImColor(1.0f, 1.0f, 1.0f), const ImColor& inverted = ImColor(0.0f, 0.0f, 0.0f));

    ESP::ESP(){
		f_Enabled = config::getValue("functions:ESP", "enabled", false);
		f_MinSize = config::getValue("functions:ESP", "minSize", 0.1f);

		f_TracerSize = config::getValue("functions:ESP", "tracerSize", 1.f);
		f_ArrowRadius = config::getValue("functions:ESP", "arrowRadius", 50.f);
		f_OutlineThickness = config::getValue("functions:ESP", "outlineThickness", 0.f);

		f_Range = config::getValue("functions:ESP", "range", 200.f);

		f_DrawBox = config::getValue("functions:ESP", "drawBox", false);
		f_DrawTracer = config::getValue("functions:ESP", "drawTracer", false);

		f_FillTransparency = config::getValue("functions:ESP", "fillTransparency", 70.f);

		f_BoxItemCurrent = config::getValue("functions:ESP", "drawBoxMode", 0);
		f_TracerItemCurrent = config::getValue("functions:ESP", "drawTracerMode", 0);

		boxItemCurrent = f_BoxItemCurrent.getValue();
		tracerItemCurrent = f_TracerItemCurrent.getValue();

		// Filters
		f_Ores = config::getValue("functions:ESP:filters", "ores", false);
		f_Oculies = config::getValue("functions:ESP:filters", "oculies", false);
		f_Plants = config::getValue("functions:ESP:filters", "plants", false);
		f_PickableLoot = config::getValue("functions:ESP:filters", "itemDrops", false);
		f_Chests = config::getValue("functions:ESP:filters", "chests", false); 
		f_Monsters = config::getValue("functions:ESP:filters", "enemies", false);

		entityManager = &game::EntityManager::getInstance();
    }

	std::string ESP::getModule() {
		return _("MODULE_WORLD");
            }

	void ESP::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
		DrawExternal();
	}

    void ESP::GUI()
    {
	    if (BeginGroupPanel("General", true))
	    {
		    ConfigCheckbox("Enabled", f_Enabled, "Show filtered object through obstacles.");
			ConfigSliderFloat("Range (m)", f_Range, 1.0f, 200.0f);

			ConfigCheckbox("Draw box", f_DrawBox);

			if (f_DrawBox.getValue()) {
				const char* box_items[] = { "Rectangle", "Box" };
				ConfigSliderFloat("Transparency", f_FillTransparency, 0.01f, 1.0f, "Transparency of filled part.");
				ImGui::Combo("Box mode", &boxItemCurrent, box_items, IM_ARRAYSIZE(box_items)); ImGui::SameLine(); HelpMarker("Select the mode of box drawing");

				switch (boxItemCurrent) {
				case 0:
					f_DrawBoxMode = DrawMode::Rectangle;
					break;
				case 1:
					f_DrawBoxMode = DrawMode::Box;
					break;
				}
				config::setValue("functions:ESP", "drawBoxMode", boxItemCurrent);

			} else 
				f_DrawBoxMode = DrawMode::None;

			ConfigCheckbox("Draw tracer", f_DrawTracer); ImGui::SameLine(); HelpMarker("Draw tracer from middle part of the screen");

			if (f_DrawTracer.getValue()) {
				const char* tracer_items[] = { "Offscreen arrows", "Lines" };
				ImGui::Combo("Tracer mode", &tracerItemCurrent, tracer_items, IM_ARRAYSIZE(tracer_items)); ImGui::SameLine(); HelpMarker("Select the mode of tracer drawing");

				switch (tracerItemCurrent) {
				case 0:
					f_DrawTracerMode = DrawTracerMode::OffscreenArrows;
					break;
				case 1:
					f_DrawTracerMode = DrawTracerMode::Line;
					break;
                    }
				config::setValue("functions:ESP", "drawTracerMode", tracerItemCurrent);
			} else
				f_DrawTracerMode = DrawTracerMode::None;

		    if (f_DrawTracerMode == DrawTracerMode::OffscreenArrows)
		    {
			    if (BeginGroupPanel("Arrow tracer options", true))
			    {
					ConfigSliderFloat("Size of tracer", f_TracerSize,  0.1f, 10.0f);
					ConfigSliderFloat("Radius of arrow", f_ArrowRadius, 0.5f, 300.0f);
					ConfigSliderFloat("Outline thickness of arrow", f_OutlineThickness, 0.1f, 10.0f);
                }
			    EndGroupPanel();
        }

			ConfigCheckbox("Draw name", f_DrawName, "Draw name of object.");
			ConfigCheckbox("Draw distance", f_DrawDistance, "Draw distance of object.");

			if (f_DrawName.getValue() or f_DrawDistance.getValue()) {
				ConfigSliderInt("Font size", f_FontSize, 1, 100, "Font size of name or distance.");
				ConfigSliderFloat("Font outline", f_FontOutlineSize, 0.1f, 10.0f);
    }

		    if (BeginGroupPanel("Colors", true))
		    {
				ImGuiColorEditFlags_ flag = ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaBar;

				ImGui::ColorEdit4("Global ESP color", &f_GlobalESPColor.getValue().Value.x, flag);
				if (BeginGroupPanel("Advanced", true)) {
					ImGui::ColorEdit4("Color of box", &f_GlobalBoxColor.getValue().Value.x, flag);
					ImGui::ColorEdit4("Color of line", &f_GlobalLineColor.getValue().Value.x, flag);
					ImGui::ColorEdit4("Color of rectangle", &f_GlobalRectColor.getValue().Value.x, flag);
					ImGui::ColorEdit4("Color of arrow tracers", &f_GlobalTracersColor.getValue().Value.x, flag);
				}
				EndGroupPanel();
		    }
		    EndGroupPanel();

			if (BeginGroupPanel("Filters", true)) {
				ConfigCheckbox("Ores", f_Ores);
				ConfigCheckbox("Oculies", f_Oculies);
				ConfigCheckbox("Plants", f_Plants);
				ConfigCheckbox("Pickable loot", f_PickableLoot);
				ConfigCheckbox("Chests", f_Chests);
				ConfigCheckbox("Monsters", f_Monsters);
    }
			EndGroupPanel();

			ConfigSliderFloat("Minimal size ", f_MinSize, 0.1f, 10.0f, "Minimum entity size as measured in-world.\n" \
			    "Some entities have either extremely small or no bounds at all.\n" \
			    "This parameter helps filter out entities that don't meet this condition.");
	    }
	    EndGroupPanel();
    }

    void ESP::Status()
    {
	    ImGui::Text("ESP [%.01fm|%s|%s%s%s%s]",
		    f_Range.getValue(),
		    f_DrawBoxMode == DrawMode::Box ? "Box" : f_DrawBoxMode == DrawMode::Rectangle ? "Rect" : "None",
		    f_DrawTracerMode == DrawTracerMode::Line ? "L" : f_DrawTracerMode == DrawTracerMode::OffscreenArrows ? "A" : "",
		    f_DrawName.getValue() ? "N" : "",
		    f_DrawDistance.getValue() ? "D" : ""
	    );
    }

	ESP& ESP::getInstance()
	{
	    static ESP instance;
	    return instance;
    }

    void DrawExternal()
    {
        auto& esp = ESP::getInstance();
	    if (!esp.f_Enabled.getValue())
		    return;

	    PrepareFrame();

	    for (auto& entity : esp.entityManager->entities())
	    {
		    if (esp.entityManager->avatar()->distance(entity) > esp.f_Range.getValue())
			    continue;

			if (!(
				(esp.f_Ores.getValue() and game::filters::combined::Ores.IsValid(entity)) or
				(esp.f_Oculies.getValue() and game::filters::combined::Oculies.IsValid(entity)) or
				(esp.f_Plants.getValue() and game::filters::combined::Plants.IsValid(entity)) or
				(esp.f_PickableLoot.getValue() and 
					(game::filters::combined::AllPickableLoot.IsValid(entity) and
					game::filters::combined::Equipments.IsValid(entity) and 
					game::filters::combined::OresDrop.IsValid(entity))
					) or (esp.f_Chests.getValue() and entity->isChest()) or
				(esp.f_Monsters.getValue() and game::filters::combined::AllMonsters.IsValid(entity))
				))
				continue;

			DrawEntity(entity->name(), entity, esp.f_GlobalESPColor.getValue(), CalcContrastColor(esp.f_GlobalESPColor.getValue()));
	    }
        }
        LOG_INFO("8");
        ESPBase::DrawESP(camera, instance, filters, drawInfo);
        LOG_INFO("9");
        CALL_ORIGIN(GameManager_Update_h, this_, mi);
    };
}
