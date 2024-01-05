#pragma once

#include "../FunctionIncludes.h"
#include "../../game/filters.h"
#include "../../game/SimpleFilter.h"

#include "ESP.h"

namespace cheat
{
	bool DrawEntity(const std::string& name, game::Entity* entity, const ImColor& color, const ImColor& contrastColor);
	void PrepareFrame();
}
