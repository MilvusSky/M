#include "FovChanger.h"

namespace cheat {
	void InLevelCameraSetFov_Hook(app::Camera* __this, float value);

	FovChanger::FovChanger() {
		f_Enabled = config::getValue("functions:FovChanger", "enabled", false);
		f_Fov = config::getValue("functions:FovChanger", "fov", 45.0f);

		f_Hotkey = Hotkey("functions:FovChanger");

		HookManager::install(app::Camera_set_fieldOfView, InLevelCameraSetFov_Hook);
	}

	FovChanger& FovChanger::getInstance() {
		static FovChanger instance;
		return instance;
	}

	void FovChanger::GUI() {
		ConfigCheckbox(_("FOV_CHANGER_TITLE"), f_Enabled, _("FOV_CHANGER_DESCRIPTION"));

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigSliderFloat(_("FOV_TITLE"), f_Fov, 10.0f, 170.0f, _("FOV_DESCRIPTION"));
			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void FovChanger::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void FovChanger::Status() {
		if (f_Enabled.getValue())
			ImGui::Text("%s (%.1f)", _("FOV_CHANGER_TITLE"), f_Fov.getValue());
	}

	std::string FovChanger::getModule() {
		return _("MODULE_VISUALS");
	}

	void InLevelCameraSetFov_Hook(app::Camera* __this, float value) {
		auto& fovChanger = FovChanger::getInstance();

		if (fovChanger.f_Enabled.getValue())
			value = fovChanger.f_Fov.getValue();
		CALL_ORIGIN(InLevelCameraSetFov_Hook, __this, value);
	}
}
