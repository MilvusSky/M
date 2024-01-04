#include "LuaConsole.h"

namespace cheat {
    TextEditor editor;

    LuaConsole::LuaConsole() {
	editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
	editor.SetPalette(TextEditor::GetDarkPalette());

	editor.SetTabSize(4);
	editor.SetShowWhitespaces(false);
	editor.SetColorizerEnable(true);
    }

    void LuaConsole::GUI() {
	if (ImGui::Button("Execute") || h_Execute.IsPressed()) {
	    luahookfunc(editor.GetText().c_str());
	} ImGui::SameLine();
	h_Execute.Draw();

	editor.Render("Lua console");
    }

    void LuaConsole::Status() {

    }

    void LuaConsole::Outer() {
	if (h_Execute.IsPressed()) {
	    luahookfunc(editor.GetText().c_str());
	}
    }

    LuaConsole& LuaConsole::getInstance() {
	static LuaConsole instance;
	return instance;
    }

    std::string LuaConsole::getModule() {
	return _("Lua");
    }
}
