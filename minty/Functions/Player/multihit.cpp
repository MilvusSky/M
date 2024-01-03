#include "MultiHit.h"

namespace cheat {
	static void LCBaseCombat_FireBeingHitEvent_Hook(app::LCBaseCombat* __this, uint32_t attackeeRuntimeID, app::AttackResult* attackResult);

	MultiHit::MultiHit() {
		f_Enabled = config::getValue("functions:MultiHit", "enabled", false);
		f_Hits = config::getValue("functions:MultiHit", "hits", 1);

		f_Hotkey = Hotkey("functions:MultiHit");

		HookManager::install(app::MoleMole_LCBaseCombat_FireBeingHitEvent, LCBaseCombat_FireBeingHitEvent_Hook);
	}

	MultiHit& MultiHit::getInstance() {
		static MultiHit instance;
		return instance;
	}

	void MultiHit::GUI() {
		ConfigCheckbox(_("MULTI_HIT_TITLE"), f_Enabled, _("MULTI_HIT_DESCRIPTION"));

		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigSliderInt(_("HITS_TITLE"), f_Hits, 1, 100, _("HITS_DESCRIPTION"));
			f_Hotkey.Draw();
			ImGui::Unindent();
		}
	}

	void MultiHit::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	void MultiHit::Status() {
		if (f_Enabled.getValue())
			ImGui::Text("%s (%i)", _("MULTI_HIT_TITLE"), f_Hits.getValue());
	}

	std::string MultiHit::getModule() {
		return _("MODULE_PLAYER");
	}

	bool IsAvatarOwner(game::Entity entity) {
		auto& manager = game::EntityManager::getInstance();
		auto avatarID = manager.avatar()->runtimeID();

		while (entity.isGadget()) {
			game::Entity temp = entity;
			entity = game::Entity(app::MoleMole_GadgetEntity_GetOwnerEntity(reinterpret_cast<app::GadgetEntity*>(entity.raw())));

			if (entity.runtimeID() == avatarID)
				return true;
		}

		return false;
	}

	bool IsAttackByAvatar(game::Entity& attacker) {
		if (attacker.raw() == nullptr)
			return false;

		auto& manager = game::EntityManager::getInstance();
		auto avatarID = manager.avatar()->runtimeID();
		auto attackerID = attacker.runtimeID();

		return attackerID == avatarID || IsAvatarOwner(attacker) || attacker.type() == app::EntityType__Enum_1::Bullet ||
			attacker.type() == app::EntityType__Enum_1::Field;
	}

	bool IsConfigByAvatar(game::Entity& attacker) {
		if (attacker.raw() == nullptr)
			return false;

		auto& manager = game::EntityManager::getInstance();
		auto avatarID = manager.avatar()->configID();
		auto attackerID = attacker.configID();
		//LOG_DEBUG("attackerID.configID(): %d", attackerID);
		// IDs can be found in ConfigAbility_Avatar_*.json or GadgetExcelConfigData.json
		bool bulletID = attackerID >= 40000160 && attackerID <= 41089999;

		/*LOG_DEBUG("avatarID == attackerID: %d", avatarID == attackerID);
		LOG_DEBUG("bulletID: %d", bulletID);
		LOG_DEBUG("attacker.type() == app::EntityType__Enum_1::Bullet: %d", attacker.type() == app::EntityType__Enum_1::Bullet);*/
		return avatarID == attackerID || (bulletID && attacker.type() == app::EntityType__Enum_1::Bullet);
	}

	void LCBaseCombat_FireBeingHitEvent_Hook(app::LCBaseCombat* __this, uint32_t attackeeRuntimeID, app::AttackResult* attackResult) {
		auto& multiHit = MultiHit::getInstance();
		auto attacker = game::Entity(__this->fields._._._entity);

		if (!multiHit.f_Enabled.getValue() || !IsConfigByAvatar(attacker) || !IsAttackByAvatar(attacker))
			return CALL_ORIGIN(LCBaseCombat_FireBeingHitEvent_Hook, __this, attackeeRuntimeID, attackResult);

		for (int i = 0; i < multiHit.f_Hits.getValue(); i++)
			CALL_ORIGIN(LCBaseCombat_FireBeingHitEvent_Hook, __this, attackeeRuntimeID, attackResult);
	}
}
