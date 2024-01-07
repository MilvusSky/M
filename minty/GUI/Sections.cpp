#include "../Functions/About/About.h"

#include "../Functions/Player/GodMode.h"
#include "../Functions/Player/InfiniteEnergy.h"
#include "../Functions/Player/InfiniteStamina.h"
#include "../Functions/Player/MultiHit.h"
#include "../Functions/Player/NoClip.h"
#include "../Functions/Player/NoCooldown.h"

#include "../Functions/Settings/Settings.h"

#include "../Functions/Visuals/CameraZoom.h"
#include "../Functions/Visuals/FovChanger.h"
#include "../Functions/Visuals/HideDamage.h"
#include "../Functions/Visuals/HideReaction.h"
#include "../Functions/Visuals/HideUI.h"
#include "../Functions/Visuals/NoFog.h"
#include "../Functions/Visuals/Peeking.h"
#include "../Functions/Visuals/ProfileChanger.h"
#include "../Functions/Visuals/ShowIndicators.h"
#include "../Functions/Visuals/UnlockFPS.h"
#include "../Functions/Visuals/GraphicsChanger.h"

#include "../Functions/Lua/LuaConsole.h"

#include "../Functions/World/PickupRange.h"
#include "../Functions/World/AutoTalk.h"
#include "../Functions/World/VacuumLoot.h"
#include "../Functions/World/CutsceneSkip.h"
#include "../Functions/World/DumbEnemies.h"
#include "../Functions/World/ElementalSight.h"
#include "../Functions/World/GameSpeed.h"
#include "../Functions/World/ESP.h"

//#include "../Functions/World/OpenTeamImmediately.h"
//#include "../Functions/World/AutoDestroy.h"
//#include "../Functions/World/AutoChallenge.h"
//#include "../Functions/World/AutoLoot.h"
//#include "../Functions/World/AutoTP.h"
//#include "../Functions/World/MobVacuum.h"

std::vector<std::string> ModuleOrder = {
    _("MODULE_PLAYER"),
    _("MODULE_WORLD"),
	_("MODULE_VISUALS"),
    _("MODULE_LUA"),
    _("MODULE_SETTINGS"),
    _("MODULE_ABOUT")
};

void Init() {
	// Player
	INIT_FUNC(GodMode);
	INIT_FUNC(InfiniteEnergy);
	INIT_FUNC(InfiniteStamina);
	INIT_FUNC(MultiHit);
	INIT_FUNC(NoClip);
	INIT_FUNC(NoCooldown);

	// World
	INIT_FUNC(CameraZoom);
	//INIT_FUNC(FovChanger);
	INIT_FUNC(GraphicsChanger);
	INIT_FUNC(HideDamage);
	INIT_FUNC(HideReaction);
	INIT_FUNC(HideUI);
	INIT_FUNC(NoFog);
	INIT_FUNC(Peeking);
	INIT_FUNC(ProfileChanger);
	INIT_FUNC(ShowIndicators);
	INIT_FUNC(UnlockFPS);

	// Lua
	INIT_FUNC(LuaConsole);

	// World
	INIT_FUNC(AutoTalk);
	INIT_FUNC(CutsceneSkip);
	INIT_FUNC(DumbEnemies);
	INIT_FUNC(ElementalSight);
	INIT_FUNC(GameSpeed);
	//INIT_FUNC(MobVacuum);
	INIT_FUNC(PickupRange);
	INIT_FUNC(VacuumLoot);

	INIT_FUNC(ESP);

	//INIT_FUNC(AutoLoot);
	//INIT_FUNC(AutoChallenge);
	//INIT_FUNC(AutoDestroy);
	//INIT_FUNC(OpenTeamImmediately);
	//INIT_FUNC(AutoTP);

	// Settings
	INIT_FUNC(Settings);

	// About
	INIT_FUNC(About);
}

void Outer() {
	for (auto& func : functions)
		func->Outer();
}

void Status() {
	auto& settings = cheat::Settings::getInstance();

	if (!settings.f_Status.getValue())
		return;

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing;

	if (!settings.f_StatusMove.getValue())
		flags |= ImGuiWindowFlags_NoMove;

	ImGui::Begin("Status", nullptr, flags);

	auto windowWidth = ImGui::GetWindowSize().x;
	auto& about = cheat::About::getInstance();
	std::string version = about.mVersion;

	ImGui::PushStyleColor(ImGuiCol_Text, { 0.17f, 0.63f, 0.45f, 1.00f });
	ImGui::Text("Minty-GI %s", version);
	ImGui::PopStyleColor();
	ImGui::Separator();
	for (auto& feature : functions)
		feature->Status();
	ImGui::End();
}


void DrawSection(const std::string& moduleName) {
	for (auto& func : functions) {
		if (func->getModule() != moduleName)
			continue;

		func->GUI();
	}
}
