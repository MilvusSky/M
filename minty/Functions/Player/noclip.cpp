#include "NoClip.h"

namespace cheat {
	void GameManager_Update_Hook(app::GameManager* __this, app::MethodInfo* method);
	void HumanoidMoveFSM_LateTick_Hook(app::HumanoidMoveFSM* __this, float deltaTime, app::MethodInfo* method);

	NoClip::NoClip() {
		f_Enabled = config::getValue("functions:NoClip", "enabled", false);
		f_EnabledAltSpeed = config::getValue("functions:NoClip:Alt", "enabled", false);
		f_Speed = config::getValue("functions:NoClip", "speed", 5.0f);
		f_AltSpeed = config::getValue("functions:NoClip:Alt", "speed", 10.0f);

		f_Hotkey = Hotkey("functions:NoClip");
		f_HotkeyAlt = Hotkey("functions:NoClip:Alt", VK_LCONTROL);

		HookManager::install(app::GameManager_Update, GameManager_Update_Hook);
		HookManager::install(app::MoleMole_HumanoidMoveFSM_LateTick, HumanoidMoveFSM_LateTick_Hook);
	}

	NoClip& NoClip::getInstance() {
		static NoClip instance;
		return instance;
	}

	void NoClip::GUI() {
		ConfigCheckbox(_("NO_CLIP_TITLE"), f_Enabled, _("NO_CLIP_DESCRIPTION"));

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigSliderFloat(_("SPEED_TITLE"), f_Speed, 0.1f, 100.0f, _("SPEED_DESCRIPTION"));
			ConfigCheckbox(_("ALT_NO_CLIP_TITLE"), f_EnabledAltSpeed, _("ALT_NO_CLIP_DESCRIPTION"));

			if (f_EnabledAltSpeed.getValue()) {
				ImGui::Indent();
				ConfigSliderFloat(_("ALT_SPEED_TITLE"), f_AltSpeed, 0.1f, 100.0f, _("ALT_SPEED_DESCRIPTION"));
				f_HotkeyAlt.Draw();
				ImGui::Unindent();
			}
			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void NoClip::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());

		if (f_EnabledAltSpeed.getValue() && f_HotkeyAlt.IsDown())
			f_finalSpeed = f_AltSpeed.getValue();
		else
			f_finalSpeed = f_Speed.getValue();
	}

	void NoClip::Status() {
		if (f_Enabled.getValue())
			ImGui::Text("%s (%.1f|%.1f)",
				_("NO_CLIP_TITLE"), f_Speed.getValue(), f_AltSpeed.getValue());
	}

	std::string NoClip::getModule() {
		return _("MODULE_PLAYER");
	}

	app::Vector3 prevPos, newPos, posCheck;

	static std::string ActiveHero;

	app::Rigidbody* rigidbody;
	app::GameObject* AvatarRoot;
	app::GameObject* nameAvatar;
	app::Transform* avatarTransform;
	app::GameObject* HeroGameObject;

	void onNoClip() {
		AvatarRoot = app::GameObject_Find(string_to_il2cppi("/EntityRoot/AvatarRoot"));
		//LOG_DEBUG("found avatar");
		auto Transform = app::GameObject_GetComponentByName(AvatarRoot, string_to_il2cppi("Transform"));
		//LOG_DEBUG("found transform");
		auto HeroCount = app::Transform_GetChildCount(reinterpret_cast<app::Transform*>(Transform));
		//LOG_DEBUG("found count");
		for (int i = 0; i <= HeroCount - 1; i++) {
			auto HeroComponent = app::Transform_GetChild(reinterpret_cast<app::Transform*>(Transform), i);
			//LOG_DEBUG("found child");
			HeroGameObject = app::Component_1_get_gameObject(reinterpret_cast<app::Component_1*>(HeroComponent));
			//LOG_DEBUG("found gameobj");
			auto isActiveHero = app::GameObject_get_active(HeroGameObject);
			//LOG_DEBUG("found active");
			if (isActiveHero) {
				auto GameObjectName = app::Object_1_get_name(reinterpret_cast<app::Object_1*>(HeroGameObject));
				//LOG_DEBUG("found name");
				ActiveHero = il2cppi_to_string(GameObjectName);
				std::string Hero = ActiveHero.erase(ActiveHero.find("(Clone)"));
				std::string avatarName = "/EntityRoot/AvatarRoot/" + il2cppi_to_string(GameObjectName) + "/OffsetDummy/" + Hero.c_str();
				nameAvatar = app::GameObject_Find(string_to_il2cppi(avatarName));
				//LOG_DEBUG("found gameob2");
				avatarTransform = app::GameObject_get_transform(nameAvatar);
				//LOG_DEBUG("found transfor2");
				rigidbody = reinterpret_cast<app::Rigidbody*>(app::GameObject_GetComponentByName(HeroGameObject, string_to_il2cppi("Rigidbody")));
				//LOG_DEBUG("found rb");
				if (rigidbody != 0)
					break;
			}
		}

		app::Rigidbody_set_collisionDetectionMode(rigidbody, app::CollisionDetectionMode__Enum::Continuous);
		//app::Rigidbody_set_detectCollisions(rigidbody, false);
		//LOG_DEBUG("coli det");
		auto cameraEntity = app::GameObject_get_transform(
			app::GameObject_Find(string_to_il2cppi("/EntityRoot/MainCamera(Clone)(Clone)")));
		//LOG_DEBUG("found transfom cam");
		app::Vector3 dir = {};

		if (ImGui::IsKeyDown(ImGuiKey_W))
			dir = dir + app::Transform_get_forward(cameraEntity);

		if (ImGui::IsKeyDown(ImGuiKey_S))
			dir = dir - app::Transform_get_forward(cameraEntity);

		if (ImGui::IsKeyDown(ImGuiKey_D))
			dir = dir + app::Transform_get_right(cameraEntity);

		if (ImGui::IsKeyDown(ImGuiKey_A))
			dir = dir - app::Transform_get_right(cameraEntity);

		if (ImGui::IsKeyDown(ImGuiKey_Space))
			dir = dir + app::Transform_get_up(avatarTransform);

		if (ImGui::IsKeyDown(ImGuiKey_ModShift))
			dir = dir - app::Transform_get_up(avatarTransform);

		prevPos = app::Rigidbody_get_position(rigidbody);
		//LOG_DEBUG("rb go pos");
		if (prevPos.x == 0 && prevPos.y == 0 && prevPos.z == 0)
			return;

		float deltaTime = app::Time_get_deltaTime() * 1.5F;
		//LOG_DEBUG("got delt");
		newPos = prevPos + dir * NoClip::f_finalSpeed * deltaTime;

		app::Rigidbody_set_velocity(rigidbody, { 0,0,0 });
		//LOG_DEBUG("rb setvel");
		//app::Rigidbody_set_velocity(rigidbody, dir * NoClip::f_finalSpeed);
		app::Rigidbody_MovePosition(rigidbody, newPos);
		//LOG_DEBUG("rb movepos");
	}

	void GameManager_Update_Hook(app::GameManager* __this, app::MethodInfo* method) {
		auto& noClip = NoClip::getInstance();

		__try {
			if (noClip.f_Enabled.getValue())
				onNoClip();
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			//LOG_WARNING("Exception 0x%08x.", GetExceptionCode());
		}

		CALL_ORIGIN(GameManager_Update_Hook, __this, method);
	}

	void HumanoidMoveFSM_LateTick_Hook(app::HumanoidMoveFSM* __this, float deltaTime, app::MethodInfo* method) {
		auto& noClip = NoClip::getInstance();

		if (noClip.f_Enabled.getValue()) {
			if (app::Vector3_Distance(posCheck, newPos) > 3.0f)
				posCheck = newPos;
			else
				return;
		}

		CALL_ORIGIN(HumanoidMoveFSM_LateTick_Hook, __this, deltaTime, method);
	}
}
