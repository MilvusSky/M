#include "../FunctionIncludes.h"
#include "../../api/lua/luahook.hpp"

namespace cheat {
	class BooResizer : public Function {
	public:
		ConfigField<bool> b_Enabled;
		ConfigField<float> f_Size;

		Hotkey h_Hotkey;

		void GUI() override;
		void Outer() override;
		void Status() override;
		
		BooResizer();

		std::string getModule();
	};
}