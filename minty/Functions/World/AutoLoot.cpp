#include "AutoLoot.h"

namespace cheat {
	static void LCSelectPickup_AddInteeBtnByID_Hook(void* __this, app::BaseEntity* entity, app::MethodInfo* method);
	void OnAutoLoot();
	void GameManager_Update_AutoLootHook(app::GameManager* __this, app::MethodInfo* method);

	app::MoleMole_ItemModule* ItemModule;
	SafeQueue<uint32_t> toBeLootedItems;
	int64_t nextLootTime;

	AutoLoot::AutoLoot() {
		f_Enabled = config::getValue("functions:AutoLoot", "enabled", false);

		f_Hotkey = Hotkey("functions:AutoLoot");

		HookManager::install(app::GameManager_Update, GameManager_Update_AutoLootHook);
		HookManager::install(app::MoleMole_LCSelectPickup_AddInteeBtnByID, LCSelectPickup_AddInteeBtnByID_Hook);
	}

	AutoLoot& AutoLoot::getInstance() {
		static AutoLoot instance;
		return instance;
	}

	void AutoLoot::GUI() {
		ConfigCheckbox(_("Auto loot"), f_Enabled, _("AutoLoot"));

		if (f_Enabled.getValue()) {
			ImGui::Indent();

			if (ImGui::BeginTable(_("AutoLootDrawTable"), 2, ImGuiTableFlags_NoBordersInBody)) {
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);

				BeginGroupPanel("Auto-Pickup");
				{
					ConfigCheckbox(_("Enabled"), f_AutoPickup, _("Automatically picks up dropped items.\n" \
						"Note: Using this with custom range and low delay times is extremely risky.\n" \
						"Abuse will definitely merit a ban.\n\n" \
						"If using with custom range, make sure this is turned on FIRST."));
					ImGui::SameLine();
					ImGui::TextColored(ImColor(255, 165, 0, 255), "Read the note!");
				}
				EndGroupPanel();

				BeginGroupPanel(_("Custom Pickup Range"));
				{
					ConfigCheckbox(_("Enabled"), f_UseCustomRange, _("Enable custom pickup range.\n" \
						"High values are not recommended, as it is easily detected by the server.\n\n" \
						"If using with auto-pickup/auto-treasure, turn this on LAST."));
					ImGui::SameLine();
					ImGui::TextColored(ImColor(255, 165, 0, 255), "Read the note!");
					ImGui::SetNextItemWidth(100.0f);
					ConfigSliderFloat(_("Range (m)"), f_CustomRange, 0.1f, 40.0f, _("Modifies pickup/open range to this value (in meters)."));
				}
				EndGroupPanel();

				BeginGroupPanel("Looting Speed");
				{
					ImGui::SetNextItemWidth(100.0f);
					ConfigSliderInt(_("Delay Time (ms)"), f_DelayTime, 1, 1000, _("Delay (in ms) between loot/open actions.\n" \
						"Values under 200ms are unsafe.\nNot used if no auto-functions are on."));
				}
				EndGroupPanel();

				BeginGroupPanel("Looting delay fluctuation");
				{
					ConfigCheckbox(_("Enabled"), f_UseDelayTimeFluctuation, _("Enable delay fluctuation.\n" \
						"Simulates human clicking delay as manual clickling never consistent."));
					ImGui::SameLine();
					ImGui::TextColored(ImColor(255, 165, 0, 255), "Read the note!");
					ImGui::SetNextItemWidth(100.0f);
					ConfigSliderInt(_("Delay range +(ms)"), f_DelayTimeFluctuation, 1, 1000, _("Delay randomly fluctuates between 'Delay Time'+'Delay Time+range'"));
				}
				EndGroupPanel();

				ImGui::TableSetColumnIndex(1);
				BeginGroupPanel("Auto-Treasure");
				{
					ConfigCheckbox(_("Enabled"), f_AutoTreasure, _("Automatically opens chests and other treasures.\n" \
						"Note: Using this with custom range and low delay times is extremely risky.\n" \
						"Abuse will definitely merit a ban.\n\n" \
						"If using with custom range, make sure this is turned on FIRST."));
					ImGui::SameLine();
					ImGui::TextColored(ImColor(255, 165, 0, 255), "Read the note!");
					ImGui::Indent();
					ConfigCheckbox(_("Chests"), f_Chest, _("Common, precious, luxurious, etc."));
					ConfigCheckbox(_("Leyline"), f_Leyline, _("Mora/XP, overworld/Trounce bosses, etc."));
					ConfigCheckbox(_("Search Points"), f_Investigate, _("Marked as Investigate/Search, etc."));
					ConfigCheckbox(_("Quest Interacts"), f_QuestInteract, _("Valid quest interact points."));
					ConfigCheckbox(_("Others"), f_Others, _("Book Pages, Spincrystals, etc."));
					ImGui::Unindent();
				}
				EndGroupPanel();
				ImGui::EndTable();
			}

			BeginGroupPanel("Pickup Filter");
			{
				ConfigCheckbox(_("Enabled"), f_PickupFilter, _("Enable pickup filter.\n"));
				ConfigCheckbox(_("Animals"), f_PickupFilter_Animals, _("Fish, Lizard, Frog, Flying animals.")); ImGui::SameLine();
				ConfigCheckbox(_("Drop Items"), f_PickupFilter_DropItems, _("Material, Mineral, Artifact.")); ImGui::SameLine();
				ConfigCheckbox(_("Resources"), f_PickupFilter_Resources, _("Everything beside Animals and Drop Items (Plants, Books, etc).")); ImGui::SameLine();
				ConfigCheckbox(_("Oculus"), f_PickupFilter_Oculus, _("Filter Oculus"));
			}
			EndGroupPanel();

			f_Hotkey.Draw();

			ImGui::Unindent();
		}
	}

	void AutoLoot::Status() {
		if (f_Enabled.getValue())
			ImGui::Text(_("Item teleport"));
	}

	void AutoLoot::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	std::string AutoLoot::getModule() {
		return _("World");
	}

	void GameManager_Update_AutoLootHook(app::GameManager* __this, app::MethodInfo* method) {
		AutoLoot& autoLoot = AutoLoot::getInstance();

		if (autoLoot.f_Enabled.getValue())
			OnAutoLoot();

		CALL_ORIGIN(GameManager_Update_AutoLootHook, __this, method);
	}

	void OnAutoLoot() {
		AutoLoot& autoLoot = AutoLoot::getInstance();
		auto currentTime = util::GetCurrentTimeMillisec();

		if (currentTime < nextLootTime)
			return;

		auto entityManager = app::MoleMole_InLevelDrumPageContext_get_ENTITY(nullptr);

		if (entityManager == nullptr)
			return;

		if (autoLoot.f_AutoTreasure.getValue()) {
			auto& manager = game::EntityManager::getInstance();

			for (auto& entity : manager.entities(game::filters::combined::Chests)) {
				auto chest = reinterpret_cast<game::Chest*>(entity);
				auto chestType = chest->itemType();

				if (!autoLoot.f_Investigate.getValue() && chestType == game::Chest::ItemType::Investigate)
					continue;

				if (!autoLoot.f_QuestInteract.getValue() && chestType == game::Chest::ItemType::QuestInteract)
					continue;

				if (!autoLoot.f_Others.getValue() && (
					chestType == game::Chest::ItemType::BGM ||
					chestType == game::Chest::ItemType::BookPage))
					continue;

				if (!autoLoot.f_Leyline.getValue() && chestType == game::Chest::ItemType::Flora)
					continue;

				if (chestType == game::Chest::ItemType::Chest) {
					if (!autoLoot.f_Chest.getValue())
						continue;
				}

				uint32_t entityId = entity->runtimeID();
				toBeLootedItems.push(entityId);
			}
		}

		auto entityId = toBeLootedItems.pop();

		if (!entityId || ItemModule == nullptr)
			return;

		auto entity = app::MoleMole_EntityManager_GetValidEntity(entityManager, *entityId);

		if (entity == nullptr)
			return;

		app::MoleMole_ItemModule_PickItem(ItemModule, *entityId, nullptr);

		int fluctuation = 0;

		if (autoLoot.f_UseDelayTimeFluctuation.getValue())
			fluctuation = std::rand() % (autoLoot.f_DelayTimeFluctuation.getValue() + 1);
		nextLootTime = currentTime + (int)autoLoot.f_DelayTime.getValue() + fluctuation;

	}


	bool OnCreateButton(app::BaseEntity* entity) {
		AutoLoot& autoLoot = AutoLoot::getInstance();

		if (!autoLoot.f_AutoPickup.getValue())
			return false;

		auto entityId = entity->fields._runtimeID_k__BackingField;

		if (autoLoot.f_DelayTime.getValue() == 0) {
			LOG_DEBUG("trying to pick item");
			app::MoleMole_ItemModule_PickItem(ItemModule, entityId, nullptr);
			LOG_DEBUG("picked up");
			return true;
		}

		toBeLootedItems.push(entityId);
		return false;
	}

	static void LCSelectPickup_AddInteeBtnByID_Hook(void* __this, app::BaseEntity* entity, app::MethodInfo* method) {
		bool canceled = OnCreateButton(entity);

		if (!canceled)
			CALL_ORIGIN(LCSelectPickup_AddInteeBtnByID_Hook, __this, entity, method);
	}
}
