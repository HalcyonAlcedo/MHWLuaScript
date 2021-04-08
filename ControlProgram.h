#pragma once
#include "imgui/imgui.h"  
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "implot/implot.h"
#include <d3d11.h>
#include <dxgi.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include "kiero.h"
#pragma comment ( lib, "D3D11.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace ControlProgram {
	bool initConsole = false;
	bool init = false;
	typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
	typedef uintptr_t PTR;
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	Present oPresent;
	HWND window = NULL;
	WNDPROC oWndProc;
	ID3D11Device* pDevice = NULL;
	ID3D11DeviceContext* pContext = NULL;
	ID3D11RenderTargetView* mainRenderTargetView;
	HMODULE hMod;

	void InitImGui()
	{
		ImGui::CreateContext();
		ImPlot::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		auto fonts = ImGui::GetIO().Fonts;
		fonts->AddFontFromFileTTF(
			"c:/windows/fonts/simhei.ttf",
			13.0f,
			NULL,
			fonts->GetGlyphRangesChineseFull()
		);
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX11_Init(pDevice, pContext);
	}

	HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		if (!init)
		{
			if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
			{
				pDevice->GetImmediateContext(&pContext);
				DXGI_SWAP_CHAIN_DESC sd;
				pSwapChain->GetDesc(&sd);
				window = sd.OutputWindow;
				ID3D11Texture2D* pBackBuffer;
				pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
				pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
				pBackBuffer->Release();
				oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
				InitImGui();
				init = true;
			}

			else
				return oPresent(pSwapChain, SyncInterval, Flags);
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (Base::ModConfig::ModConsole)
		{
			ImGui::SetNextWindowBgAlpha(0.35f);
			ImGui::Begin(u8"LuaScript 控制台");

			ImGui::Text(u8"LuaScript版本：%s", Base::ModConfig::ModVersion);

			if (ImGui::TreeNode(u8"Lua脚本列表"))
			{
				if (ImGui::Button(u8"更新脚本代码")) {
					for (string file_name : Base::LuaHandle::LuaFiles) { Base::LuaHandle::LuaCode[file_name].Update(); }
				}
				for (string file_name : Base::LuaHandle::LuaFiles) {
					ImGui::TextColored(Base::LuaHandle::LuaCode[file_name].start ? ImVec4(0.0f, 0.8f, 0.0f, 1.0f) : ImVec4(0.8f, 0.0f, 0.0f, 1.0f), Component::string_To_UTF8(file_name).c_str());
					if (!Base::LuaHandle::LuaCode[file_name].hotReload) {
						ImGui::SameLine();
						ImGui::Checkbox((u8"启用" + file_name).c_str(), &Base::LuaHandle::LuaCode[file_name].start);
					}
				}
				ImGui::TreePop();
				ImGui::Separator();
			}
			if (ImGui::TreeNode(u8"Lua脚本数据"))
			{
				ImGui::Text(u8"当前时间：%f", Base::Chronoscope::NowTime);
				if (ImGui::TreeNode(u8"计时器"))
				{
					for (auto [chronoscopeName, chronoscopeData] : Base::Chronoscope::ChronoscopeList) {
						if (chronoscopeData.EndTime < Base::Chronoscope::NowTime) {
							ImGui::TextColored(ImVec4(0.8f, 0.0f, 0.0f, 1.0f), chronoscopeName.c_str());
						}
						else {
							ImGui::TextColored(ImVec4(0.0f, 0.8f, 0.0f, 1.0f), chronoscopeName.c_str());
						}
						ImGui::SameLine();
						ImGui::Text(u8" : %f", chronoscopeData.EndTime);
					}
					ImGui::TreePop();
				}
				if (ImGui::TreeNode(u8"变量缓存"))
				{
					if (ImGui::TreeNode(u8"整数"))
					{
						for (auto [VariableName, VariableData] : LuaData::IntVariable) {
							ImGui::Text(u8"%s: %d", VariableName.c_str(), VariableData);
						}
						ImGui::TreePop();
					}
					if (ImGui::TreeNode(u8"浮点数"))
					{
						for (auto [VariableName, VariableData] : LuaData::FloatVariable) {
							ImGui::Text(u8"%s: %f", VariableName.c_str(), VariableData);
						}
						ImGui::TreePop();
					}
					if (ImGui::TreeNode(u8"字符串"))
					{
						for (auto [VariableName, VariableData] : LuaData::StringVariable) {
							ImGui::Text(u8"%s: %s", VariableName.c_str(), VariableData.c_str());
						}
						ImGui::TreePop();
					}
					ImGui::TreePop();
				}
				ImGui::TreePop();
				ImGui::Separator();
			}
			if (ImGui::TreeNode(u8"游戏数据"))
			{
				ImGui::Text(u8"地图Id：%d", Base::World::MapId);
				if (ImGui::TreeNode(u8"玩家信息"))
				{
					ImGui::Text(u8"动作Id：%d", Base::PlayerData::ActionId);
					if (ImGui::TreeNode(u8"派生信息"))
					{
						ImGui::Text(u8"当前Fsm：%d - %d", Base::PlayerData::NowFsm.Target, Base::PlayerData::NowFsm.Id);
						ImGui::Text(u8"上一个执行的Fsm：%d - %d", Base::PlayerData::Fsm.Target, Base::PlayerData::Fsm.Id);
						ImGui::TreePop();
					}
					ImGui::Text(u8"当前耐力：%f", Base::PlayerData::CurrentEndurance);
					ImGui::Text(u8"当前血量：%f", Base::PlayerData::CurrentHealth);
					ImGui::Text(u8"当前坐标");
					ImGui::Text(u8"X：%f", Base::PlayerData::Coordinate::Entity.x);
					ImGui::Text(u8"Y：%f", Base::PlayerData::Coordinate::Entity.y);
					ImGui::Text(u8"Z：%f", Base::PlayerData::Coordinate::Entity.z);
					ImGui::Text(u8"武器类型：%d", Base::PlayerData::Weapons::WeaponType);
					ImGui::Text(u8"武器Id：%d", Base::PlayerData::Weapons::WeaponId);
					ImGui::TreePop();
				}
				if (ImGui::TreeNode(u8"怪物信息"))
				{
					for (auto [monster, monsterData] : Base::Monster::Monsters) {
						if (monster != nullptr) {
							ostringstream ptr;
							ptr << monsterData.Plot;
							string ptrstr = ptr.str();
							if (ImGui::TreeNode((Component::GetMonstersName_CN(monsterData.Id) + ptrstr).c_str()))
							{
								void* healthMgr = *offsetPtr<void*>(monster, 0x7670);
								float health = *offsetPtr<float>(healthMgr, 0x64);
								float maxHealth = *offsetPtr<float>(healthMgr, 0x60);
								ImGui::Text(u8"内存地址：%x", monsterData.Plot);
								ImGui::Text(u8"怪物Id：%d", monsterData.Id);
								ImGui::Text(u8"怪物变种：%d", monsterData.SubId);
								ImGui::Text(u8"当前血量：%f", health);
								ImGui::Text(u8"最大血量：%f", maxHealth);
								ImGui::Text(u8"当前坐标");
								ImGui::Text(u8"X：%f", monsterData.CoordinatesX);
								ImGui::Text(u8"Y：%f", monsterData.CoordinatesY);
								ImGui::Text(u8"Z：%f", monsterData.CoordinatesZ);
								void* MonstersHate = Base::Monster::GetHateTarget(monster);
								ImGui::Text(u8"仇恨目标：%s", MonstersHate != nullptr ? 
									MonstersHate == Base::BasicGameData::PlayerPlot ? u8"玩家" : u8"其他"
									: u8"无目标"
								);
								ImGui::SameLine();
								ImGui::Text("%x", MonstersHate);
								ImGui::TreePop();
								ImGui::Separator();
							}
						}
					}
					ImGui::TreePop();
				}
				if (ImGui::TreeNode(u8"环境生物信息"))
				{
					for (auto [environmental, environmentalData] : Base::World::EnvironmentalData::Environmentals) {
						if (environmental != nullptr) {
							ostringstream ptr;
							ptr << environmentalData.Plot;
							string ptrstr = ptr.str();
							if (ImGui::TreeNode(ptrstr.c_str()))
							{
								ImGui::Text(u8"内存地址：%x", environmentalData.Plot);
								ImGui::Text(u8"生物Id：%d", environmentalData.Id);
								ImGui::Text(u8"生物变种：%d", environmentalData.SubId);
								ImGui::Text(u8"当前坐标");
								ImGui::Text(u8"X：%f", environmentalData.CoordinatesX);
								ImGui::Text(u8"Y：%f", environmentalData.CoordinatesY);
								ImGui::Text(u8"Z：%f", environmentalData.CoordinatesZ);
								ImGui::TreePop();
								ImGui::Separator();
							}
						}
					}
					ImGui::TreePop();
				}

				ImGui::TreePop();
				ImGui::Separator();
			}
			ImGui::End();
		}
		ImGui::Render();
		pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		return oPresent(pSwapChain, SyncInterval, Flags);
	}

	DWORD WINAPI MainThread(LPVOID lpReserved)
	{
		bool init_hook = false;
		do
		{
			if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
			{
				kiero::bind(8, (void**)&oPresent, hkPresent);
				init_hook = true;
			}
		} while (!init_hook);
		return TRUE;
	}

	LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;

		return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
	}

	static void InitConsole() {
		if (initConsole)
			return;
		else
			initConsole = true;
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
	}
}