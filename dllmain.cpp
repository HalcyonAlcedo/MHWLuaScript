#ifdef _WIN32
#pragma comment( lib, "ws2_32" )
#include <WinSock2.h>
#endif
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
#include "Component.h"
#include "LuaData.h"
#include "ControlProgram.h"
#include "LuaScript.h"
using namespace loader;

__declspec(dllexport) extern bool Load()
{
	
	//游戏版本检查
	if (std::string(GameVersion) != Base::ModConfig::Version) {
		LOG(WARN) << Base::ModConfig::ModName << " : Wrong version";
		return false;
	}

	Component::getFiles("nativePC\\LuaScript\\", Base::LuaHandle::LuaFiles);
	LOG(INFO) << "Lua file load:";
	for (string file_name : Base::LuaHandle::LuaFiles) {
		LOG(INFO) << file_name;
	}

	//初始化WebSocket
#ifdef _WIN32
	INT rc;
	WSADATA wsaData;

	rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (rc) {
		printf("WSAStartup Failed.\n");
		return 1;
	}
#endif
	//初始化steamid
	HMODULE  module = ::GetModuleHandle("steam_api64.dll");
	if (module != nullptr) {
		MODULEINFO moduleInfo;
		if (GetModuleInformation(GetCurrentProcess(), module, &moduleInfo, sizeof(moduleInfo))) {
			void* startAddr = (void*)module;
			Base::World::SteamId = *offsetPtr<int>(startAddr, 0x3A118);
		}
	}
	//获取程序列表
	Base::World::ProcessList = Component::GetProcessList();
	//初始化钩子
	MH_Initialize();
	HookLambda(MH::World::MapClockLocal,
		[](auto clock, auto clock2) {
			auto ret = original(clock, clock2);
			ControlProgram::InitConsole();
			if (Base::Init()) {
				Base::RealTimeUpdate();
				if (Base::ModConfig::GameDataInit) {
					for (string file_name : Base::LuaHandle::LuaFiles) {
						if(Base::LuaHandle::LuaCode[file_name].start)
							Lua_Main(file_name);
					}
				}
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
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		ControlProgram::hMod = hModule;
		return Load();
	}
	return TRUE;
}

