#include "ShowIndicators.h"

namespace cheat {
    bool IndicatorPlugin_DoCheck(app::LCIndicatorPlugin* __this);

    ShowIndicators::ShowIndicators() {
	f_Enabled = config::getValue("functions:ShowIndicators", "enabled", false);
	f_Waypoints = config::getValue("functions:ShowIndicators", "waypoints", false);
	f_Chests = config::getValue("functions:ShowChestIndicator", "chests", false);
        f_Hotkey = Hotkey("functions:ShowChestIndicator");

        HookManager::install(app::MoleMole_LCIndicatorPlugin_DoCheck, IndicatorPlugin_DoCheck);
    }

    ShowIndicators& ShowIndicators::getInstance() {
        static ShowIndicators instance;
        return instance;
    }

    void ShowIndicators::GUI() {
        ConfigCheckbox(_("Show indicators"), f_Enabled, _("Show chests or/and waypoints indicators."));

        if (f_Enabled.getValue()) {
            ImGui::Indent();
	    ConfigCheckbox(_("Show chests indicators"), f_Chests, _("Show chests indicators."));
	    ConfigCheckbox(_("Show waypoints indicators"), f_Waypoints, _("Show waypoints indicators."));

            f_Hotkey.Draw();
            ImGui::Unindent();
        }
    }

    void ShowIndicators::Outer() {
        if (f_Hotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
    }

    void ShowIndicators::Status() {
	if (f_Chests.getValue() and f_Waypoints.getValue()) {
	    ImGui::Text("Show chests and waypoints indicators");
	    return;
	}
	if (f_Chests.getValue()) {
	    ImGui::Text("Show chests indicators");
	    return;
	}
	if (f_Waypoints.getValue()) 
	    ImGui::Text("Show waypoints indicators");
    }

    std::string ShowIndicators::getModule() {
        return _("Visuals");
    }

    bool IndicatorPlugin_DoCheck(app::LCIndicatorPlugin* __this) {
	auto& showChestIndicator = ShowIndicators::getInstance();
	if (showChestIndicator.f_Enabled.getValue()) {
	    bool isWaypoint = (__this->fields._dataItem->fields.ownerUid == 0);

	    bool showIcon = (showChestIndicator.f_Chests.getValue() && !isWaypoint) ||
		(showChestIndicator.f_Waypoints.getValue() && isWaypoint) ||
		(showChestIndicator.f_Chests.getValue() && showChestIndicator.f_Waypoints.getValue());

	    if (showIcon)
		app::MoleMole_LCIndicatorPlugin_ShowIcon(__this);
	    else
		app::MoleMole_LCIndicatorPlugin_HideIcon(__this);
	}
	return CALL_ORIGIN(IndicatorPlugin_DoCheck, __this);
    }
}
