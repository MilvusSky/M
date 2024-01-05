#include "GameSpeed.h"

namespace cheat {
	void onUpdate_3(app::GameManager* __this, app::MethodInfo* method);

	GameSpeed::GameSpeed() {
		f_Enabled = config::getValue("functions:GameSpeed", "enabled", false);
		f_Speed = config::getValue("functions:GameSpeed", "multiplier", 5.0f);

		f_Hotkey = Hotkey("functions:GameSpeed");

		HookManager::install(app::GameManager_Update, onUpdate_3);
	}

	GameSpeed& GameSpeed::getInstance() {
		static GameSpeed instance;
		return instance;
	}

	void GameSpeed::GUI() {
		ConfigCheckbox(_("GAME_SPEED_TITLE"), f_Enabled, _("GAME_SPEED_DESCRIPTION"));

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigSliderFloat(_("MULTIPLIER_TITLE"), f_Speed, 1.0f, 20.0f, _("MULTIPLIER_DESCRIPTION"));
			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void GameSpeed::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void GameSpeed::Status() {
		if (f_Enabled.getValue())
			ImGui::Text("%s (%.1f)", _("GAME_SPEED_TITLE"), f_Speed.getValue());
	}

	std::string GameSpeed::getModule() {
		return _("MODULE_WORLD");
	}

	void onUpdate_3(app::GameManager* __this, app::MethodInfo* method) {
		auto& gameSpeed = GameSpeed::getInstance();

		app::Time_set_timeScale(gameSpeed.f_Enabled.getValue() ? gameSpeed.f_Speed.getValue() : 1.0f);
		CALL_ORIGIN(onUpdate_3, __this, method);
	}
}
