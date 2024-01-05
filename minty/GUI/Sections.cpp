#include "../functions/about/About.h"

#include "../functions/player/GodMode.h"
#include "../functions/player/InfiniteEnergy.h"
#include "../functions/player/InfiniteStamina.h"
#include "../functions/player/MultiHit.h"
#include "../functions/player/NoClip.h"
#include "../functions/player/NoCooldown.h"

#include "../functions/settings/Settings.h"

#include "../functions/visuals/CameraZoom.h"
#include "../functions/visuals/FovChanger.h"
#include "../functions/visuals/HideDamage.h"
#include "../functions/visuals/HideReaction.h"
#include "../functions/visuals/HideUI.h"
#include "../functions/visuals/NoFog.h"
#include "../functions/visuals/Peeking.h"
#include "../functions/visuals/ProfileChanger.h"
#include "../functions/visuals/ShowIndicators.h"
#include "../functions/visuals/UnlockFPS.h"
#include "../functions/visuals/GraphicsChanger.h"

#include "../Functions/Lua/LuaConsole.h"

#include "../functions/world/AutoLoot.h"
#include "../functions/world/AutoTalk.h"
//#include "../functions/world/MobVacuum.h"
#include "../functions/world/VacuumLoot.h"
//#include "../functions/world/AutoDestroy.h"
//#include "../functions/world/AutoChallenge.h"
//#include "../functions/world/AutoDestroy.h"
//#include "../functions/world/AutoLoot.h"
#include "../functions/world/AutoTalk.h"
//#include "../functions/world/AutoTP.h"
#include "../functions/world/CutsceneSkip.h"
#include "../functions/world/DumbEnemies.h"
#include "../functions/world/ElementalSight.h"
#include "../functions/world/GameSpeed.h"
//#include "../functions/world/MobVacuum.h"
//#include "../functions/world/OpenTeamImmediately.h"
//#include "../functions/world/VacuumLoot.h"
#include "../Functions/World/ESP.h"

#include "../functions/World/ESP.h"


std::vector<std::string> ModuleOrder = {
    _("MODULE_PLAYER"),
    _("MODULE_WORLD"),
    _("MODULE_VISUALS"),
    _("MODULE_LUA"),
    _("MODULE_SETTINGS"),
    _("MODULE_ABOUT")
};

void Init() {
	INIT_FUNC(About);

	INIT_FUNC(GodMode);
	INIT_FUNC(InfiniteEnergy);
	INIT_FUNC(InfiniteStamina);
	INIT_FUNC(MultiHit);
	INIT_FUNC(NoClip);
	INIT_FUNC(NoCooldown);

	INIT_FUNC(Settings);

  INIT_FUNC(CameraZoom);
  //INIT_FUNC(FovChanger);
  INIT_FUNC(HideDamage);
  INIT_FUNC(HideReaction);
  INIT_FUNC(HideUI);
  INIT_FUNC(NoFog);
  INIT_FUNC(Peeking);
  INIT_FUNC(ProfileChanger);
  INIT_FUNC(ShowIndicators);
  INIT_FUNC(UnlockFPS);
  INIT_FUNC(GraphicsChanger);

  //INIT_FUNC(PickupRange);
  INIT_FUNC(AutoLoot);
  //INIT_FUNC(AutoChallenge);
  //INIT_FUNC(MobVacuum);
  //INIT_FUNC(AutoDestroy);
  INIT_FUNC(AutoTalk);
  //INIT_FUNC(AutoTP);
  INIT_FUNC(CutsceneSkip);
  INIT_FUNC(DumbEnemies);
  INIT_FUNC(ElementalSight);
  INIT_FUNC(GameSpeed);
  //INIT_FUNC(OpenTeamImmediately);
  //INIT_FUNC(SkipEnhanceAnimation);
  INIT_FUNC(VacuumLoot);

  INIT_FUNC(ESP);
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
	//std::string text = "Minty-GI " + about.getVersion();
	std::string text = "Status";
	auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::PushStyleColor(ImGuiCol_Text, { 0.0f / 255, 142.0f / 255, 85.0f / 255, 1.0f });
	ImGui::Text("%s", text);
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
