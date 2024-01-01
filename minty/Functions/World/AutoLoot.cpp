#include "AutoLoot.h"

namespace cheat {
    static void LCSelectPickup_AddInteeBtnByID_Hook(void* __this, app::BaseEntity* entity, app::MethodInfo* method);
    int amountOfItems = 0;

    void PressKey(char key) {
	auto autoLoot = AutoLoot::getInstance();
	Sleep(autoLoot.f_Delay.getValue());

	INPUT inputs[2] = {};
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = key;

	Sleep(50);

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = key;
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    }

    void PressKeyThread(char key) {
	while (true) {
	    Sleep(100);
	    for (int i = 0; i < amountOfItems; i++) {
		PressKey(key);
		amountOfItems--;
	    }
	}
    }

    AutoLoot::AutoLoot() {
	f_Enabled = config::getValue("functions:AutoLoot", "enabled", false);
	f_Delay = config::getValue("functions:AutoLoot", "delay", 150);
	f_Hotkey = Hotkey("functions:AutoLoot");
	HookManager::install(app::MoleMole_LCSelectPickup_AddInteeBtnByID, LCSelectPickup_AddInteeBtnByID_Hook);

	std::thread(PressKeyThread, 'F').detach();
    }

    AutoLoot& AutoLoot::getInstance() {
	static AutoLoot instance;
	return instance;
    }

    void AutoLoot::GUI() {
	ConfigCheckbox(_("Auto Loot"), f_Enabled, _("Automatically presses F when item pickup button is aviable. It is just kind of macro, so missclicks are possible."));

	if (f_Enabled.getValue()) {
	    ImGui::Indent();
	    ConfigSliderInt(_("Delay (ms)"), f_Delay, 0, 3000, _("Delay in/between clicks (in miliseconds)."));
	    f_Hotkey.Draw();
	    ImGui::Unindent();
	}
    }

    void AutoLoot::Status() {
	if (f_Enabled.getValue())
	    ImGui::Text(_("Auto Loot"));
    }

    void AutoLoot::Outer() {
	if (f_Hotkey.IsPressed())
	    f_Enabled.setValue(!f_Enabled.getValue());
    }

    std::string AutoLoot::getModule() {
	return _("World");
    }

    static void LCSelectPickup_AddInteeBtnByID_Hook(void* __this, app::BaseEntity* entity, app::MethodInfo* method)
    {
	auto autoLoot = AutoLoot::getInstance();
	CALL_ORIGIN(LCSelectPickup_AddInteeBtnByID_Hook, __this, entity, method);

	if (autoLoot.f_Enabled.getValue()) 
	    amountOfItems++;
    }
}
