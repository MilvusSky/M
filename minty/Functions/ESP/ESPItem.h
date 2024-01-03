#pragma once

#include "../FunctionIncludes.h"

namespace cheat
{
	class ESPItem
	{
	public:
		ESPItem(const std::string& name, const ImColor& color, const Hotkey& hotkey, const std::string& textureName)
			: m_Name(name), m_Color(color), m_Hotkey(hotkey), m_Texture(nullptr), m_Enabled(false) { }

		bool operator==(const ESPItem& another) const
		{
			return m_Enabled == another.m_Enabled && m_Color == another.m_Color /*& m_Hotkey == another.m_Hotkey*/ ;
		}

		Hotkey m_Hotkey;
		bool m_Enabled;
		std::string m_Name;
		ImColor m_Color;
		ImColor m_ContrastColor;
		void* m_Texture;
	};
}
