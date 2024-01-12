#include "VacuumLoot.h"

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

	/*
	The first parameter is a name for the entity and at the same time a key to save the filter status in the config.
	Second - path to the place where the filter value will be saved.
	Third - the filter itself(see game/filters.h).
	*/
	void AddVacuumLootFilter(std::string name, std::string path, game::SimpleFilter filter) {
		std::string key = util::FirstCharToLowercase(name);
		auto value = config::getValue(path, key, false);
		filters.push_back({ name, value.getValue(), filter });
	}

	void GameManager_Update_VacuumLoot_Hook(app::GameManager* __this, app::MethodInfo* method);

	VacuumLoot::VacuumLoot() {
		f_Enabled = config::getValue("functions:VacuumLoot", "enabled", false);
		f_Delay = config::getValue("functions:VacuumLoot", "delay", 1000);
		f_Distance = config::getValue("functions:VacuumLoot", "distance", 1.5f);
		f_Radius = config::getValue("functions:VacuumLoot", "radius", 20.f);
		f_Hotkey = Hotkey("functions:VacuumLoot");

		/*
		Filters
		Write names in the format "SomeEntityName" to save them in the config as
		"someEntityName" and for the name in the game as "Some entity name"
		*/
		AddVacuumLootFilter("Ore", "functions:VacuumLoot:filters", game::filters::combined::Ores);
		AddVacuumLootFilter("Plant", "functions:VacuumLoot:filters", game::filters::combined::Plants);
		AddVacuumLootFilter("Item", "functions:VacuumLoot:filters", game::filters::featured::ItemDrops);
		//AddVacuumLootFilter("Item", "functions:VacuumLoot:filters", game::filters::combined::AllPickableLoot); // idk why its not workin
		AddVacuumLootFilter("Oculus", "functions:VacuumLoot:filters", game::filters::combined::Oculies);

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
			ConfigSliderInt("Delay Time (ms)", f_Delay, 1, 1000, _("Delay (in ms) between loot vacuum."));
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
			ImGui::Text("VacuumLoot\n[%dms|%.01fm|%.01fm]",
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
		auto currentTime = util::GetCurrentTimeMillisec();
		auto vacuumLoot = VacuumLoot::getInstance();
		if (currentTime < vacuumLoot.nextTime || !vacuumLoot.f_Enabled.getValue()) 
			return CALL_ORIGIN(GameManager_Update_VacuumLoot_Hook, __this, method);

		auto& manager = game::EntityManager::getInstance();
		auto avatarEntity = manager.avatar();

		for (const auto& entity : manager.entities())
		{
			if (manager.avatar()->distance(entity) > vacuumLoot.f_Radius.getValue() and !entity->isAvatar())
				continue;

			LOG_DEBUG("%s", entity->name().c_str());

			VacuumLootFilter data = FilterEntity(*entity);
			if (data) 
				entity->setRelativePosition(avatarEntity->relativePosition() + avatarEntity->forward() * vacuumLoot.f_Distance.getValue());
			
		}
		LOG_DEBUG("GM ITERATION END");
		LOG_DEBUG("");

		vacuumLoot.nextTime = currentTime + vacuumLoot.f_Delay.getValue();

		return CALL_ORIGIN(GameManager_Update_VacuumLoot_Hook, __this, method);
	}
}
