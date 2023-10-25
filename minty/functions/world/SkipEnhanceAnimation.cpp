#include "SkipEnhanceAnimation.h"

namespace cheat {
    static void MoleMole_EquipLevelUpDialogContext_SetupView_Hook(app::MoleMole_EquipLevelUpDialogContext* __this);
    static void MoleMole_EquipOverviewPageContext_PlayExpAddAnimation_Hook(void* __this, float startPer, float endPer, void* callback);
    static void MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow_Hook(void* __this, void* refreshViewAction);

    static uint32_t substatRollLevels[] = { 5, 9, 13, 17, 21 }; // artifact levels from the field go from 1 to 21, so we do +1

	SkipEnhanceAnimation::SkipEnhanceAnimation() {
		f_Enabled = config::getValue("functions:SkipEnhanceAnimation", "enabled", false);
		f_ShowLevelUp = config::getValue("functions:SkipEnhanceAnimation", "showLevelUp", true);

        HookManager::install(app::MoleMole_EquipLevelUpDialogContext_SetupView, MoleMole_EquipLevelUpDialogContext_SetupView_Hook);
        HookManager::install(app::MoleMole_EquipOverviewPageContext_PlayExpAddAnimation, MoleMole_EquipOverviewPageContext_PlayExpAddAnimation_Hook);
        HookManager::install(app::MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow, MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow_Hook);
	}

	SkipEnhanceAnimation& SkipEnhanceAnimation::getInstance() {
		static SkipEnhanceAnimation instance;
		return instance;
	}

	void SkipEnhanceAnimation::GUI() {
		ConfigCheckbox("Skip Enhance Animation", f_Enabled);
        ImGui::SameLine();
        HelpMarker("Skip weapon and artifact enhancement animation.");

		if (f_Enabled.getValue()) {
			ImGui::Indent();
            ConfigCheckbox("Show Level-Up Dialog For Substat Rolls", f_ShowLevelUp);
            ImGui::SameLine();
            HelpMarker(_("Show level up dialog when artifacts roll substats\n"
                "(when hitting levels 4, 8, 12, 16, and 20)."));
            skipAnimHotkey.Draw();
			ImGui::Unindent();
		}
	}

	void SkipEnhanceAnimation::Outer() {
        if (skipAnimHotkey.IsPressed())
            f_Enabled.setValue(!f_Enabled.getValue());
	}

	void SkipEnhanceAnimation::Status() {
        if (f_Enabled.getValue())
            ImGui::Text(!f_ShowLevelUp.getValue() ? "SkipAnim" : "SkipAnim|ShowLevelUp");
	}

	std::string SkipEnhanceAnimation::getModule() {
		return _("World");
	}

    bool ShouldShowLevelUpDialog(app::MoleMole_EquipLevelUpDialogContext* dialog) {
        auto& SkipEnhanceAnimation = SkipEnhanceAnimation::getInstance();

        if (SkipEnhanceAnimation.f_ShowLevelUp.getValue()) {
            /*
            LOG_DEBUG("_prevLevel: %d", dialog->fields._prevLevel);
            LOG_DEBUG("_powerUpRate: %d", dialog->fields._powerUpRate);
            LOG_DEBUG("_currLevel: %d", dialog->fields._currLevel);
            */
            if (dialog->fields._equipType == app::MoleMole_Config_ItemType__Enum::ITEM_RELIQUARY) {
                const uint32_t prevLvl = dialog->fields._prevLevel;
                const uint32_t currLvl = dialog->fields._currLevel;
                return std::any_of(std::begin(substatRollLevels), std::end(substatRollLevels),
                    [prevLvl, currLvl](uint32_t level) { return prevLvl < level && level <= currLvl; });
            }
        }
        return false;
    }

    void MoleMole_EquipLevelUpDialogContext_SetupView_Hook(app::MoleMole_EquipLevelUpDialogContext* __this) {
        CALL_ORIGIN(MoleMole_EquipLevelUpDialogContext_SetupView_Hook, __this);

        auto& SkipEnhanceAnimation = SkipEnhanceAnimation::getInstance();

        if (SkipEnhanceAnimation.f_Enabled.getValue() && !ShouldShowLevelUpDialog(__this))
            app::MoleMole_EquipLevelUpDialogContext_ShowReturnedMaterialAndCloseDialog(__this);
    }

    void MoleMole_EquipOverviewPageContext_PlayExpAddAnimation_Hook(/*MoleMole_EquipOverviewPageContext*/ void* __this, float startPer, float endPer, /*Action*/ void* callback) {
        auto& SkipEnhanceAnimation = SkipEnhanceAnimation::getInstance();

        if (SkipEnhanceAnimation.f_Enabled.getValue())
            return app::Action_Invoke(callback);
        CALL_ORIGIN(MoleMole_EquipOverviewPageContext_PlayExpAddAnimation_Hook, __this, startPer, endPer, callback);
    }

    void MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow_Hook(/*MoleMole_EquipOverviewPageContext*/ void* __this, /*Action*/ void* refreshViewAction) {
        auto& SkipEnhanceAnimation = SkipEnhanceAnimation::getInstance();

        if (SkipEnhanceAnimation.f_Enabled.getValue())
            return app::Action_Invoke(refreshViewAction);
        CALL_ORIGIN(MoleMole_EquipOverviewPageContext_PlayLevelUpSuccessShow_Hook, __this, refreshViewAction);
    }
}