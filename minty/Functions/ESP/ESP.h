#pragma once
#include "ESPItem.h"
#include "../../game/IEntityFilter.h"
#include "../FunctionIncludes.h"

namespace cheat 
{
    class ESP : public Function {
    public:
	enum class DrawMode
	{
	    None,
	    Rectangle,
	    Box
	};

	enum class DrawTracerMode
	{
	    None,
	    Line,
	    OffscreenArrows
	};

	ConfigField<bool> f_Enabled;

	ConfigField<bool> f_DrawBox;
	ConfigField<bool> f_DrawTracer;

	ConfigField<int> f_TracerItemCurrent;
	ConfigField<int> f_BoxItemCurrent;

	//ConfigField<DrawMode> f_DrawBoxMode;
	//ConfigField<DrawTracerMode> f_DrawTracerMode;

	DrawMode f_DrawBoxMode;
	DrawTracerMode f_DrawTracerMode;

	ConfigField<float> f_FillTransparency;

	ConfigField<bool> f_DrawDistance;
	ConfigField<bool> f_DrawName;

	ConfigField<float> f_ArrowRadius;
	ConfigField<float> f_OutlineThickness;
	ConfigField<float> f_TracerSize;

	ConfigField<int> f_FontSize;
	ConfigField<float> f_FontOutlineSize;

	ConfigField<ImColor> f_GlobalFontColor;
	//ImColor m_FontContrastColor;
	ConfigField<ImColor> f_GlobalBoxColor;
	ConfigField<ImColor> f_GlobalRectColor;
	ConfigField<ImColor> f_GlobalLineColor;
	ConfigField<ImColor> f_GlobalESPColor;

	ConfigField<float> f_MinSize;
	ConfigField<float> f_Range;
	
	// Filters
	ConfigField<bool> f_Ores;
	ConfigField<bool> f_OresDrop;
	ConfigField<bool> f_Oculies;
	ConfigField<bool> f_Plants;
	ConfigField<bool> f_PickableLoot;
	ConfigField<bool> f_Chests;
	ConfigField<bool> f_Monsters;
	Hotkey f_Hotkey;

	ESP();

	static ESP& getInstance();

	void Outer() override;
	void GUI() override;
	void Status() override;
	std::string getModule() override;

    };
}

