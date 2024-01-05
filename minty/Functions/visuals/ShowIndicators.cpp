#include "ShowIndicators.h"

namespace cheat {
	bool IndicatorPlugin_DoCheck(app::LCIndicatorPlugin* __this);

	ShowIndicators::ShowIndicators() {
		f_Enabled = config::getValue("functions:ShowIndicators", "enabled", false);
		f_ShowWaypoints = config::getValue("functions:ShowIndicators", "waypoints", false);
		f_ShowChests = config::getValue("functions:ShowIndicators", "chests", false);

		f_Hotkey = Hotkey("functions:ShowIndicators");

		HookManager::install(app::MoleMole_LCIndicatorPlugin_DoCheck, IndicatorPlugin_DoCheck);
	}

	ShowIndicators& ShowIndicators::getInstance() {
		static ShowIndicators instance;
		return instance;
	}

	void ShowIndicators::GUI() {
		ConfigCheckbox(_("SHOW_INDICATORS_TITLE"), f_Enabled, _("SHOW_INDICATORS_DESCRIPTION"));

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigCheckbox(_("CHESTS_INDICATORS_TITLE"), f_ShowChests, _("CHESTS_INDICATORS_DESCRIPTION"));
			ConfigCheckbox(_("WAYPOINTS_INDICATORS_TITLE"), f_ShowWaypoints, _("WAYPOINTS_INDICATORS_DESCRIPTION"));

			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void ShowIndicators::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void ShowIndicators::Status() {
		if (f_Enabled.getValue()) {
			/*ImGui::Text("%s (%s)", _("SHOW_INDICATORS_TITLE"),
				f_ShowChests.getValue() && f_ShowWaypoints.getValue() ? _("ALL_INDICATORS_STATUS") :
				f_ShowChests.getValue() ? _("CHESTS_INDICATORS_STATUS") :
				f_ShowWaypoints.getValue() ? _("WAYPOINTS_INDICATORS_STATUS") :
				_("NONE_INDICATORS_STATUS"));*/
			ImGui::Text("%s", _("SHOW_INDICATORS_TITLE"));
		}
	}

	std::string ShowIndicators::getModule() {
		return _("MODULE_VISUALS");
	}

	bool IndicatorPlugin_DoCheck(app::LCIndicatorPlugin* __this) {
		auto& showIndicators = ShowIndicators::getInstance();

		if (showIndicators.f_Enabled.getValue()) {
			bool isWaypoint = __this->fields._dataItem->fields.ownerUid == 0;
			bool showIcon = (showIndicators.f_ShowChests.getValue() && !isWaypoint) ||
			(showIndicators.f_ShowWaypoints.getValue() && isWaypoint) ||
			(showIndicators.f_ShowChests.getValue() && showIndicators.f_ShowWaypoints.getValue());
			/*bool showIcon = showIndicators.f_ShowChests.getValue() ? !isWaypoint :
				showIndicators.f_ShowWaypoints.getValue() ? isWaypoint :
				showIndicators.f_ShowChests.getValue() && showIndicators.f_ShowWaypoints.getValue();*/

			if (showIcon)
				app::MoleMole_LCIndicatorPlugin_ShowIcon(__this);
			else
				app::MoleMole_LCIndicatorPlugin_HideIcon(__this);
		}
		return CALL_ORIGIN(IndicatorPlugin_DoCheck, __this);
	}
}
