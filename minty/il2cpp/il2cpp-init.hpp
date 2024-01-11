#pragma once

#include <Windows.h>
#include <sstream>
#include <fstream>

#include "../utils/Logger.h"
#include "../config/ConfigManager.h"

// Define IL2CPP API function addresses
#define DO_API(a, b, r, n, p) r(*n) p
	#include "il2cpp-api-functions.h"
#undef DO_API

// Define function addresses
#define DO_APP_FUNC(a, b, r, n, p) r(*n) p
#define DO_TYPEDEF(a, n) n ## __Class** n ## __TypeInfo
#define DO_APP_FUNC_METHODINFO(a, n) struct MethodInfo ** n
namespace app {
	#include "il2cpp-types.h"
	#include "il2cpp-functions.h"
}
#undef DO_APP_FUNC
#undef DO_TYPEDEF
#undef DO_APP_FUNC_METHODINFO

// Define UnityPlayer functions
#define DO_UP_FUNC(a, b, r, n, p) r(*n) p
namespace app {
	#include "il2cpp-unityplayer-functions.h"
}
#undef DO_UP_FUNC

#define SELECT_VERSION(VERSION, OS_OFFSET, CN_OFFSET) (VERSION == GameVersion::GLOBAL ? OS_OFFSET : CN_OFFSET)

enum class GameVersion {
	NONE,
	GLOBAL,
	CHINA
};

GameVersion getGameVersion() {
	// 4.3.0 (pkg_version -> md5)
	std::array<std::pair<GameVersion, std::string>, 2> gameVersions = {{
			{ GameVersion::GLOBAL, "218603b67495dab9f6ce28515451c231" },
			{ GameVersion::CHINA, "9171a8aba135d881b082bcdd6174d812" }
		}};
	std::string hash = util::getUAHash(config::getValue<std::string>("general", "execPath", "").getValue());

	for (const auto& [gameVersion, checksum] : gameVersions) {
		if (checksum != hash)
			continue;

		return gameVersion;
	}

	return GameVersion::NONE;
}

uintptr_t baseAddress;
uintptr_t unityPlayerAddress;

VOID init_il2cpp() {
	auto gameVersion = getGameVersion();

	if (gameVersion != GameVersion::NONE)
		LOG_INFO("Detected %s version.", gameVersion == GameVersion::GLOBAL ? "GLOBAL" : "CHINA");
	else {
		LOG_ERROR("Failed to detect any game version. If you sure that cheat has updated for current game version, and you downloaded the correct one.");
		system("pause");
		exit(0);
		return;
	}

	while (baseAddress == (uint64_t) nullptr) {
		Sleep(1000);
		baseAddress = (uint64_t) GetModuleHandleA("UserAssembly.dll");

		if (GetModuleHandleA("UserAssembly.dll") != nullptr) {
			baseAddress = (uint64_t) GetModuleHandleA("UserAssembly.dll");
			unityPlayerAddress = (uint64_t) GetModuleHandleA("UnityPlayer.dll");

			#define DO_API(a, b, r, n, p) n = (r (*) p)(baseAddress + SELECT_VERSION(gameVersion, a, b))
				#include "il2cpp-api-functions.h"
			#undef DO_API

			#define DO_APP_FUNC(a, b, r, n, p) n = (r (*) p)(baseAddress + SELECT_VERSION(gameVersion, a, b))
			#define DO_APP_FUNC_METHODINFO(a, n) n = (struct MethodInfo **)(baseAddress + a)
				#include "il2cpp-functions.h"
			#undef DO_APP_FUNC
			#undef DO_APP_FUNC_METHODINFO

			#define DO_TYPEDEF(a, b, n) n ## __TypeInfo = (n ## __Class**) (baseAddress + SELECT_VERSION(gameVersion, a, b))
				#include "il2cpp-types.h"
			#undef DO_TYPEDEF

			#define DO_UP_FUNC(a, b, r, n, p) n = (r (*) p)(unityPlayerAddress + SELECT_VERSION(gameVersion, a, b))
				#include "il2cpp-unityplayer-functions.h"
			#undef DO_UP_FUNC
		}
	}
}
