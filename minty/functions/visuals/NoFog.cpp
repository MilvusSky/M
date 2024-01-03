#include "NoFog.h"

namespace cheat {
	static void onUpdate_5(app::GameManager* __this, app::MethodInfo* method);

	NoFog::NoFog() : Function() {
		f_Enabled = config::getValue("functions:NoFog", "enabled", false);

		f_Hotkey = Hotkey("functions:NoFog");

		HookManager::install(app::GameManager_Update, onUpdate_5);
	}

	NoFog& NoFog::getInstance() {
		static NoFog instance;
		return instance;
	}

	void NoFog::GUI() {
		ConfigCheckbox(_("NO_FOG_TITLE"), f_Enabled, _("NO_FOG_DESCRIPTION"));

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void NoFog::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void NoFog::Status() {
		if (f_Enabled.getValue())
			ImGui::Text(_("NO_FOG_TITLE"));
	}

	std::string NoFog::getModule() {
		return _("MODULE_VISUALS");
	}

	static bool _prevEnabledState = false;

	void onUpdate_5(app::GameManager* __this, app::MethodInfo* method) {
		auto& noFog = NoFog::getInstance();
		bool enabled = noFog.f_Enabled.getValue();

		if (_prevEnabledState != enabled) {
			app::RenderSettings_set_fog(!enabled);
			_prevEnabledState = enabled;
		}
		CALL_ORIGIN(onUpdate_5, __this, method);
	}
}
