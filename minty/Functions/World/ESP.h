#include "../FunctionIncludes.h"
#include "../../game/EntityManager.h"
#include "ESPRender.h"

namespace cheat {
    class ESP : public Function {
    public:
	ConfigField<bool> b_Enabled;
	ConfigField<std::vector<float>> c_Color;
	ConfigField<float> f_TracerWidth;
	ConfigField<float> f_OutlineWidth;
	ConfigField<bool> b_TracerEnabled;
	ConfigField<int> i_OutlineType;
	ConfigField<std::vector<std::tuple<int, bool, std::string>>> v_Filters;


	virtual void GUI() override;
	virtual void Outer() override;
	virtual void Status() override;

	static ESP& getInstance();

	std::string getModule();

	ESP();
    };
}
