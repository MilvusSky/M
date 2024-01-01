#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
    class PickupRange : public Function {
    public:
	ConfigField<bool> f_Enabled;
	ConfigField<float> f_CustomRange;

	Hotkey f_Hotkey;

	void GUI() override;
	void Outer() override;
	void Status() override;

	std::string getModule() override;

	static PickupRange& getInstance();
	bool isTeleportHotkeyPressed;

	PickupRange();
    };
}
