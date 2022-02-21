#pragma once
#include "imgui/imgui.h"  
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "implot/implot.h"
#include "imgui/imgui_markdown.h"
#include <d3d11.h>
#include <dxgi.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include <direct.h>
#include "kiero.h"
#include "imHotKey.h"
#pragma comment ( lib, "D3D11.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace ControlProgram {
	bool initConsole = false;
	bool init = false;
	typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
	typedef uintptr_t PTR;
	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	Present oPresent;
	Present oResize;
	HWND window = NULL;
	WNDPROC oWndProc;
	ID3D11Device* pDevice = NULL;
	ID3D11DeviceContext* pContext = NULL;
	ID3D11RenderTargetView* mainRenderTargetView;
	HMODULE hMod;

	//�ȼ��б�
	static map<string, bool> Checkhotkey;

	//������
	struct TextureCache {
		int width = 0;
		int height = 0;
		ID3D11ShaderResourceView* texture = NULL;
		TextureCache(
			int width = 0,
			int height = 0,
			ID3D11ShaderResourceView* texture = NULL
		) :width(width), height(height), texture(texture) { };
	};
	map<string, TextureCache> ImgTextureCache;

	static void PlaySoundFile(string SoundFile) {
		Player* player = new Player();
		Sound* sound = new Sound();
		player->Create();
		sound->LoadFromFile(SoundFile);
		player->SetSound(*sound);
		player->Play();
	}

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
	//����ͼƬ��д������
	void LoadTexture(unsigned char* image_data, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height, int image_width, int image_height) {
		// Create texture
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Width = image_width;
		desc.Height = image_height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;

		ID3D11Texture2D* pTexture = NULL;
		D3D11_SUBRESOURCE_DATA subResource;
		subResource.pSysMem = image_data;
		subResource.SysMemPitch = desc.Width * 4;
		subResource.SysMemSlicePitch = 0;
		pDevice->CreateTexture2D(&desc, &subResource, &pTexture);

		// Create texture view
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;
		pDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
		pTexture->Release();

		*out_width = image_width;
		*out_height = image_height;
		stbi_image_free(image_data);
	}
	bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
	{
		// Load from disk into a raw RGBA buffer
		int image_width = 0;
		int image_height = 0;
		unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
		if (image_data == NULL)
			return false;
		LoadTexture(image_data, out_srv, out_width, out_height, image_width, image_height);
		return true;
	}
	bool LoadTextureFromBase(string Base64Data, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height, int image_width, int image_height)
	{
		unsigned char* image_data = Base::Calculation::Base64ToImg(Base64Data);
		if (image_data == NULL)
			return false;
		LoadTexture(image_data, out_srv, out_width, out_height, image_width, image_height);
		return true;
	}
	HRESULT __stdcall hkResize(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		mainRenderTargetView->Release();
		mainRenderTargetView = nullptr;
		Base::ModConfig::DrawInit = false;
		if(!Base::ModConfig::SecurityModel) Base::ModConfig::GameDataInit = false;
		return oResize(pSwapChain, SyncInterval, Flags);
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
				ImHotKey::LoadHotKey();
				ImHotKey::AddHotKey(u8"Console", u8"�򿪻�رտ���̨", 0xFFFF1D44);
				ImHotKey::AddHotKey(u8"HotKeys", u8"��ݼ�����", 0xFFFF1D25);
				string HotKeyDir = "./HotKeys/";
				if (_access(HotKeyDir.c_str(), 0) == -1)
					_mkdir(HotKeyDir.c_str());
				init = true;
			}
			else
				return oPresent(pSwapChain, SyncInterval, Flags);
		}

		if (!Base::ModConfig::DrawInit)
			return oPresent(pSwapChain, SyncInterval, Flags);
		else if (mainRenderTargetView == nullptr) {
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
		}

		//��������
		int hotkey = ImHotKey::GetHotKey(ImHotKey::hotkeys.data(), ImHotKey::hotkeys.size());
		if (hotkey != -1)
		{
			if ((string)ImHotKey::hotkeys.at(hotkey).functionName == u8"Console") {
				Base::ModConfig::ModConsole = !Base::ModConfig::ModConsole;
			}
			if ((string)ImHotKey::hotkeys.at(hotkey).functionName == u8"HotKeys") {
				Base::ModConfig::HotKeyEdit = true;
			}
			Checkhotkey[(string)ImHotKey::hotkeys.at(hotkey).functionName] = true;
		}

		//��������
		if (!Base::SoundPlay::SoundList.empty()) {
			PlaySoundFile(Base::SoundPlay::SoundList.back());
			Base::SoundPlay::SoundList.pop_back();
		}
		
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		if (Base::ModConfig::ModConsole)
		{
			ImGui::SetNextWindowBgAlpha(0.35f);
			ImGui::Begin(u8"LuaScript ����̨");

			ImGui::Text(u8"LuaScript�汾��%s", Base::ModConfig::ModVersion);
			ImGui::Text(u8"SteamId��%d", Base::World::SteamId);
			
			if (ImGui::TreeNode(u8"Lua�ű��б�"))
			{
				if (ImGui::Button(u8"���½ű�����")) {
					for (string file_name : Base::LuaHandle::LuaFiles) { Base::LuaHandle::LuaCode[file_name].Update(); }
				}
				ImGui::SameLine();
				if (ImGui::Button(u8"����")) {
					Base::ModConfig::About = true;
				}
				for (string file_name : Base::LuaHandle::LuaFiles) {
					ImGui::TextColored(Base::LuaHandle::LuaCode[file_name].start ? ImVec4(0.0f, 0.8f, 0.0f, 1.0f) : ImVec4(0.8f, 0.0f, 0.0f, 1.0f), Component::string_To_UTF8(file_name).c_str());
					if (!Base::LuaHandle::LuaCode[file_name].hotReload) {
						ImGui::SameLine();
						ImGui::Checkbox((u8"����" + file_name).c_str(), &Base::LuaHandle::LuaCode[file_name].start);
					}
				}
				ImGui::TreePop();
				ImGui::Separator();
			}
			if (ImGui::TreeNode(u8"Lua�ű�����"))
			{
				ImGui::Text(u8"��ǰʱ�䣺%f", Base::Chronoscope::NowTime);
				if (ImGui::TreeNode(u8"��ʱ��"))
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
				if (ImGui::TreeNode(u8"��������"))
				{
					if (ImGui::TreeNode(u8"����"))
					{
						for (auto [VariableName, VariableData] : LuaData::IntVariable) {
							ImGui::Text(u8"%s: %d", VariableName.c_str(), VariableData);
						}
						ImGui::TreePop();
					}
					if (ImGui::TreeNode(u8"������"))
					{
						for (auto [VariableName, VariableData] : LuaData::FloatVariable) {
							ImGui::Text(u8"%s: %f", VariableName.c_str(), VariableData);
						}
						ImGui::TreePop();
					}
					if (ImGui::TreeNode(u8"�ַ���"))
					{
						for (auto [VariableName, VariableData] : LuaData::StringVariable) {
							ImGui::Text(u8"%s: %s", VariableName.c_str(), VariableData.c_str());
						}
						ImGui::TreePop();
					}
					ImGui::TreePop();
				}
				if (ImGui::TreeNode(u8"�����¼"))
				{
					ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
					ImGui::BeginChild("LuaErrList", ImVec2(ImGui::GetWindowContentRegionWidth(), 260), false, window_flags);
					for (auto iter = Base::LuaHandle::LuaError.cbegin(); iter != Base::LuaHandle::LuaError.cend(); iter++)
						ImGui::Text("Err: %s", *iter);
					ImGui::EndChild();
					ImGui::TreePop();
				}
				if (ImGui::Button(u8"��ݼ��༭")) {
					Base::ModConfig::HotKeyEdit = true;
				}
				ImGui::TreePop();
				ImGui::Separator();
			}
			if (ImGui::TreeNode(u8"��Ϸ����"))
			{
				ImGui::Text(u8"��ͼId��%d", Base::World::MapId);
				ImGui::Text(u8"��������%s", Base::World::Assembly);
				if (ImGui::TreeNode(u8"�����Ϣ"))
				{
					ImGui::Text(u8"�������%s", Base::PlayerData::Name);
					ImGui::Text(u8"����Id��%d", Base::PlayerData::ActionId);
					if (ImGui::TreeNode(u8"������Ϣ"))
					{
						ImGui::Text(u8"��ǰFsm��%d - %d", Base::PlayerData::NowFsm.Target, Base::PlayerData::NowFsm.Id);
						ImGui::Text(u8"��һ��ִ�е�Fsm��%d - %d", Base::PlayerData::Fsm.Target, Base::PlayerData::Fsm.Id);
						ImGui::Text(u8"��ǰ����֡��%f", Base::PlayerData::ActionFrame);
						ImGui::Text(u8"��ǰ����֡���ȣ�%f", Base::PlayerData::ActionFrameEnd);
						ImGui::Text(u8"��ǰ����֡���ʣ�%f", Base::PlayerData::ActionFrameSpeed);
						ImGui::TreePop();
					}
					ImGui::Text(u8"��ǰ������%f", Base::PlayerData::CurrentEndurance);
					ImGui::Text(u8"��ǰѪ����%f", Base::PlayerData::CurrentHealth);
					if (ImGui::TreeNode(u8"��ǰ����"))
					{
						ImGui::Text(u8"X��%f", Base::PlayerData::Coordinate::Entity.x);
						ImGui::Text(u8"Y��%f", Base::PlayerData::Coordinate::Entity.y);
						ImGui::Text(u8"Z��%f", Base::PlayerData::Coordinate::Entity.z);
						ImGui::TreePop();
					}
					if (ImGui::TreeNode(u8"ŷ����"))
					{
						ImGui::Text(u8"X��%f", Base::PlayerData::EulerAngle.x);
						ImGui::Text(u8"Y��%f", Base::PlayerData::EulerAngle.y);
						ImGui::Text(u8"Z��%f", Base::PlayerData::EulerAngle.z);
						ImGui::TreePop();
					}
					ImGui::Text(u8"����ǣ�%f", Base::PlayerData::Angle);
					ImGui::Text(u8"�������ͣ�%d", Base::PlayerData::Weapons::WeaponType);
					ImGui::Text(u8"����Id��%d", Base::PlayerData::Weapons::WeaponId);
					ImGui::Text(u8"�������ٶȣ�%f", Base::PlayerData::Gravity);
					ImGui::Text(u8"�������ʣ�%f", Base::PlayerData::Fallspeedrate);
					ImGui::TreePop();
				}
				if (ImGui::TreeNode(u8"��¶è��Ϣ"))
				{
					ImGui::Text(u8"����Id��%d", Base::Otomo::ActionId);
					if (ImGui::TreeNode(u8"������Ϣ"))
					{
						ImGui::Text(u8"��ǰFsm��%d - %d", Base::Otomo::NowFsm.Target, Base::Otomo::NowFsm.Id);
						ImGui::Text(u8"��һ��ִ�е�Fsm��%d - %d", Base::Otomo::Fsm.Target, Base::Otomo::Fsm.Id);
						ImGui::Text(u8"��ǰ����֡��%f", Base::Otomo::ActionFrame);
						ImGui::Text(u8"��ǰ����֡���ȣ�%f", Base::Otomo::ActionFrameEnd);
						ImGui::Text(u8"��ǰ����֡���ʣ�%f", Base::Otomo::ActionFrameSpeed);
						ImGui::TreePop();
					}
					if (ImGui::TreeNode(u8"��ǰ����"))
					{
						ImGui::Text(u8"X��%f", Base::Otomo::Coordinate::Entity.x);
						ImGui::Text(u8"Y��%f", Base::Otomo::Coordinate::Entity.y);
						ImGui::Text(u8"Z��%f", Base::Otomo::Coordinate::Entity.z);
						ImGui::TreePop();
					}
					ImGui::Text(u8"����ǣ�%f", Base::Otomo::Angle);
					ImGui::TreePop();
				}
				if (ImGui::TreeNode(u8"������Ϣ"))
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
								ImGui::Text(u8"�ڴ��ַ��%x", monsterData.Plot);
								ImGui::Text(u8"����Id��%d", monsterData.Id);
								ImGui::Text(u8"������֣�%d", monsterData.SubId);
								ImGui::Text(u8"��ǰѪ����%f", health);
								ImGui::Text(u8"���Ѫ����%f", maxHealth);
								if (ImGui::TreeNode(u8"��ǰ����"))
								{
									ImGui::Text(u8"X��%f", monsterData.CoordinatesX);
									ImGui::Text(u8"Y��%f", monsterData.CoordinatesY);
									ImGui::Text(u8"Z��%f", monsterData.CoordinatesZ);
									ImGui::TreePop();
								}
								float MonsterGravity = *offsetPtr<float>(monsterData.Plot, 0x14B0);
								ImGui::Text(u8"�������ٶȣ�%f", MonsterGravity);
								float MonsterAngle = Base::Calculation::QuaternionToAngle(Base::Vector4(
									*offsetPtr<float>(monsterData.Plot, 0x174),
									*offsetPtr<float>(monsterData.Plot, 0x178),
									*offsetPtr<float>(monsterData.Plot, 0x17C),
									*offsetPtr<float>(monsterData.Plot, 0x180)
								));
								ImGui::Text(u8"����ǣ�%f", MonsterAngle);
								int MonsterActionId = 0;
								float MonsterActionFrame = 0;
								float MonsterActionFrameEnd = 0;
								float MonsterActionFrameSpeed = 0;
								void* MonsterActionPlot = *offsetPtr<undefined**>((undefined(*)())monsterData.Plot, 0x468);
								if (MonsterActionPlot != nullptr) {
									MonsterActionId = *offsetPtr<int>(MonsterActionPlot, 0xE9C4);
									MonsterActionFrame = *offsetPtr<float>(MonsterActionPlot, 0x10C);
									MonsterActionFrameEnd = *offsetPtr<float>(MonsterActionPlot, 0x114);
								}
								MonsterActionFrameSpeed = *offsetPtr<float>(monsterData.Plot, 0x6c);
								Base::PlayerData::FsmData MonsterFsm = Base::PlayerData::FsmData();
								Base::PlayerData::FsmData MonsterNowFsm = Base::PlayerData::FsmData();
								MonsterFsm = Base::PlayerData::FsmData(
									*offsetPtr<int>(monsterData.Plot, 0x628C),
									*offsetPtr<int>(monsterData.Plot, 0x6290)
								);
								MonsterNowFsm = Base::PlayerData::FsmData(
									*offsetPtr<int>(monsterData.Plot, 0x6274),
									*offsetPtr<int>(monsterData.Plot, 0x6278)
								);
								ImGui::Text(u8"����Id��%d", MonsterActionId);
								if (ImGui::TreeNode(u8"������Ϣ"))
								{
									ImGui::Text(u8"��ǰFsm��%d - %d", MonsterNowFsm.Target, MonsterNowFsm.Id);
									ImGui::Text(u8"��һ��ִ�е�Fsm��%d - %d", MonsterFsm.Target, MonsterFsm.Id);
									ImGui::Text(u8"��ǰ����֡��%f", MonsterActionFrame);
									ImGui::Text(u8"��ǰ����֡���ȣ�%f", MonsterActionFrameEnd);
									ImGui::Text(u8"��ǰ����֡���ʣ�%f", MonsterActionFrameSpeed);
									ImGui::TreePop();
								}
								void* MonstersHate = Base::Monster::GetHateTarget(monster);
								ImGui::Text(u8"���Ŀ�꣺%s", MonstersHate != nullptr ?
									MonstersHate == Base::BasicGameData::PlayerPlot ? u8"���" : u8"����"
									: u8"��Ŀ��"
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
				if (ImGui::TreeNode(u8"����������Ϣ"))
				{
					for (auto [environmental, environmentalData] : Base::World::EnvironmentalData::Environmentals) {
						if (environmental != nullptr) {
							ostringstream ptr;
							ptr << environmentalData.Plot;
							string ptrstr = ptr.str();
							if (ImGui::TreeNode(ptrstr.c_str()))
							{
								ImGui::Text(u8"�ڴ��ַ��%x", environmentalData.Plot);
								ImGui::Text(u8"����Id��%d", environmentalData.Id);
								ImGui::Text(u8"������֣�%d", environmentalData.SubId);
								ImGui::Text(u8"��ǰ����");
								ImGui::Text(u8"X��%f", environmentalData.CoordinatesX);
								ImGui::Text(u8"Y��%f", environmentalData.CoordinatesY);
								ImGui::Text(u8"Z��%f", environmentalData.CoordinatesZ);
								ImGui::TreePop();
								ImGui::Separator();
							}
						}
					}
					ImGui::TreePop();
				}
				if (ImGui::TreeNode(u8"Ͷ������Ϣ"))
				{
					for (auto [projectiles, projectilesData] : Base::ProjectilesOperation::ProjectilesList) {
						if (projectiles != nullptr) {
							ostringstream ptr;
							ptr << projectilesData.Plot;
							string ptrstr = ptr.str();
							if (ImGui::TreeNode(ptrstr.c_str()))
							{
								ImGui::Text(u8"�ڴ��ַ��%x", projectilesData.Plot);
								ImGui::Text(u8"��ǰ����X��%f", projectilesData.CoordinatesX);
								ImGui::Text(u8"��ǰ����Y��%f", projectilesData.CoordinatesY);
								ImGui::Text(u8"��ǰ����Z��%f", projectilesData.CoordinatesZ);
								float MonsterAngle = Base::Calculation::QuaternionToAngle(Base::Vector4(
									*offsetPtr<float>(projectilesData.Plot, 0x174),
									*offsetPtr<float>(projectilesData.Plot, 0x178),
									*offsetPtr<float>(projectilesData.Plot, 0x17C),
									*offsetPtr<float>(projectilesData.Plot, 0x180)
								));
								ImGui::Text(u8"����ǣ�%f", MonsterAngle);
								ImGui::TreePop();
								ImGui::Separator();
							}
						}
					}
					ImGui::TreePop();
				}
				if (ImGui::TreeNode(u8"������Ϣ"))
				{
					ImGui::Text(u8"����Id��%d", Base::Quest::QuestId);
					ImGui::Text(u8"��һ������Id��%d", Base::Quest::NextQuest);
					ImGui::Text(u8"����״̬��%d", Base::Quest::QuestState);
				}
				ImGui::TreePop();
				ImGui::Separator();
			}
			ImGui::End();
		}
		//�ȼ�����
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysUseWindowPadding;
		ImGui::Begin("HotKeysEdit", NULL, window_flags);
		if (Base::ModConfig::HotKeyEdit) {
			Base::ModConfig::HotKeyEdit = false;
			ImHotKey::LoadHotKey();
			ImGui::OpenPopup(u8"�ȼ��༭��");
		}
		ImHotKey::Edit(ImHotKey::hotkeys.data(), ImHotKey::hotkeys.size(), u8"�ȼ��༭��");
		ImGui::End();
		//ͼƬ��ʾ
		for (auto [Begin, Data] : Base::Draw::Img) {
			if (ImgTextureCache.find(Data.ImageFile) != ImgTextureCache.end()) {
				if (ImgTextureCache[Data.ImageFile].texture == NULL) {
					if (Data.Base64) {
						bool ret = LoadTextureFromBase(Data.ImageFile, &ImgTextureCache[Data.ImageFile].texture, &ImgTextureCache[Data.ImageFile].width, &ImgTextureCache[Data.ImageFile].height, Data.Width, Data.Height);
						IM_ASSERT(ret);
					}
					else {
						bool ret = LoadTextureFromFile(Data.ImageFile.c_str(), &ImgTextureCache[Data.ImageFile].texture, &ImgTextureCache[Data.ImageFile].width, &ImgTextureCache[Data.ImageFile].height);
						IM_ASSERT(ret);
					}
				}
			}
			else {
				ImgTextureCache[Data.ImageFile] = TextureCache();
				if (Data.Base64) {
					bool ret = LoadTextureFromBase(Data.ImageFile, &ImgTextureCache[Data.ImageFile].texture, &ImgTextureCache[Data.ImageFile].width, &ImgTextureCache[Data.ImageFile].height, Data.Width, Data.Height);
					IM_ASSERT(ret);
				}
				else {
					bool ret = LoadTextureFromFile(Data.ImageFile.c_str(), &ImgTextureCache[Data.ImageFile].texture, &ImgTextureCache[Data.ImageFile].width, &ImgTextureCache[Data.ImageFile].height);
					IM_ASSERT(ret);
				}
			}
			//��������
			ImGui::SetNextWindowBgAlpha(0);
			ImGui::SetNextWindowPos(ImVec2(
				ImGui::GetMainViewport()->Pos.x + ImGui::GetMainViewport()->Size.x * Data.Pos.x,
				ImGui::GetMainViewport()->Pos.y + ImGui::GetMainViewport()->Size.y * Data.Pos.y
			), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
			ImGui::Begin(("IMG_" + Data.Name).c_str(), NULL, window_flags);
			ImVec2 DisplaySize = ImVec2(ImgTextureCache[Data.ImageFile].width, ImgTextureCache[Data.ImageFile].height);
			if (Data.DisplayHeight != 0 and Data.DisplayWidth != 0)
				DisplaySize = ImVec2(Data.DisplayWidth, Data.DisplayHeight);
			ImGui::Image((void*)ImgTextureCache[Data.ImageFile].texture, DisplaySize, ImVec2(0.0, 0.0), ImVec2(1.0, 1.0), ImVec4(Data.Channel.x, Data.Channel.y, Data.Channel.z, Data.BgAlpha));
			ImGui::End();
		}
		//������ʾ
		for (auto [Begin, Data] : Base::Draw::Text) {
			ImGui::SetNextWindowBgAlpha(0);
			ImGui::SetNextWindowPos(ImVec2(
				ImGui::GetMainViewport()->Pos.x + ImGui::GetMainViewport()->Size.x * Data.Pos.x,
				ImGui::GetMainViewport()->Pos.y + ImGui::GetMainViewport()->Size.y * Data.Pos.y
			), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
			ImGui::Begin(("TEXT_" + Data.Name).c_str(), NULL, window_flags);
			ImGui::SetWindowFontScale(Data.Size);
			ImGui::TextColored(ImVec4(Data.Color.x, Data.Color.y, Data.Color.z, Data.BgAlpha), Data.Text.c_str());
			ImGui::End();
		}
		//About
		if (Base::ModConfig::About) {
			ImGui::SetNextWindowBgAlpha(0.25f);
			ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
			ImGui::Begin("About");
			// Left
			static string selected = "LuaScript";
			{
				ImGui::BeginChild("left pane", ImVec2(150, 0), true);
				for (auto [title, text] : Base::Draw::About) {
					if (ImGui::Selectable(title.c_str(), selected == title))
						selected = title;
				}
				ImGui::EndChild();
			}
			ImGui::SameLine();
			// Right
			{
				ImGui::BeginGroup();
				ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
				ImGui::Text(selected.c_str());
				ImGui::Separator();
				ImGui::MarkdownConfig mdConfig{ NULL, NULL, NULL, NULL, NULL, NULL };
				ImGui::Markdown(Base::Draw::About[selected].c_str(), Base::Draw::About[selected].length(), mdConfig);
				ImGui::EndChild();
				if (ImGui::Button(u8"�ر�")) { Base::ModConfig::About = false; }
				ImGui::EndGroup();
			}
			ImGui::End();
		}
		//�豸����ˢ��
		ImGuiIO& io = ImGui::GetIO();
		Base::Draw::MouseDelta = Base::Vector2(io.MouseDelta.x, io.MouseDelta.y);

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
				kiero::bind(13, (void**)&oResize, hkResize);
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