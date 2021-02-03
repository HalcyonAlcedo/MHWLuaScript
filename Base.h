#pragma once
#include "ghidra_export.h"
#include "util.h"
#include "loader.h"
#include <map>

using namespace std;
using namespace loader;

extern "C" long long _stdcall Navigation(float*, float*, float*);
extern "C" void* _stdcall GetVisualPtr(void*);

namespace Base {
	//常用结构
	struct Vector3 {
		float x, y, z;
		Vector3(float x = 0, float y = 0, float z = 0) :x(x), y(y), z(z) {
		};
	};
	struct Vector2 {
		float x, y;
		Vector2(float x = 0, float y = 0) :x(x), y(y) {
		};
	};

	namespace ModConfig {
		//内置参数
		bool GameDataInit = false;
		bool InitErrInfo = true;
		int InitErrCount = 0;
		//可设置参数
		string ModName = "Blink";
		string ModAuthor = "Alcedo";
		string ModVersion = "v1.0";
		string Version = "421470";
	}
	//游戏基址数据
	namespace BasicGameData {
		void* PlayerPlot = nullptr;
		void* ActionPlot = nullptr;
		void* MapPlot = nullptr;
		void* GameTimePlot = nullptr;
	}
	//世界信息
	namespace World {
		//环境生物
		namespace EnvironmentalData {
			//缓存数据
			namespace TempData {
				void* t_environmental = nullptr;
				vector<void*> t_environmentalMessages;
			}

			struct EnvironmentalData {
				void* Plot = nullptr;
				float CoordinatesX = 0;
				float CoordinatesY = 0;
				float CoordinatesZ = 0;
				int Id = 0;
				int SubId = 0;
			};
			//环境生物列表
			map<void*, EnvironmentalData> Environmentals;
		}
		int MapId = 0;
	}
	//计时器
	namespace Chronoscope {
		struct ChronoscopeData {
			float StartTime = 0;
			float EndTime = 0;
		};

		//现在的时间
		float NowTime = 0;
		//计时器列表
		map<string, ChronoscopeData> ChronoscopeList;
		//添加计时器(时长，计时器名称，是否覆盖)
		static bool AddChronoscope(float duration, string name, bool Overlay = false) {
			if (ChronoscopeList.find(name) == ChronoscopeList.end() || Overlay) {
				ChronoscopeList[name].EndTime = NowTime + duration;
				ChronoscopeList[name].StartTime = NowTime;
				return true;
			}
			else
				return false;
		}
		//删除计时器
		static void DelChronoscope(string name) {
			if (ChronoscopeList.find(name) != ChronoscopeList.end()) {
				ChronoscopeList.erase(name);
			}
		}
		//检查计时器
		static bool CheckChronoscope(string name) {
			if (ChronoscopeList.find(name) != ChronoscopeList.end()) {
				if (ChronoscopeList[name].EndTime > NowTime)
					return true;
			}
			return false;
		}
	}
	//计算
	namespace Calculation {
		Vector3 GetVector(Vector3 p1, Vector3 p2, float l) {
			float a = (p2.x - p1.x);
			float b = (p2.y - p1.y);
			float c = (p2.z - p1.z);
			l = l * l / (a * a + b * b + c * c);
			float k = sqrt(l);
			float newx1 = k * a + p1.x;
			float newy1 = k * b + p1.y;
			float newz1 = k * c + p1.z;
			return Vector3(newx1, newy1, newz1);
		}
		Vector2 GetExtensionVector2D(Vector2 Coordinate,float r, float angle) {
			float x, y;
			x = Coordinate.x + r * cos((4 * atan(1.0) / 180 * angle));
			y = Coordinate.y + r * sin((4 * atan(1.0) / 180 * angle));
			return Vector2(x, y);
		}
		float myRander(float min, float max)
		{
			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_real_distribution<float> dist(min, max);
			return dist(eng);
		}
	}
	//图形绘制
	namespace Draw {
		HWND GameHandle;
		bool HandleInit = false;
		//初始化图形绘制
		static void InitDraw() {
			string GameName = "MONSTER HUNTER: WORLD(" + ModConfig::Version + ")";
			GameHandle = FindWindow(NULL, GameName.c_str());
			if(GameHandle != nullptr)
				HandleInit = true;
		}
		//绘制 待完善
		static void Draw() {
			HDC hdc = ::GetDC(GameHandle);
			RECT rect;
			::GetWindowRect(GameHandle, &rect);
			::MoveToEx(hdc, 0, 0, NULL);
			::LineTo(hdc, rect.right, rect.bottom);
			::MoveToEx(hdc, rect.right, 0, NULL);
			::LineTo(hdc, 0, rect.bottom);
			::ReleaseDC(GameHandle, hdc);
		}
	}
	//委托
	namespace Commission {
		namespace MoveEntity {
			struct Parameter {
				Vector3 Vector;
				void* Entity = nullptr;
				float speed = 100.0;
			};
			map<void*, Parameter> CommissionList;

			static void MoveEntityToTarget() {
				for (auto [entity, parameter] : CommissionList) {
					if (entity != nullptr) {
						//移动到目标
						if (parameter.Entity != nullptr) {
							float EntityX = *offsetPtr<float>(entity, 0x160);
							float EntityY = *offsetPtr<float>(entity, 0x160);
							float EntityZ = *offsetPtr<float>(entity, 0x160);
							float ToEntityX = *offsetPtr<float>(parameter.Entity, 0x160);
							float ToEntityY = *offsetPtr<float>(parameter.Entity, 0x160);
							float ToEntityZ = *offsetPtr<float>(parameter.Entity, 0x160);

							if (fabs(ToEntityX - EntityX) > float(10)) {
								if (ToEntityX < EntityX)
									EntityX -= float(fabs(ToEntityX - EntityX) / 10);
								else
									EntityX += float(fabs(ToEntityX - EntityX) / 10);
							}
							else
								EntityX = ToEntityX;

							if (fabs(ToEntityY - EntityY) > float(10)) {
								if (ToEntityY < EntityY)
									EntityY -= float(fabs(ToEntityY - EntityY) / parameter.speed);
								else
									EntityY += float(fabs(ToEntityY - EntityY) / parameter.speed);
							}
							else
								EntityY = ToEntityY;

							if (fabs(ToEntityZ - EntityZ) > float(10)) {
								if (ToEntityZ < EntityZ)
									EntityZ -= float(fabs(ToEntityZ - EntityZ) / 10);
								else
									EntityZ += float(fabs(ToEntityZ - EntityZ) / 10);
							}
							else
								EntityZ = ToEntityZ;

							*offsetPtr<float>(entity, 0x160) = ToEntityX;
							*offsetPtr<float>(entity, 0x164) = ToEntityY;
							*offsetPtr<float>(entity, 0x168) = ToEntityZ;

							if (
								*offsetPtr<float>(entity, 0x160) == ToEntityX and
								*offsetPtr<float>(entity, 0x164) == ToEntityY and
								*offsetPtr<float>(entity, 0x168) == ToEntityZ
								)
								CommissionList.erase(entity);
						}
						//移动到点
						else {
							float EntityX = *offsetPtr<float>(entity, 0x160);
							float EntityY = *offsetPtr<float>(entity, 0x160);
							float EntityZ = *offsetPtr<float>(entity, 0x160);
							float ToEntityX = parameter.Vector.x;
							float ToEntityY = parameter.Vector.y;
							float ToEntityZ = parameter.Vector.z;
							if (EntityX - ToEntityX > 10) {
								if (EntityX > ToEntityX)
									*offsetPtr<float>(entity, 0x160) -= (EntityX - ToEntityX) / parameter.speed;
								else
									*offsetPtr<float>(entity, 0x160) += (EntityX - ToEntityX) / parameter.speed;
							}
							else
								*offsetPtr<float>(entity, 0x160) = ToEntityX;
							if (EntityY - ToEntityY > 10) {
								if (EntityY > ToEntityY)
									*offsetPtr<float>(entity, 0x164) -= (EntityY - ToEntityY) / parameter.speed;
								else
									*offsetPtr<float>(entity, 0x164) += (EntityY - ToEntityY) / parameter.speed;
							}
							else
								*offsetPtr<float>(entity, 0x164) = ToEntityY;
							if (EntityZ - ToEntityZ > 10) {
								if (EntityZ > ToEntityZ)
									*offsetPtr<float>(entity, 0x168) -= (EntityZ - ToEntityZ) / parameter.speed;
								else
									*offsetPtr<float>(entity, 0x168) += (EntityZ - ToEntityZ) / parameter.speed;
							}
							else
								*offsetPtr<float>(entity, 0x168) = ToEntityZ;

							if (
								*offsetPtr<float>(entity, 0x160) == ToEntityX and
								*offsetPtr<float>(entity, 0x164) == ToEntityY and
								*offsetPtr<float>(entity, 0x168) == ToEntityZ
								)
								CommissionList.erase(entity);
						}
					}
				}
			}
		}

		static void CleanCommission() {
			MoveEntity::CommissionList.clear();
		}

		static void Run() {
			MoveEntity::MoveEntityToTarget();
		}
	}
	//怪物信息
	namespace Monster {
		struct MonsterData {
			void* Plot = nullptr;
			float CoordinatesX = 0;
			float CoordinatesY = 0;
			float CoordinatesZ = 0;
			int Id = 0;
			int SubId = 0;
		};
		//环境生物列表
		map<void*, MonsterData> Monsters;
	}
	//玩家信息
	namespace PlayerData {
		//坐标
		namespace Coordinate {
			struct Coordinate {
				float x, y, z;
				Coordinate(float x = 0, float y = 0, float z = 0) :x(x), y(y), z(z) {
				};
			};

			//缓存数据
			namespace TempData {
				void* t_visual = nullptr;
				Coordinate t_SetVisualCoordinate;
				void* t_SetVisualBind = nullptr;
				bool t_SetVisual = false;
				bool t_LockVisual = false;
			}

			//玩家坐标
			Coordinate Entity;
			//准星坐标
			Coordinate Collimator;
			//碰撞返回坐标
			Coordinate Collision;
			//增量坐标
			Coordinate Increment;
			//导航坐标
			Coordinate Navigation;
			//相机坐标
			Coordinate Visual;
			//玩家传送(X坐标,Y坐标,Z坐标,是否穿墙)
			static void TransportCoordinate(float X, float Y, float Z, bool Across = false) {
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x160) = X;
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x164) = Y;
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x168) = Z;
				if (Across) {
					*offsetPtr<float>(BasicGameData::PlayerPlot, 0xA50) = X;
					*offsetPtr<float>(BasicGameData::PlayerPlot, 0xA54) = Y;
					*offsetPtr<float>(BasicGameData::PlayerPlot, 0xA58) = Z;
				}
			}
		}
		//特效
		namespace Effects {
			//生成特效(特效组，特效id)
			static void GenerateSpecialEffects(int group, int record) {
				//仅仅这里用到，无需加入地址列表
				void* EffectsPlot = *(undefined**)MH::Player::EffectsBasePlot;
				void* EffectsOffset1 = *offsetPtr<undefined**>((undefined(*)())EffectsPlot, 0x80);
				void* EffectsOffset2 = *offsetPtr<undefined**>((undefined(*)())EffectsOffset1, 0xC0);
				void* EffectsOffset3 = *offsetPtr<undefined**>((undefined(*)())EffectsOffset2, 0x38);
				void* EffectsOffset4 = *offsetPtr<undefined**>((undefined(*)())EffectsOffset3, 0x58);
				void* EffectsOffset5 = *offsetPtr<undefined**>((undefined(*)())EffectsOffset4, 0x40);
				void* Effects = offsetPtr<void*>(EffectsOffset5, 0xD10);
				//特效添加
				MH::Player::Effects((undefined*)Effects, group, record);
			}
		}
		//相机设置(X坐标,Y坐标,Z坐标,持续时间0=长期)
		static void SetVisual(float X, float Y, float Z, float Duration = 0) {
			if (Duration != 0)
				Chronoscope::AddChronoscope(Duration, "SetVisual", true);
			else
				Coordinate::TempData::t_LockVisual = true;
			Coordinate::TempData::t_SetVisualCoordinate.x = X;
			Coordinate::TempData::t_SetVisualCoordinate.y = Y;
			Coordinate::TempData::t_SetVisualCoordinate.z = Z;
			Coordinate::TempData::t_SetVisual = true;
		}
		//相机绑定
		static void SetVisual(void* bind, float Duration = 0) {
			if (Duration != 0)
				Chronoscope::AddChronoscope(Duration, "SetVisual", true);
			else
				Coordinate::TempData::t_LockVisual = true;
			Coordinate::TempData::t_SetVisualBind = bind;
			Coordinate::TempData::t_SetVisual = true;
		}
		//解除相机设置
		static void UnbindVisual() {
			Coordinate::TempData::t_LockVisual = false;
			Coordinate::TempData::t_SetVisual = false;
		}
		//朝向角度
		float Angle;
		//朝向弧度
		float Radian;
		//是否处于瞄准状态
		bool AimingState;
		//最后一次击中的怪物地址
		void* AttackMonsterPlot = nullptr;
		//动作id
		float ActionId;
		//武器类型
		int WeaponType;
		//武器ID
		int WeaponId;
	}
	//按键信息
	namespace Keyboard {
		namespace TempData {
			map<int, bool> t_KeyDown;
			map<int, int> t_KeyCount;
		}
		//检查窗口
		static bool CheckWindows() {
			string GameName = "MONSTER HUNTER: WORLD(" + ModConfig::Version + ")";
			HWND wnd = GetForegroundWindow();;
			HWND mhd = FindWindow(NULL, GameName.c_str());
			if (wnd == mhd)
				return true;
			else
				return false;
		}
		//清理缓存
		static void ClearKey() {
			for (auto [Environmental, EData] : World::EnvironmentalData::Environmentals) {
				if (EData.Plot == nullptr) {
					World::EnvironmentalData::Environmentals.erase(Environmental);
				}
			}
		}
		//按键检查
		static bool CheckKey(int vk, int ComboClick = 1,float Duration = 0.3) {
			if (!CheckWindows())
				return false;
			//建立按键档案
			if (TempData::t_KeyDown.find(vk) == TempData::t_KeyDown.end()) {
				TempData::t_KeyDown[vk] = false;
			}
			//按键检查
			if (GetKeyState(vk) < 0 and !TempData::t_KeyDown[vk]) {
				TempData::t_KeyDown[vk] = true;
				//连击检查
				if (TempData::t_KeyCount.find(vk) != TempData::t_KeyCount.end()) {
					//计时器检查
					if(TempData::t_KeyCount[vk] == 1)
						Chronoscope::AddChronoscope(Duration, "KEY_" + to_string(vk), true);
					if (!Chronoscope::CheckChronoscope("KEY_" + to_string(vk))) {
						TempData::t_KeyCount[vk] = 0;
					}
					TempData::t_KeyCount[vk]++;
				}
				else {
					Chronoscope::AddChronoscope(Duration, "KEY_" + to_string(vk), true);
					TempData::t_KeyCount[vk] = 1;
				}

				//检查结果
				if (TempData::t_KeyCount[vk] == ComboClick)
					return true;
				else
					return false;
			}
			else if(GetKeyState(vk) >= 0)
				TempData::t_KeyDown[vk] = false;
			return false;
		}
	}
	//初始化
	static bool Init() {
		if (!ModConfig::GameDataInit) {
			void* PlayerPlot = *(undefined**)MH::Player::PlayerBasePlot;
			BasicGameData::PlayerPlot = *offsetPtr<undefined**>((undefined(*)())PlayerPlot, 0x50);
			BasicGameData::ActionPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x468);
			BasicGameData::GameTimePlot = (undefined(*)())MH::World::GmaeClock;
			BasicGameData::MapPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x7D20);
			if (
				BasicGameData::PlayerPlot != nullptr and
				BasicGameData::ActionPlot != nullptr and
				BasicGameData::MapPlot != nullptr and
				BasicGameData::GameTimePlot != nullptr
				) {
				//钩入数据
				MH_Initialize();
				//坐标数据获取
				HookLambda(MH::World::WaypointZLocal,
					[](auto x1, auto x2) {
						Navigation(
							&Base::PlayerData::Coordinate::Navigation.x,
							&Base::PlayerData::Coordinate::Navigation.y,
							&Base::PlayerData::Coordinate::Navigation.z
						);
						return original(x1, x2);
					});
				//环境生物地址获取
				HookLambda(MH::EnvironmentalBiological::ctor,
					[](auto rcx, auto rdx, auto r8, auto r9) {
						Base::World::EnvironmentalData::TempData::t_environmental = rcx;
						return original(rcx, rdx, r8, r9);
					});
				HookLambda(MH::EnvironmentalBiological::ctor_,
					[](auto unkn1) {
						bool addEnvironmental = true;
						vector<void*>::iterator it;
						for (it = Base::World::EnvironmentalData::TempData::t_environmentalMessages.begin(); it != Base::World::EnvironmentalData::TempData::t_environmentalMessages.end(); it++)
						{
							if (*it == Base::World::EnvironmentalData::TempData::t_environmental)
								addEnvironmental = false;
						}
						if (addEnvironmental)
							Base::World::EnvironmentalData::TempData::t_environmentalMessages.push_back(Base::World::EnvironmentalData::TempData::t_environmental);
						return original(unkn1);
					});
				//怪物地址获取
				HookLambda(MH::Monster::ctor,
					[](auto monster, auto id, auto subId) {
						auto ret = original(monster, id, subId);
						Base::Monster::Monsters[monster].Plot = monster;
						Base::Monster::Monsters[monster].CoordinatesX = *offsetPtr<float>(monster, 0x160);
						Base::Monster::Monsters[monster].CoordinatesY = *offsetPtr<float>(monster, 0x164);
						Base::Monster::Monsters[monster].CoordinatesZ = *offsetPtr<float>(monster, 0x168);
						Base::Monster::Monsters[monster].Id = id;
						Base::Monster::Monsters[monster].SubId = subId;
						return ret;
					});
				HookLambda(MH::Monster::dtor,
					[](auto monster) {
						Base::Monster::Monsters.erase(monster);
						return original(monster);
					});
				//视角相机坐标修改
				HookLambda(MH::Player::Visual,
					[]() {
						GetVisualPtr(&Base::PlayerData::Coordinate::TempData::t_visual);
						if (Base::PlayerData::Coordinate::TempData::t_visual != nullptr) {
							Base::PlayerData::Coordinate::Visual.x = *offsetPtr<float>(Base::PlayerData::Coordinate::TempData::t_visual, 0x0);
							Base::PlayerData::Coordinate::Visual.y = *offsetPtr<float>(Base::PlayerData::Coordinate::TempData::t_visual, 0x4);
							Base::PlayerData::Coordinate::Visual.z = *offsetPtr<float>(Base::PlayerData::Coordinate::TempData::t_visual, 0x8);
							if (Base::PlayerData::Coordinate::TempData::t_SetVisual) {
								*offsetPtr<float>(Base::PlayerData::Coordinate::TempData::t_visual, 0x0) = Base::PlayerData::Coordinate::TempData::t_SetVisualCoordinate.x;
								*offsetPtr<float>(Base::PlayerData::Coordinate::TempData::t_visual, 0x4) = Base::PlayerData::Coordinate::TempData::t_SetVisualCoordinate.y;
								*offsetPtr<float>(Base::PlayerData::Coordinate::TempData::t_visual, 0x8) = Base::PlayerData::Coordinate::TempData::t_SetVisualCoordinate.z;
							}
						}
						return original();
					});
				MH_ApplyQueued();
				ModConfig::GameDataInit = true;
				LOG(INFO) << ModConfig::ModName << " : Game data initialization complete!";
				LOG(INFO) << " |  Mod：" << ModConfig::ModName;
				LOG(INFO) << " |  Author：" << ModConfig::ModAuthor;
				LOG(INFO) << " |  Version：" << ModConfig::ModVersion;
				return true;
			}
			else {
				if (ModConfig::InitErrInfo) {
					LOG(ERR) << ModConfig::ModName << " : Game data initialization failed!";
					LOG(ERR) << "The following address failed to complete the initialization. We will try again later. If the address is still not initialized successfully, please contact the mod author for solution.";
					if (BasicGameData::PlayerPlot == nullptr)
						LOG(ERR) << " |  PlayerPlot";
					if (BasicGameData::ActionPlot == nullptr)
						LOG(ERR) << " |  ActionPlot";
					if (BasicGameData::MapPlot == nullptr)
						LOG(ERR) << " |  MapPlot";
					if (BasicGameData::GameTimePlot == nullptr)
						LOG(ERR) << " |  GameTimePlot";

					ModConfig::InitErrCount++;
					if (ModConfig::InitErrCount > 10)
						ModConfig::InitErrInfo = false;
				}
				return false;
			}
		}
		else
			return true;
	}
	//实时更新的数据
	static void RealTimeUpdate() {
		if (ModConfig::GameDataInit) {
			//实时更新地图地址信息
			BasicGameData::MapPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x7D20);
			//写入地图信息和清除数据
			if (World::MapId != *offsetPtr<int>(BasicGameData::MapPlot, 0xB88)) {
				World::MapId = *offsetPtr<int>(BasicGameData::MapPlot, 0xB88);
				//清除计时器数据
				Chronoscope::ChronoscopeList.clear();
				//清除环境生物数据
				World::EnvironmentalData::TempData::t_environmentalMessages.clear();
				World::EnvironmentalData::Environmentals.clear();
				//清除相机数据
				PlayerData::Coordinate::TempData::t_SetVisualBind = nullptr;
				PlayerData::Coordinate::TempData::t_SetVisual = false;
				PlayerData::Coordinate::TempData::t_LockVisual = false;
				//清理委托
				Commission::CleanCommission();
				//更新地址信息
				void* PlayerPlot = *(undefined**)MH::Player::PlayerBasePlot;
				BasicGameData::PlayerPlot = *offsetPtr<undefined**>((undefined(*)())PlayerPlot, 0x50);
				BasicGameData::ActionPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x468);
			}
			//清除死亡的环境生物
			for (auto [Environmental, EData] : World::EnvironmentalData::Environmentals) {
				if (EData.Plot == nullptr) {
					World::EnvironmentalData::Environmentals.erase(Environmental);
				}
			}
			//更新玩家数据
			PlayerData::Angle = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x198) * 180.0;
			PlayerData::Radian = 4 * atan(1.0) / 180 * PlayerData::Angle;
			PlayerData::Coordinate::Entity.x = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x160);
			PlayerData::Coordinate::Entity.y = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x164);
			PlayerData::Coordinate::Entity.z = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x168);
			PlayerData::Coordinate::Collision.x = *offsetPtr<float>(BasicGameData::PlayerPlot, 0xA50);
			PlayerData::Coordinate::Collision.y = *offsetPtr<float>(BasicGameData::PlayerPlot, 0xA54);
			PlayerData::Coordinate::Collision.z = *offsetPtr<float>(BasicGameData::PlayerPlot, 0xA58);
			PlayerData::Coordinate::Collimator.x = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x7D30);
			PlayerData::Coordinate::Collimator.y = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x7D34);
			PlayerData::Coordinate::Collimator.z = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x7D38);
			void* IncrementPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x468);
			if (IncrementPlot != nullptr) {
				PlayerData::Coordinate::Increment.x = *offsetPtr<float>(IncrementPlot, 0x7D30);
				PlayerData::Coordinate::Increment.y = *offsetPtr<float>(IncrementPlot, 0x7D34);
				PlayerData::Coordinate::Increment.z = *offsetPtr<float>(IncrementPlot, 0x7D38);
			}
			else {
				PlayerData::Coordinate::Increment.x = 0.0;
				PlayerData::Coordinate::Increment.y = 0.0;
				PlayerData::Coordinate::Increment.z = 0.0;
			}
			void* AimingStatePlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0xC0);
			if (AimingStatePlot != nullptr)
				PlayerData::AimingState = *offsetPtr<bool>(AimingStatePlot, 0xC28);
			else
				PlayerData::AimingState = false;
			void* AttackMonsterPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x4C0);
			void* AttackMonsterOffset1 = *offsetPtr<undefined**>((undefined(*)())AttackMonsterPlot, 0x98);
			void* AttackMonsterOffset2 = *offsetPtr<undefined**>((undefined(*)())AttackMonsterOffset1, 0xD8);
			PlayerData::AttackMonsterPlot = *offsetPtr<void*>(AimingStatePlot, 0x4298);
			PlayerData::ActionId = *offsetPtr<int>(BasicGameData::ActionPlot, 0xE9C4);
			void* WeaponPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0xc0);
			void* WeaponOffset1 = *offsetPtr<undefined**>((undefined(*)())WeaponPlot, 0x8);
			void* WeaponOffset2 = *offsetPtr<undefined**>((undefined(*)())WeaponOffset1, 0x78);
			PlayerData::WeaponType = *offsetPtr<int>(WeaponOffset2, 0x2E8);
			PlayerData::WeaponId = *offsetPtr<int>(WeaponOffset2, 0x2EC);
			//更新环境生物数据
			vector<void*>::iterator it;
			for (it = World::EnvironmentalData::TempData::t_environmentalMessages.begin(); it != World::EnvironmentalData::TempData::t_environmentalMessages.end(); it++)
			{
				if (*it != nullptr) {
					if (Base::World::EnvironmentalData::Environmentals.find(*it) == Base::World::EnvironmentalData::Environmentals.end()) {
						Base::World::EnvironmentalData::Environmentals[*it].Plot = *it;
						Base::World::EnvironmentalData::Environmentals[*it].CoordinatesX = *offsetPtr<float>(*it, 0x160);
						Base::World::EnvironmentalData::Environmentals[*it].CoordinatesY = *offsetPtr<float>(*it, 0x164);
						Base::World::EnvironmentalData::Environmentals[*it].CoordinatesZ = *offsetPtr<float>(*it, 0x168);
						Base::World::EnvironmentalData::Environmentals[*it].Id = *offsetPtr<int>(*it, 0x1AF0);
						Base::World::EnvironmentalData::Environmentals[*it].SubId = *offsetPtr<int>(*it, 0x1AF4);
					}
					else {
						//如果生物存在列表中就只更新坐标数据
						Base::World::EnvironmentalData::Environmentals[*it].CoordinatesX = *offsetPtr<float>(*it, 0x160);
						Base::World::EnvironmentalData::Environmentals[*it].CoordinatesY = *offsetPtr<float>(*it, 0x164);
						Base::World::EnvironmentalData::Environmentals[*it].CoordinatesZ = *offsetPtr<float>(*it, 0x168);
					}
				}
				else {
					World::EnvironmentalData::TempData::t_environmentalMessages.erase(it);
				}
			}
			//更新怪物信息
			for (auto [monster, monsterData] : Base::Monster::Monsters) {
				if (monster != nullptr) {
					Base::Monster::Monsters[monster].CoordinatesX = *offsetPtr<float>(monster, 0x160);
					Base::Monster::Monsters[monster].CoordinatesY = *offsetPtr<float>(monster, 0x164);
					Base::Monster::Monsters[monster].CoordinatesZ = *offsetPtr<float>(monster, 0x168);
				}
			}
			//更新计时器时间
			Chronoscope::NowTime = *offsetPtr<float>(BasicGameData::MapPlot, 0xC24);
			//检查相机计时器
			if (!Chronoscope::CheckChronoscope("SetVisual")) {
				if(!PlayerData::Coordinate::TempData::t_LockVisual)
					PlayerData::Coordinate::TempData::t_SetVisual = false;
				Chronoscope::DelChronoscope("SetVisual");
			}
			//清除相机绑定数据
			if (!PlayerData::Coordinate::TempData::t_SetVisual) {
				PlayerData::Coordinate::TempData::t_SetVisualBind = nullptr;
			}
			//设置相机绑定数据
			if (PlayerData::Coordinate::TempData::t_SetVisualBind != nullptr) {
				PlayerData::Coordinate::TempData::t_SetVisualCoordinate.x = *offsetPtr<float>(PlayerData::Coordinate::TempData::t_SetVisualBind, 0x160);
				PlayerData::Coordinate::TempData::t_SetVisualCoordinate.y = *offsetPtr<float>(PlayerData::Coordinate::TempData::t_SetVisualBind, 0x164);
				PlayerData::Coordinate::TempData::t_SetVisualCoordinate.z = *offsetPtr<float>(PlayerData::Coordinate::TempData::t_SetVisualBind, 0x168);
			}
			//运行委托
			Commission::Run();
		}
	}
}