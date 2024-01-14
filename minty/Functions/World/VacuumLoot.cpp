#include "VacuumLoot.h"

const char* entityTypeToString(app::EntityType__Enum_1 type) {
	switch (type) {
	case app::EntityType__Enum_1::None: return "None";
	case app::EntityType__Enum_1::Avatar: return "Avatar";
	case app::EntityType__Enum_1::Monster: return "Monster";
	case app::EntityType__Enum_1::Bullet: return "Bullet";
	case app::EntityType__Enum_1::AttackPhyisicalUnit: return "AttackPhyisicalUnit";
	case app::EntityType__Enum_1::AOE: return "AOE";
	case app::EntityType__Enum_1::Camera: return "Camera";
	case app::EntityType__Enum_1::EnviroArea: return "EnviroArea";
	case app::EntityType__Enum_1::Equip: return "Equip";
	case app::EntityType__Enum_1::MonsterEquip: return "MonsterEquip";
	case app::EntityType__Enum_1::Grass: return "Grass";
	case app::EntityType__Enum_1::Level: return "Level";
	case app::EntityType__Enum_1::NPC: return "NPC";
	case app::EntityType__Enum_1::TransPointFirst: return "TransPointFirst";
	case app::EntityType__Enum_1::TransPointFirstGadget: return "TransPointFirstGadget";
	case app::EntityType__Enum_1::TransPointSecond: return "TransPointSecond";
	case app::EntityType__Enum_1::TransPointSecondGadget: return "TransPointSecondGadget";
	case app::EntityType__Enum_1::DropItem: return "DropItem";
	case app::EntityType__Enum_1::Field: return "Field";
	case app::EntityType__Enum_1::Gadget: return "Gadget";
	case app::EntityType__Enum_1::Water: return "Water";
	case app::EntityType__Enum_1::GatherPoint: return "GatherPoint";
	case app::EntityType__Enum_1::GatherObject: return "GatherObject";
	case app::EntityType__Enum_1::AirflowField: return "AirflowField";
	case app::EntityType__Enum_1::SpeedupField: return "SpeedupField";
	case app::EntityType__Enum_1::Gear: return "Gear";
	case app::EntityType__Enum_1::Chest: return "Chest";
	case app::EntityType__Enum_1::EnergyBall: return "EnergyBall";
	case app::EntityType__Enum_1::ElemCrystal: return "ElemCrystal";
	case app::EntityType__Enum_1::Timeline: return "Timeline";
	case app::EntityType__Enum_1::Worktop: return "Worktop";
	case app::EntityType__Enum_1::Team: return "Team";
	case app::EntityType__Enum_1::Platform: return "Platform";
	case app::EntityType__Enum_1::AmberWind: return "AmberWind";
	case app::EntityType__Enum_1::EnvAnimal: return "EnvAnimal";
	case app::EntityType__Enum_1::SealGadget: return "SealGadget";
	case app::EntityType__Enum_1::Tree: return "Tree";
	case app::EntityType__Enum_1::Bush: return "Bush";
	case app::EntityType__Enum_1::QuestGadget: return "QuestGadget";
	case app::EntityType__Enum_1::Lightning: return "Lightning";
	case app::EntityType__Enum_1::RewardPoint: return "RewardPoint";
	case app::EntityType__Enum_1::RewardStatue: return "RewardStatue";
	case app::EntityType__Enum_1::MPLevel: return "MPLevel";
	case app::EntityType__Enum_1::WindSeed: return "WindSeed";
	case app::EntityType__Enum_1::MpPlayRewardPoint: return "MpPlayRewardPoint";
	case app::EntityType__Enum_1::ViewPoint: return "ViewPoint";
	case app::EntityType__Enum_1::RemoteAvatar: return "RemoteAvatar";
	case app::EntityType__Enum_1::GeneralRewardPoint: return "GeneralRewardPoint";
	case app::EntityType__Enum_1::PlayTeam: return "PlayTeam";
	case app::EntityType__Enum_1::OfferingGadget: return "OfferingGadget";
	case app::EntityType__Enum_1::EyePoint: return "EyePoint";
	case app::EntityType__Enum_1::MiracleRing: return "MiracleRing";
	case app::EntityType__Enum_1::Foundation: return "Foundation";
	case app::EntityType__Enum_1::WidgetGadget: return "WidgetGadget";
	case app::EntityType__Enum_1::Vehicle: return "Vehicle";
	case app::EntityType__Enum_1::DangerZone: return "DangerZone";
	case app::EntityType__Enum_1::EchoShell: return "EchoShell";
	case app::EntityType__Enum_1::HomeGatherObject: return "HomeGatherObject";
	case app::EntityType__Enum_1::Projector: return "Projector";
	case app::EntityType__Enum_1::Screen: return "Screen";
	case app::EntityType__Enum_1::CustomTile: return "CustomTile";
	case app::EntityType__Enum_1::FishPool: return "FishPool";
	case app::EntityType__Enum_1::FishRod: return "FishRod";
	case app::EntityType__Enum_1::CustomGadget: return "CustomGadget";
	case app::EntityType__Enum_1::RoguelikeOperatorGadget: return "RoguelikeOperatorGadget";
	case app::EntityType__Enum_1::ActivityInteractGadget: return "ActivityInteractGadget";
	case app::EntityType__Enum_1::BlackMud: return "BlackMud";
	case app::EntityType__Enum_1::SubEquip: return "SubEquip";
	case app::EntityType__Enum_1::UIInteractGadget: return "UIInteractGadget";
	case app::EntityType__Enum_1::NightCrowGadget: return "NightCrowGadget";
	case app::EntityType__Enum_1::Partner: return "Partner";
	case app::EntityType__Enum_1::DeshretObeliskGadget: return "DeshretObeliskGadget";
	case app::EntityType__Enum_1::CoinCollectLevelGadget: return "CoinCollectLevelGadget";
	case app::EntityType__Enum_1::UgcSpecialGadget: return "UgcSpecialGadget";
	case app::EntityType__Enum_1::UgcTowerLevelUpGadget: return "UgcTowerLevelUpGadget";
	case app::EntityType__Enum_1::JourneyGearOperatorGadget: return "JourneyGearOperatorGadget";
	case app::EntityType__Enum_1::CurveMoveGadget: return "CurveMoveGadget";
	case app::EntityType__Enum_1::PlaceHolder: return "PlaceHolder";
	default: return "Unknown";
	}
}

namespace cheat
{
	struct VacuumLootFilter {
		std::string name;
		bool enabled;
		game::SimpleFilter simpleFilter;

		explicit operator bool() const {
			return name != "Empty";
		}
	};

	std::vector<VacuumLootFilter> filters;

	void AddVacuumLootFilter(std::string name, std::string path, game::SimpleFilter filter) {
		std::string key = util::FirstCharToLowercase(name);
		auto value = config::getValue(path, key, false);
		filters.push_back({ name, value.getValue(), filter });
	}

	void GameManager_Update_VacuumLoot_Hook(app::GameManager* __this, app::MethodInfo* method);

	VacuumLoot::VacuumLoot() {
		f_Enabled = config::getValue("functions:VacuumLoot", "enabled", false);
		f_Distance = config::getValue("functions:VacuumLoot", "distance", 1.5f);
		f_Radius = config::getValue("functions:VacuumLoot", "radius", 20.f);
		f_Hotkey = Hotkey("functions:VacuumLoot");

		/*
		Filters
		Write names in the format "SomeEntityName" to save them in the config as
		"someEntityName" and for the name in the game as "Some entity name"
		*/
		AddVacuumLootFilter("Ores", "functions:VacuumLoot:filters", game::filters::combined::Ores);
		AddVacuumLootFilter("Plants", "functions:VacuumLoot:filters", game::filters::combined::Plants);
		AddVacuumLootFilter("Items", "functions:VacuumLoot:filters", game::filters::featured::ItemDrops); // combined::AllPickableLoot instead of featured::ItemDrops, idk why its not workin
		AddVacuumLootFilter("Oculuses", "functions:VacuumLoot:filters", game::filters::combined::Oculies);

		entityManager = &game::EntityManager::getInstance();

		HookManager::install(app::GameManager_Update, GameManager_Update_VacuumLoot_Hook);
	}

	VacuumLoot& VacuumLoot::getInstance()
	{
		static VacuumLoot instance;
		return instance;
	}

	void VacuumLoot::GUI()
	{
		ConfigCheckbox(_("Vacuum loot"), f_Enabled, _("Vacuum of various entities to the character"));
		if (f_Enabled.getValue()) {
			ImGui::Indent();

			ConfigSliderFloat("Radius (m)", f_Radius, 0.1f, 100.0f, _("Radius of common loot vacuum."));
			ConfigSliderFloat("Distance (m)", f_Distance, 1.f, 10.0f, _("Distance between the player and the loot.\n"
				"Values under 1.5 may be too intruding."));

			if (BeginGroupPanel("Filters", true)) {
				for (VacuumLootFilter& filter : filters) {
					auto name = util::ConvertToWords(filter.name);
					ImGui::Checkbox(name.c_str(), &filter.enabled);
					std::string key = util::FirstCharToLowercase(filter.name);
					config::setValue("functions:VacuumLoot:filters", key, filter.enabled);
				}
			}
			EndGroupPanel();

			f_Hotkey.Draw();
			
			ImGui::Unindent();
		}
	}

	void VacuumLoot::Status()
	{
		if (f_Enabled.getValue())
			ImGui::Text("VacuumLoot[%.01fm|%.01fm]",
				f_Delay.getValue(),
				f_Radius.getValue(),
				f_Distance.getValue()
			);
	}

	std::string VacuumLoot::getModule() {
		return _("World");	
	}

	void VacuumLoot::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	VacuumLootFilter FilterEntity(game::Entity entity) {
		auto vacuumLoot = VacuumLoot::getInstance();

		for (VacuumLootFilter& filter : filters) {
			if (filter.simpleFilter.IsValid(&entity) and filter.enabled)
				return filter;
		}

		return { "Empty", false, game::filters::Empty };
	}

	void GameManager_Update_VacuumLoot_Hook(app::GameManager* __this, app::MethodInfo* method)
	{
		auto vacuumLoot = VacuumLoot::getInstance();
		auto avatarEntity = vacuumLoot.entityManager->avatar();

		if (!vacuumLoot.f_Enabled.getValue())
			return CALL_ORIGIN(GameManager_Update_VacuumLoot_Hook, __this, method);

		for (const auto& entity : vacuumLoot.entityManager->entities())
		{
			if (avatarEntity->distance(entity) > vacuumLoot.f_Radius.getValue())
				continue;

			// some debug logs for adding filters manualy
			// LOG_DEBUG("%s", entity->name().c_str());
			// const char* entityString = entityTypeToString(entity->type());
			// LOG_DEBUG("type: %s", entityString);

			if (FilterEntity(*entity))
				entity->setRelativePosition(avatarEntity->relativePosition() + avatarEntity->forward() * vacuumLoot.f_Distance.getValue());
		}
		// LOG_DEBUG("");

		return CALL_ORIGIN(GameManager_Update_VacuumLoot_Hook, __this, method);
	}
}
