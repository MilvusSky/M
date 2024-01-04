#include "../FunctionIncludes.h"
#include "../../game/EntityManager.h"

namespace cheat {
    class ESP : public Function {
    public:
	ConfigField<bool> b_Enabled;
	ConfigField<std::tuple<int, int, int>> c_Color;
	ConfigField<float> f_TracerWidth;
	ConfigField<float> f_OutlineWidth;
	ConfigField<bool> b_TracerEnabled;
	ConfigField<int> i_OutlineType;
	ConfigField<std::vector<int>> v_Filters;

	const char* drawModes[4] = { "Line", "Rectangle", "Filled rectangle", "Circle" };

	virtual void GUI() override;
	virtual void Outer() override;
	virtual void Status() override;

	static ESP& getInstance();

	std::string getModule();

	ESP();
    };
}
