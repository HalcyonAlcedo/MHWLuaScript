// dllmain.cpp : Définit le point d'entrée de l'application DLL.
// MHWDLLMod 005
#include <fstream>
#include <queue>
#include <functional>

#include <random>
#include <iostream>
#include <cmath>

#include <windows.h>

#include "minhook/MinHook.h"
#include "json/json.hpp"
#include "loader.h"
#include "ghidra_export.h"
#include "util.h"
#include <thread>

#include "Base.h"
#include "Execution.h"

using namespace loader;

//随机浮点数
float myRander(float min, float max)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_real_distribution<float> dist(min, max);
	return dist(eng);
}

__declspec(dllexport) extern bool Load()
{

	//游戏版本检查
	if (std::string(GameVersion) != Base::ModConfig::Version) {
		LOG(WARN) << Base::ModConfig::ModName << " : Wrong version";
		return false;
	}

	//初始化钩子
	MH_Initialize();
	HookLambda(MH::World::MapClockLocal,
		[](auto clock, auto clock2) {
			auto ret = original(clock, clock2);
			if (Base::Init()) {
				Base::RealTimeUpdate();
				Execution::Main();
			}
			return ret;
		});
	//应用钩子
	MH_ApplyQueued();

	return true;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
		return Load();
	return TRUE;
}

