#include "HideDamage.h"

namespace cheat {
	void MonoParticleDamageTextContainer_ShowDamageText(void* __this, void* attackResult, void* attackee);

	HideDamage::HideDamage() : Function() {
		f_Enabled = config::getValue("functions:HideDamage", "enabled", false);

		f_Hotkey = Hotkey("functions:HideDamage");

		HookManager::install(app::MonoParticleDamageTextContainer_ShowDamageText, MonoParticleDamageTextContainer_ShowDamageText);
	}

	HideDamage& HideDamage::getInstance() {
		static HideDamage instance;
		return instance;
	}

	void HideDamage::GUI() {
		ConfigCheckbox(_("HIDE_DAMAGE_TITLE"), f_Enabled, _("HIDE_DAMAGE_DESCRIPTION"));

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void HideDamage::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void HideDamage::Status() {
		if (f_Enabled.getValue())
			ImGui::Text(_("HIDE_DAMAGE_TITLE"));
	}

	std::string HideDamage::getModule() {
		return _("MODULE_VISUALS");
	}

	void MonoParticleDamageTextContainer_ShowDamageText(void* __this, void* attackResult, void* attackee) {
		auto& hideDamage = HideDamage::getInstance();

		if (hideDamage.f_Enabled.getValue())
			return;
		CALL_ORIGIN(MonoParticleDamageTextContainer_ShowDamageText, __this, attackResult, attackee);
	}
}
