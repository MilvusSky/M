#include "../../api/lua/luahook.hpp"
#include "../../api/imgui/ImGui/imgui.h"
#include "../FunctionIncludes.h"
#include "../../api/imgui/TextEditor/TextEditor.h"

namespace cheat {
    class LuaConsole : public Function {
    public:
	Hotkey h_Execute;

	virtual void GUI() override;
	virtual void Outer() override;
	virtual void Status() override;

	std::string getModule() override;

	static LuaConsole& getInstance();

	LuaConsole();
    };
}
