#pragma once

#include "../FunctionIncludes.h"


#include "ESP.h"

namespace cheat
{
	bool DrawEntity(const std::string& name, game::Entity* entity, const ImColor& contrastColor);
	void PrepareFrame();
}
