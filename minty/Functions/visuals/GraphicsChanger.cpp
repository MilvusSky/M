#include "GraphicsChanger.h"

namespace cheat {
    bool needUpdate;

    GraphicsChanger::GraphicsChanger() {
		b_Enabled = config::getValue("functions:GraphicsChanger", "enabled", false);
    }

    void GraphicsChanger::GUI() {
		needUpdate = false;
		ConfigCheckbox("Graphics changer", b_Enabled, "Allows to customize few graphics settings.");
		if (b_Enabled) {
			ImGui::Indent();
			if (ImGui::SliderFloat("Outline width", &f_OutlineWidth.getValue(), 0, 10)) {
				f_OutlineWidth.setValue(f_OutlineWidth.getValue());
				config::setValue(f_OutlineWidth, f_OutlineWidth.getValue());
				needUpdate = true;
				std::string outline = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").outlineCorrectionWidth = " + std::to_string(f_OutlineWidth.getValue()); // Outline width
				luahookfunc(outline.c_str());
			}
			if (ImGui::SliderFloat("Gamma scale", &f_GammaScale.getValue(), 0, 20)) {
				f_GammaScale.setValue(f_GammaScale.getValue());
				config::setValue(f_GammaScale, f_GammaScale.getValue());
				needUpdate = true;
				std::string gamma = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\")._gammaValue = " + std::to_string(f_GammaScale.getValue()); // Gamma scale
				luahookfunc(gamma.c_str());
				//luahookfunc("CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").cameraBufferDirty = true");
			}
			if (ImGui::SliderFloat("Render resolution", &f_RenderScale.getValue(), 0, 5)) {
				f_RenderScale.setValue(f_RenderScale.getValue());
				config::setValue(f_RenderScale, f_RenderScale.getValue());
				needUpdate = true;
				auto uaba = (uint64_t)GetModuleHandleA("UserAssembly.dll");
				write<float>(read<uint64_t>(read<uint64_t>(read<uint64_t>(read<uint64_t>(read<uint64_t>(read<uint64_t>(uaba + 0x0205FC68) + 0x98) + 0x10) + 0x18) + 0x130) + 0xB0) + 0x44, f_RenderScale.getValue());
				luahookfunc("CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").cameraBufferDirty = true");
			}
			ImGui::Unindent();

		}
	}
    
    void GraphicsChanger::Outer() {
    	if (!b_Enabled.getValue()) return;
	if (needUpdate) {
	    
	}
 //   	luahookfunc("CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").cameraBufferDirty = true"); // refresh da buffer
 //   	
 //   	//::write<float>(::read<uint64_t>(::read<uint64_t>(::read<uint64_t>(uaba + offst1) + 0x) + 0x) + 0x, f_RenderScale.getValue()); -- Render scale, requires offsets
 //   
	//std::string outline = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").outlineCorrectionWidth = " + std::to_string(f_OutlineWidth.getValue()); // Outline width
	//luahookfunc(outline.c_str());
 //   
	//std::string gamma = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\")._gammaValue = " + std::to_string(f_GammaScale.getValue()); // Gamma scale
	//luahookfunc(gamma.c_str());

	//std::string ortho = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"Camera\").orthographic = " + b_OrthographicMode.getValue() ? "true" : "false"; // Orthographic mode
	//luahookfunc(ortho.c_str());

	//std::string AA;
 //   	switch (i_AntialiasingMode.getValue()) {
 //   	case 0: {
	//    AA = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").antialiasingMode = CS.UnityEngine.Rendering.PostProcessing.PostProcessLayer.Antialiasing.None";
 //   			break;
 //   		}
 //   	case 1: {
	//    AA = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").antialiasingMode = CS.UnityEngine.Rendering.PostProcessing.PostProcessLayer.Antialiasing.FastApproximateAntialiasing";
 //   			break;
 //   		}
 //   	case 2: {
	//    AA = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").antialiasingMode = CS.UnityEngine.Rendering.PostProcessing.PostProcessLayer.Antialiasing.miHoYoFXAA";
 //   			break;
 //   		}
 //   	case 3: {
	//    AA = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").antialiasingMode = CS.UnityEngine.Rendering.PostProcessing.PostProcessLayer.Antialiasing.SubpixelMorphologicalAntialiasing";
 //   			break;
 //   		}
 //   	case 4: {
	//    AA = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").antialiasingMode = CS.UnityEngine.Rendering.PostProcessing.PostProcessLayer.Antialiasing.TemporalAntialiasing";
 //   			break;
 //   		}
 //   	case 5: {
	//    AA = "CS.UnityEngine.GameObject.Find(\"/EntityRoot/MainCamera(Clone)(Clone)\"):GetComponent(\"PostProcessLayer\").antialiasingMode = CS.UnityEngine.Rendering.PostProcessing.PostProcessLayer.Antialiasing.FFX_FSR_2";
 //   			break;
 //   		}
 //   	}
	//luahookfunc(AA.c_str());
 //   	
 //   	/*switch (i_ShadowMode.getValue()) {
 //   	case 0: {
 //   			app::QualitySettings_set_shadows(app::ShadowQuality::Disable);
 //   			break;
 //   		}
 //   	case 1: {
 //   			app::QualitySettings_set_shadows(app::ShadowQuality::HardOnly);
 //   			break;
 //   		}
 //   	case 2: {
 //   			app::QualitySettings_set_shadows(app::ShadowQuality::All);
 //   			break;
 //   		}
 //   	case 3: {
 //   			app::QualitySettings_set_shadows(app::ShadowQuality::ShadowsPCSS);
 //   			break;
 //   		}
 //   	case 4: {
 //   			app::QualitySettings_set_shadows(app::ShadowQuality::ShadowsPCSSHigh);
 //   			break;
 //   		}
 //   	}*/
    }
    
    void GraphicsChanger::Status() {
    
    }
    
    std::string GraphicsChanger::getModule() {
    	return _("Visuals");
    }

    GraphicsChanger& GraphicsChanger::getInstance() {
	static GraphicsChanger instance;
	return instance;
    }
}
