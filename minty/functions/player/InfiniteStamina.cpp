#include "InfiniteStamina.h"

namespace cheat {
	void DataItem_HandleNormalProp_Hook(app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state);
	void VCHumanoidMove_Scara_Hook(app::VCHumanoidMove* __this, float val);
	void LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook(app::LevelSyncCombatPlugin* __this, uint32_t entityId, app::MotionInfo* syncInfo, bool isReliable, uint32_t reliableSeq);

	InfiniteStamina::InfiniteStamina() {
		f_Enabled = config::getValue("functions:InfiniteStamina", "enabled", false);

		f_Hotkey = Hotkey("functions:InfiniteStamina");

		HookManager::install(app::MoleMole_DataItem_HandleNormalProp, DataItem_HandleNormalProp_Hook);
		HookManager::install(app::VCHumanoidMove_Scara, VCHumanoidMove_Scara_Hook);
		HookManager::install(app::MoleMole_LevelSyncCombatPlugin_RequestSceneEntityMoveReq, LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook);
	}

	InfiniteStamina& InfiniteStamina::getInstance() {
		static InfiniteStamina instance;
		return instance;
	}

	void InfiniteStamina::GUI() {
		ConfigCheckbox(_("INFINITE_STAMINA_TITLE"), f_Enabled, _("INFINITE_STAMINA_DESCRIPTION"));

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void InfiniteStamina::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void InfiniteStamina::Status() {
		if (f_Enabled.getValue())
			ImGui::Text(_("INFINITE_STAMINA_TITLE"));
	}

	std::string InfiniteStamina::getModule() {
		return _("MODULE_PLAYER");
	}

	bool InfiniteStamina::OnPropertySet(app::PropType__Enum propType) {
		using PT = app::PropType__Enum;
		static bool override_cheat = true;

		if (propType == PT::PROP_CUR_TEMPORARY_STAMINA)
			override_cheat = true;

		const bool result = !f_Enabled.getValue() || override_cheat ||
			(propType != PT::PROP_MAX_STAMINA &&
				propType != PT::PROP_CUR_PERSIST_STAMINA &&
				propType != PT::PROP_CUR_TEMPORARY_STAMINA);

		if (propType == PT::PROP_MAX_STAMINA)
			override_cheat = false;
		return result;
	}

	void LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook(app::LevelSyncCombatPlugin* __this, uint32_t entityId, app::MotionInfo* syncInfo,
		bool isReliable, uint32_t reliableSeq) {
		static bool afterDash = false;

		auto& infiniteStamina = InfiniteStamina::getInstance();
		auto& manager = game::EntityManager::getInstance();
		auto entity = manager.entity(entityId);

		//LOG_DEBUG("entityType: %s", magic_enum::enum_name(entity->type()).data());
		if (entity->type() == app::EntityType__Enum_1::Vehicle || entity->isAvatar()) {
			if (infiniteStamina.f_Enabled.getValue()) {
				auto state = app::MotionInfo_get_State(syncInfo);
				//LOG_DEBUG("state: %s", magic_enum::enum_name(state).data());
				switch (state) {
				case app::MotionState__Enum::MotionDash:
				case app::MotionState__Enum::MotionClimb:
				case app::MotionState__Enum::MotionClimbJump:
				case app::MotionState__Enum::MotionStandbyToClimb:
				case app::MotionState__Enum::MotionSwimDash:
				case app::MotionState__Enum::MotionSwimIdle:
				case app::MotionState__Enum::MotionSwimMove:
				case app::MotionState__Enum::MotionSwimJump:
				case app::MotionState__Enum::MotionDiveDash:
				case app::MotionState__Enum::MotionDiveIdle:
				case app::MotionState__Enum::MotionDiveMove:
				case app::MotionState__Enum::MotionDiveSwimDash:
				case app::MotionState__Enum::MotionDiveSwimIdle:
				case app::MotionState__Enum::MotionDiveSwimMove:
				case app::MotionState__Enum::MotionFly:
				case app::MotionState__Enum::MotionFight:
				case app::MotionState__Enum::MotionDashBeforeShake:
				case app::MotionState__Enum::MotionDangerDash:
					app::MotionInfo_set_State(syncInfo, app::MotionState__Enum::MotionRun);
					break;
				case app::MotionState__Enum::MotionJump:
					if (afterDash)
						app::MotionInfo_set_State(syncInfo, app::MotionState__Enum::MotionRun);
					break;
				case app::MotionState__Enum::MotionSkiffDash:
				case app::MotionState__Enum::MotionSkiffPoweredDash:
					app::MotionInfo_set_State(syncInfo, app::MotionState__Enum::MotionSkiffNormal);
					break;
				}

				if (state != app::MotionState__Enum::MotionJump && state != app::MotionState__Enum::MotionFallOnGround)
					afterDash = state == app::MotionState__Enum::MotionDash;
			}
		}

		CALL_ORIGIN(LevelSyncCombatPlugin_RequestSceneEntityMoveReq_Hook, __this, entityId, syncInfo, isReliable, reliableSeq);
	}

	void DataItem_HandleNormalProp_Hook(app::DataItem* __this, uint32_t type, int64_t value, app::DataPropOp__Enum state) {
		auto& infiniteStamina = InfiniteStamina::getInstance();
		//LOG_DEBUG("type: %d", type);
		auto propType = static_cast<app::PropType__Enum>(type);
		bool isValid = infiniteStamina.OnPropertySet(propType);

		if (isValid)
			CALL_ORIGIN(DataItem_HandleNormalProp_Hook, __this, type, value, state);
	}

	void VCHumanoidMove_Scara_Hook(app::VCHumanoidMove* __this, float val) {
		auto& infiniteStamina = InfiniteStamina::getInstance();

		if (infiniteStamina.f_Enabled.getValue())
			val = 34028234663852885981170418348451692544.0f;
		CALL_ORIGIN(VCHumanoidMove_Scara_Hook, __this, val);
	}
}
