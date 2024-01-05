#pragma once

#include "../FunctionIncludes.h"
#include "../../api/lua/luahook.hpp"
#include "../../il2cpp/il2cppUtils.h"

namespace cheat {
    class GraphicsChanger : public Function {
    public:
    	ConfigField<bool> b_Enabled;
    
    	ConfigField<bool> b_RenderScale;
    	ConfigField<bool> b_GammaScale;
    	ConfigField<bool> b_OutlineWidth;
    	ConfigField<bool> b_AntialiasingMode;
    	ConfigField<bool> b_ShadowMode;
    	ConfigField<bool> b_OrthographicMode;
    
    	Hotkey h_Enabled;
    
    	Hotkey h_RenderScale;
    	Hotkey h_GammaScale;
    	Hotkey h_OutlineWidth;
    	Hotkey h_AntialiasingMode;
    	Hotkey h_ShadowMode;
    	Hotkey h_OrthographicMode;
    
    	ConfigField<float> f_RenderScale;
    	ConfigField<float> f_GammaScale;
    	ConfigField<float> f_OutlineWidth;
    	ConfigField<int> i_AntialiasingMode;
    	ConfigField<int> i_ShadowMode;
    
    	const char* a_ShadowModes[5] = { "Disable", "Hard", "Soft", "NVidia PCSS", "NVidia PCSS high" };
    	const char* a_AntialiasingModes[6] = { "None", "FAA", "FXAA", "SMAA", "TA", "FSR2" };
    
    	void GUI() override;
    	void Outer() override;
    	void Status() override;
    
    	std::string getModule() override;
    
    	static GraphicsChanger& getInstance();
    
    	GraphicsChanger();
    };
}
