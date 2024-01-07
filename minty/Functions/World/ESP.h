#pragma once
#include "../../game/IEntityFilter.h"
#include "../FunctionIncludes.h"
#include "../../game/EntityManager.h"
#include "ESPRender.h"

namespace cheat 
{
    class ESP : public Function {
    public:
		ConfigField<bool> f_Enabled;

		ConfigField<bool> f_DrawBox;
		ConfigField<bool> f_DrawTracer;
		
		ConfigField<float> f_FillTransparency;

		ConfigField<bool> f_DrawDistance;
		ConfigField<bool> f_DrawName;

		ConfigField<float> f_OutlineThickness;
		ConfigField<float> f_TracerSize;

		ConfigField<int> f_FontSize;
		ConfigField<float> f_FontOutlineSize;

		ConfigField<std::vector<float>> f_GlobalBoxColor;
		ConfigField<std::vector<float>> f_GlobalLineColor;
		ConfigField<std::vector<float>> f_GlobalESPColor;

		ConfigField<float> f_Range;
		
		// Filters
		ConfigField<bool> f_Ores;
		ConfigField<bool> f_OresDrop;
		ConfigField<bool> f_Oculies;
		ConfigField<bool> f_Plants;
		ConfigField<bool> f_PickableLoot;
		ConfigField<bool> f_Chests;
		ConfigField<bool> f_Monsters;

		ImColor GlobalBoxColor;
		ImColor GlobalLineColor;
		ImColor GlobalESPColor;

		Hotkey f_Hotkey;

		game::EntityManager* entityManager;

		ImColor m_FontContrastColor;

		void Outer() override;
		void GUI() override;
		void Status() override;

		std::string getModule() override;
		static ESP& getInstance();
		ESP();
    };
}

