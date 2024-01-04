#include "../FunctionIncludes.h"

namespace ESPBase {
    //const char* drawModes[4] = { "Line", "Rectangle", "Filled rectangle", "Circle" };

    enum ESPFilter : int {
        //Chests
        Chest1,
        Chest2,
        Chest3,
        Chest4,
        Chest5,
        HiddenChest,

        //Env
        TpPoint,
        ArchonStatue,
        Dungeon,

        //Puzzle
        Trial,
        Seelie,
        Usipalnitsa,
        ElementalMonument,
        ElementalTorch,

        //NPC
        Npc,
        Enemy,

        //Explore
        Anemoculus,
        Geoculus,
        Electroculus,
        Dendroculus,
        Hydroculus,
        BagroviyAgat,
        ChasmCrystall
    };

    struct Filter {
        ESPFilter filter;
        bool enabled;
        std::string name;
    };

    struct ESPDrawInfo {
        ImVec4 color;
        float tracerWidth;
        float outlineWidth;
        int drawMode;
        bool tracerEnabled;
    };

    struct Bounds {
        app::Vector3 v_min;
        app::Vector3 v_max;
        app::Vector3 v_center;
    };

    void DrawESP(app::Camera* camera, cheat::game::EntityManager& manager, std::vector<Filter> filters, ESPDrawInfo drawInfo);
}
