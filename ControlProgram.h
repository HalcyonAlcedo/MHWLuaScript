#pragma once
#include "imgui.h"  
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#pragma comment ( lib, "D3D11.lib")

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace ControlProgram {
	bool init = false;
	// Data
	static ID3D11Device* g_pd3dDevice = NULL;
	static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
	static IDXGISwapChain* g_pSwapChain = NULL;
	static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

	// Forward declarations of helper functions
	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
	void CreateRenderTarget();
	void CleanupRenderTarget();
	LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static bool CreateDeviceD3D(HWND hWnd)
	{
		// Setup swap chain
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 2;
		sd.BufferDesc.Width = 0;
		sd.BufferDesc.Height = 0;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hWnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		UINT createDeviceFlags = 0;
		//createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
		if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
			return false;

		CreateRenderTarget();
		return true;
	}

	static void CleanupDeviceD3D()
	{
		CleanupRenderTarget();
		if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
		if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
		if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
	}

	static void CreateRenderTarget()
	{
		ID3D11Texture2D* pBackBuffer;
		g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
		g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
		pBackBuffer->Release();
	}

	static void CleanupRenderTarget()
	{
		if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
	}

	// Win32 message handler
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;

		switch (msg)
		{
		case WM_SIZE:
			if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
			{
				CleanupRenderTarget();
				g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
				CreateRenderTarget();
			}
			return 0;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
				return 0;
			break;
		case WM_DESTROY:
			::PostQuitMessage(0);
			return 0;
		}
		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	}

	static void InitConsole() {
		if (init)
			return;
		else
			init = true;

		std::thread([](bool &showwindow,
			vector<string>& LuaFiles,
			string& ModVersion,
			int& MapId,
			int& ActionId,
			int& WeaponType,
			int& WeaponId,
			float& CurrentEndurance,
			float& CurrentHealth,
			Base::Vector3& PlayerCoordinate,
			map<void*, Base::Monster::MonsterData> &Monsters
			) {
			WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("LuaScrippt"), NULL };
			::RegisterClassEx(&wc);
			//在扩展样式中加入WS_EX_LAYERED
			HWND hwnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW,
				wc.lpszClassName,
				_T("LuaScrpt 控制台"),
				WS_POPUP,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				GetSystemMetrics(SM_CXSCREEN),
				GetSystemMetrics(SM_CYSCREEN),
				NULL,
				NULL,
				GetModuleHandle(NULL),
				NULL);
			//设置颜色过滤,使用改关键色刷新屏幕后颜色被过滤实现透明
			SetLayeredWindowAttributes(hwnd, RGB(254, 254, 254), NULL, LWA_COLORKEY);

			//设置dx11屏幕刷新颜色 注意这里的颜色要和设置透明关键色设置一样
			ImVec4 clear_color = ImGui::ColorConvertU32ToFloat4(IM_COL32(254, 254, 254, 255));
			
			if (!CreateDeviceD3D(hwnd))
			{
				CleanupDeviceD3D();
				::UnregisterClass(wc.lpszClassName, wc.hInstance);
				return 1;
			}
			::ShowWindow(hwnd, SW_SHOWDEFAULT);
			::UpdateWindow(hwnd);

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			ImGui::StyleColorsDark();

			ImGui_ImplWin32_Init(hwnd);
			ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
			auto fonts = ImGui::GetIO().Fonts;
			fonts->AddFontFromFileTTF(
				"c:/windows/fonts/simhei.ttf",
				13.0f,
				NULL,
				fonts->GetGlyphRangesChineseSimplifiedCommon()
			);

			MSG msg;
			ZeroMemory(&msg, sizeof(msg));
			HWND gameHwnd = FindWindow("MT FRAMEWORK", NULL);
			RECT rect1;
			RECT rect2;
			while (msg.message != WM_QUIT)
			{
				GetWindowRect(gameHwnd, &rect1);
				GetWindowRect(hwnd, &rect2);
				if (
					rect1.left != rect2.left or
					rect1.top != rect2.top or
					rect1.right != rect2.right or
					rect1.bottom != rect2.bottom
					)
					MoveWindow(hwnd, rect1.left, rect1.top, rect1.right - rect1.left, rect1.bottom - rect1.top, false);
				if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					::TranslateMessage(&msg);
					::DispatchMessage(&msg);
					continue;
				}
				ImGui_ImplDX11_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();
				if(showwindow)
				{
					ImGui::Begin(u8"LuaScript 控制台");

					ImGui::Text(u8"LuaScript版本：%s", ModVersion);

					if (ImGui::TreeNode(u8"Lua脚本列表"))
					{
						for (string file_name : LuaFiles) {
							ImGui::TextColored(ImVec4(0.0f, 0.8f, 0.0f, 1.0f), file_name.c_str());
						}
						ImGui::TreePop();
						ImGui::Separator();
					}
					if (ImGui::TreeNode(u8"游戏数据"))
					{
						ImGui::Text(u8"地图Id：%d", MapId);
						if (ImGui::TreeNode(u8"玩家信息"))
						{
							ImGui::Text(u8"动作Id：%d", ActionId);
							ImGui::Text(u8"当前耐力：%f", CurrentEndurance);
							ImGui::Text(u8"当前血量：%f", CurrentHealth);
							ImGui::Text(u8"当前坐标");
							ImGui::Text(u8"X：%f", PlayerCoordinate.x);
							ImGui::Text(u8"Y：%f", PlayerCoordinate.y);
							ImGui::Text(u8"Z：%f", PlayerCoordinate.z);
							ImGui::Text(u8"武器类型：%d", WeaponType);
							ImGui::Text(u8"武器Id：%d", WeaponId);
							ImGui::TreePop();
						}
						if (ImGui::TreeNode(u8"怪物信息"))
						{
							for (auto [monster, monsterData] : Monsters) {
								if (monster != nullptr) {
									ostringstream ptr;
									ptr << monsterData.Plot;
									string ptrstr = ptr.str();
									if (ImGui::TreeNode(ptrstr.c_str()))
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
				const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
				g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
				g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
				ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

				g_pSwapChain->Present(1, 0);
			}

			// Cleanup
			ImGui_ImplDX11_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();

			CleanupDeviceD3D();
			::DestroyWindow(hwnd);
			::UnregisterClass(wc.lpszClassName, wc.hInstance);

		},
			ref(Base::ModConfig::ModConsole),
			ref(Base::ModConfig::LuaFiles),
			ref(Base::ModConfig::ModVersion),
			ref(Base::World::MapId),
			ref(Base::PlayerData::ActionId),
			ref(Base::PlayerData::Weapons::WeaponType),
			ref(Base::PlayerData::Weapons::WeaponId),
			ref(Base::PlayerData::CurrentEndurance),
			ref(Base::PlayerData::CurrentHealth),
			ref(Base::PlayerData::Coordinate::Entity),
			ref(Base::Monster::Monsters)
		).detach();
	}
}