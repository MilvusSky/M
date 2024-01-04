#include "Peeking.h"

namespace cheat {
	static void MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue(app::MoleMole_VCBaseSetDitherValue* __this, float value);

	Peeking::Peeking() {
		f_Enabled = config::getValue("functions:Peeking", "enabled", false);

		f_Hotkey = Hotkey("functions:Peeking");

		HookManager::install(app::MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue);
	}

	Peeking& Peeking::getInstance() {
		static Peeking instance;
		return instance;
	}

	void Peeking::GUI() {
		ConfigCheckbox(_("ENABLE_PEEKING_TITLE"), f_Enabled, _("ENABLE_PEEKING_DESCRIPTION"));

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void Peeking::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void Peeking::Status() {
		if (f_Enabled.getValue())
			ImGui::Text(_("ENABLE_PEEKING_TITLE"));
	}

	std::string Peeking::getModule() {
		return _("MODULE_VISUALS");
	}

	void MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue(app::MoleMole_VCBaseSetDitherValue* __this, float value) {
		auto& peeking = Peeking::getInstance();

		if (peeking.f_Enabled.getValue())
			value = 1;
		CALL_ORIGIN(MoleMole_VCBaseSetDitherValue_set_ManagerDitherAlphaValue, __this, value);
	}
}
