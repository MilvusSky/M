#include "Settings.h"

namespace cheat {
    static void DrawFPS();

    Settings::Settings() {
        f_DisableProtection = config::getValue("functions:Settings", "disableProtection", true);
        f_DisableLog = config::getValue("functions:Settings", "disableLog", true);
        f_SpoofACResult = config::getValue("functions:Settings", "spoofACResult", true);
        f_UseSignature = config::getValue("functions:Settings", "useSignature", false);
        f_ShowFps = config::getValue("functions:Settings", "showFps", true);
	f_ShowRpc = config::getValue("functions:Settings", "showRpc", true);
	f_ShowConsole = config::getValue("functions:Settings", "showConsole", true);
        f_InitDelay = config::getValue("functions:Settings", "initDelay", 7000);
	f_Language = config::getValue("functions:Settings", "f_Language", 0);
	f_MobileMode = config::getValue("functions:Settings", "mobileMode", false);
        f_StartupArguments = config::getValue<std::string>("functions:Settings", "startupArguments", "");
	f_AnimationDuration = config::getValue("functions:Settings", "animationDuration", 0.2f);
	f_Status = config::getValue("functions:Settings", "status", true);
	f_StatusMove = config::getValue("functions:Settings", "statusMove", true);
        f_Hotkey = Hotkey("functions:Settings:Menu", VK_F12);
	f_HotkeyConsole= Hotkey("functions:Settings:Console", VK_HOME);
        f_ShowMenu = true;
    }

    Settings& Settings::getInstance() {
        static Settings instance;
        return instance;
    }
    const char* languages[] = { "English", "Russian", "Chinese", "Indonesian" };
    void RefreshMenu() {
      
      // 刷新菜单的逻辑
    }
    void Settings::GUI() {

	//更换语言
	ImGui::SeparatorText(_("language settings"));
	ConfigComboLanguage(f_Language);


        ImGui::SeparatorText("General");

	f_Hotkey.Draw(_("Show the Minty Menu."));

	ConfigCheckbox(_("Show console"), f_ShowConsole, _("Show/Hide console log window."));
	if (f_Status.getValue()) {
	    ImGui::Indent();
	    f_HotkeyConsole.Draw();
	    ImGui::Unindent();
	}

        ConfigCheckbox(_("Disable protection"), f_DisableProtection, _("Close anitcheat handle.\n(changes will take effect after relaunch)."));
        ConfigCheckbox(_("Disable analytic log"), f_DisableLog, _("Disable game telemetry and analytic log from spamming the console.\n"
            "(changes will take effect after relaunch)."));
        ConfigCheckbox(_("Spoof anticheat result"), f_SpoofACResult, _("Spoofs/Blocks anticheat reports made by WindSeedClientNotify.\n"
            "(changes will take effect after relaunch)."));
        ConfigCheckbox(_("Use predefined file signature"), f_UseSignature, _("Uses 'hardcoded' signature value for file check.\n"
            "Can be useful, when you put the additional executable files to game directory.\n"
            "And can't pass the 'Integrity check' on login.\n"
            "(changes will take effect after relaunch)."));

	ConfigCheckbox(_("Show status window"), f_Status, _("Shows a window with statements of enabled functions."));

	if (f_Status.getValue()) {
	    ImGui::Indent();
	    ConfigCheckbox(_("Move status window"), f_StatusMove);
	    ImGui::Unindent();
	}

        ConfigCheckbox(_("Show current FPS"), f_ShowFps, _("Shows the current FPS."));
        ConfigCheckbox(_("Show Discord RPC"), f_ShowRpc, _("Shows the Discord RPC.\n(changes will take effect after relaunch)."));

        ConfigSliderInt(_("Initialization delay (ms)"), f_InitDelay, 0, 60000,
	    _("Change delay before showing menu.\nMay cause lags while opening, so try to change this value in case."));

	ConfigCheckbox(_("mobileMode"), f_MobileMode, _("Using mobile platform touch screen mode\n""please restart."));

	ConfigInputText(_("Startup arguments"), f_StartupArguments, _("Launch the game with command line arguments.\n"
	    "(changes will take effect after relaunch)."));
        TextURL(_("List of unity command line arguments"), "https://docs.unity3d.com/Manual/PlayerCommandLineArguments.html", false, false);

        ImGui::SeparatorText(_("Theme"));

        static int themeIndex = 1;
        if (ImGui::RadioButton("Dark", &themeIndex, 1))
            setTheme(1);

        if (ImGui::RadioButton("Light", &themeIndex, 2))
            setTheme(2);

        ImGui::SeparatorText(_("Style"));

        static int styleIndex = 1;
        if (ImGui::RadioButton("Cozy", &styleIndex, 1))
            setStyle(1);

        if (ImGui::RadioButton("Cozy Squared", &styleIndex, 2))
            setStyle(2);

        ImGui::SeparatorText("Font");

        static int fontIndex = 0;
        if (ImGui::RadioButton("Normal", &fontIndex, 0))
            setFont(1);

        if (ImGui::RadioButton("Bold", &fontIndex, 1))
            setFont(2);

        ImGui::SeparatorText("Customize");
        ImGui::Checkbox(_("Show Style Editor"), &show_style_editor);
        ConfigSliderFloat("Duration of animation (s)", f_AnimationDuration, 0, 5.0f,
            "Window appearance animation duration.");
	}

    void Settings::Outer() {
        if (f_Hotkey.IsPressed())
            f_ShowMenu = !f_ShowMenu;

	if (f_HotkeyConsole.IsPressed())
	    f_ShowConsole.setValue(!f_ShowConsole.getValue());

	if (f_ShowConsole.getValue())
	    ShowWindow(GetConsoleWindow(), SW_SHOW);
	else
	    ShowWindow(GetConsoleWindow(), SW_HIDE);
	
        if (f_ShowFps.getValue())
            DrawFPS();

        if (show_style_editor) {
            ImGui::Begin("Style Editor", &show_style_editor);
            ImGui::ShowStyleEditor();
            ImGui::End();
        }
    }

    std::string Settings::getModule() {
        return _("Settings");
    }

    void DrawFPS() {
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

        ImGui::Begin("##FPS", NULL, flags);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::End();
    }
}
