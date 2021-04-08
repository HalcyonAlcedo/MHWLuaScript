﻿#include "kiero.h"

#if KIERO_INCLUDE_D3D11

#include "d3d11_impl.h"
#include <d3d11.h>
#include <assert.h>

#include "win32_impl.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

typedef long(__stdcall* Present)(IDXGISwapChain*, UINT, UINT);
static Present oPresent = NULL;

long __stdcall hkPresent11(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	static bool init = false;

	if (!init)
	{
		DXGI_SWAP_CHAIN_DESC desc;
		pSwapChain->GetDesc(&desc);

		ID3D11Device* device;
		pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&device);

		ID3D11DeviceContext* context;
		device->GetImmediateContext(&context);

		impl::win32::init(desc.OutputWindow);

		ImGui::CreateContext();
		ImGui_ImplWin32_Init(desc.OutputWindow);
		ImGui_ImplDX11_Init(device, context);

		init = true;
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	impl::showExampleWindow("D3D11");

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return oPresent(pSwapChain, SyncInterval, Flags);
}

void impl::d3d11::init()
{
	assert(kiero::bind(8, (void**)&oPresent, hkPresent11) == kiero::Status::Success);
}

#endif // KIERO_INCLUDE_D3D11