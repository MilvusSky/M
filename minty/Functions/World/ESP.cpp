#include "ESP.h"

namespace cheat {
    ESPBase::ESPDrawInfo drawInfo;
    std::vector<ESPBase::Filter> v_Filters;

    void GameManager_Update_h(app::GameManager* this_, app::MethodInfo* mi);

    ESP::ESP() {
        b_Enabled = config::getValue("functions:ESP", "enabled", false);

        c_Color = config::getValue<std::vector<float>>("functions:ESP:DrawInfo", "color", { 1, 1, 1, 1 });
        i_OutlineType = config::getValue("functions:ESP:DrawInfo", "DrawType", 2);
        f_OutlineWidth = config::getValue("functions:ESP:DrawInfo", "OutlineWidth", 10.f);
        b_TracerEnabled = config::getValue("functions:ESP:DrawInfo", "Tracer", true);
        f_TracerWidth = config::getValue("functions:ESP:DrawInfo", "TracerWidth", 5.f);

        drawInfo.color = { c_Color.getValue()[0], c_Color.getValue()[1], c_Color.getValue()[2], c_Color.getValue()[3] };
        drawInfo.drawMode = i_OutlineType.getValue();
        drawInfo.outlineWidth = f_OutlineWidth.getValue();
        drawInfo.tracerEnabled = b_TracerEnabled.getValue();
        drawInfo.tracerWidth = f_TracerWidth.getValue();

        v_Filters = config::getValue<std::vector<std::tuple<int, bool, std::string>>>("functions:ESP", "filters", {
            // Chests
            { 0, false, "Common chest" },
            { 1, false, "Exquisite chest" },
            { 2, false, "Precious chest" },
            { 3, false, "Luxurious chest" },
            { 4, false, "Remarkable chest" },
            { 5, false, "Buried chest" },
            // Environment
            { 6, false, "TP Point" },
            { 7, false, "Archon statue" },
            { 8, false, "Dungeon" },
            // Puzzles
            { 9, false, "Time trial" },
            { 10, false, "Seelie" },
            { 11, false, "Shrine of depths" },
            { 12, false, "Elemental monument" },
            { 13, false, "Elemental torch" },
            // NPC
            { 14, false, "NPC" },
            { 15, false, "Enemy" },
            // Exploration
            { 16, false, "Anemoculus" },
            { 17, false, "Geoculus" },
            { 18, false, "Electroculus" },
            { 19, false, "Dendroculus" },
            { 20, false, "Hydroculus" },
            { 21, false, "Crimson Agate" },
            { 22, false, "Lumenspar" }
        });

	    HookManager::install(app::GameManager_Update, GameManager_Update_h);
    }

    void ESP::GUI() {
        ConfigCheckbox("ESP", b_Enabled, "Shows chosen categories of entities through the walls.");
        if (b_Enabled) {
            ImGui::Indent();
            if (ImGui::ColorEdit4("Outline color", &c_Color.getValue()[0], ImGuiColorEditFlags_AlphaBar)) {
                c_Color.setValue(c_Color.getValue());
                config::setValue(c_Color, c_Color.getValue());
            }
            if (BeginGroupPanel("Choose target entities", true)) {
                for (int i = 0; i < 23; i++) {
                    if (ImGui::Checkbox(std::get<2>(v_Filters.getValue()[i]).c_str(), &std::get<1>(v_Filters.getValue()[i]))) {
                        v_Filters.setValue(v_Filters.getValue());
                        config::setValue(v_Filters, v_Filters.getValue());
                    }
                }
            } EndGroupPanel();
            ImGui::Unindent();
        }
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
        LOG_INFO("1");
        game::EntityManager& instance = cheat::game::EntityManager::getInstance();
        LOG_INFO("2");
        auto& esp = ESP::getInstance();
        LOG_INFO("3");
        app::Camera* camera = app::Camera_get_main();
        LOG_INFO("4");
        std::vector<ESPBase::Filter> filters;
        LOG_INFO("5");
        for (int i = 0; i < 23; i++) {
            LOG_INFO("6");
            filters[i] = { (ESPBase::ESPFilter)std::get<0>(esp.v_Filters.getValue()[i]), std::get<1>(esp.v_Filters.getValue()[i]), std::get<2>(esp.v_Filters.getValue()[i]) };
            LOG_INFO("7");
        }
        LOG_INFO("8");
        ESPBase::DrawESP(camera, instance, filters, drawInfo);
        LOG_INFO("9");
        CALL_ORIGIN(GameManager_Update_h, this_, mi);
    };
}
