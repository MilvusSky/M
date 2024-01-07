#include "PickupRange.h"

namespace cheat {
	static bool LCSelectPickup_IsInPosition_Hook(void* __this, app::BaseEntity* entity, app::MethodInfo* method);
	static bool LCSelectPickup_IsOutPosition_Hook(void* __this, app::BaseEntity* entity, app::MethodInfo* method);

	float g_default_range = 3.0f;

	PickupRange::PickupRange() {
		f_Enabled = config::getValue("functions:ItemTeleport", "enabled", false);
		f_CustomRange = config::getValue("functions:ItemTeleport", "range", g_default_range);
		f_Hotkey = Hotkey("functions:ItemTeleport");

		HookManager::install(app::MoleMole_LCSelectPickup_IsInPosition, LCSelectPickup_IsInPosition_Hook);
		HookManager::install(app::MoleMole_LCSelectPickup_IsOutPosition, LCSelectPickup_IsOutPosition_Hook);
	}

	PickupRange& PickupRange::getInstance() {
		static PickupRange instance;
		return instance;
	}

	void PickupRange::GUI() {
		ConfigCheckbox(_("Custom Pickup Range"), f_Enabled, _("Enable custom pickup range."));
		if (f_Enabled.getValue()) {
			ImGui::Indent();
			ConfigSliderFloat(_("Range (m)"), f_CustomRange, 0.1f, 40.0f, _("Modifies pickup/open range to this value (in meters)."));
			f_Hotkey.Draw();
			ImGui::Unindent();
		}	
	}
	void PickupRange::Status() {
		if (f_Enabled.getValue())
			ImGui::Text(_("Pickup range"));
	}

	void PickupRange::Outer() {
		if (f_Hotkey.IsPressed())
			f_Enabled.setValue(!f_Enabled.getValue());
	}

	std::string PickupRange::getModule() {
		return _("World");
	}

	void OnCheckIsInPosition(bool& result, app::BaseEntity* entity)
	{
		PickupRange& pickupRange = PickupRange::getInstance();
		auto& manager = game::EntityManager::getInstance();

		float distance = pickupRange.f_Enabled.getValue() ? pickupRange.f_CustomRange.getValue() : g_default_range;

		result = manager.avatar()->distance(entity) < distance;
	}

	static bool LCSelectPickup_IsInPosition_Hook(void* __this, app::BaseEntity* entity, app::MethodInfo* method)
	{
		bool result = CALL_ORIGIN(LCSelectPickup_IsInPosition_Hook, __this, entity, method);

		OnCheckIsInPosition(result, entity);

		return result;
	}

	static bool LCSelectPickup_IsOutPosition_Hook(void* __this, app::BaseEntity* entity, app::MethodInfo* method)
	{
		bool result = CALL_ORIGIN(LCSelectPickup_IsOutPosition_Hook, __this, entity, method);

		OnCheckIsInPosition(result, entity);

		return result;
	}
}