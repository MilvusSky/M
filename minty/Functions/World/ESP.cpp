#include "ESP.h"

namespace cheat {
    ImVec4 color;

    void GameManager_Update_h(app::GameManager* this_, app::MethodInfo* mi);

    ESP::ESP() {
	HookManager::install(app::GameManager_Update, GameManager_Update_h);
    }

    void ESP::GUI() {

    }

    void ESP::Outer() {

    }

    void ESP::Status() {

    }

    ESP& ESP::getInstance() {
	static ESP instance;
	return instance;
    }

    std::string ESP::getModule() {
	return _("World");
    }

    void GameManager_Update_h(app::GameManager* this_, app::MethodInfo* mi) {
	return CALL_ORIGIN(GameManager_Update_h, this_, mi);
    };
}
