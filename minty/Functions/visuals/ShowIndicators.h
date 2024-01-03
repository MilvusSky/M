#pragma once

#include "../FunctionIncludes.h"

namespace cheat {
    class ShowIndicators : public Function {
    public:
	ConfigField<bool> f_Enabled;
	ConfigField<bool> f_ShowWaypoints;
	ConfigField<bool> f_ShowChests;

	Hotkey f_Hotkey;

	void GUI() override;
	void Outer() override;
	void Status() override;

	std::string getModule() override;

	static ShowIndicators& getInstance();

	ShowIndicators();
    };
}
