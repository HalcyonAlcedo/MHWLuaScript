#pragma once
#include <map>
#include "MonsterBuff.h"
#include "PlayerBuff.h"
#include "Network.h"
#include "AobAddress.h"
#define GUID_LEN 64

using namespace std;
using namespace loader;

extern "C" long long _stdcall Navigation(float*, float*, float*);
extern "C" void* _stdcall GetRBXPtr(void*);
extern "C" void* _stdcall GetRDIPtr(void*);
extern "C" void* _stdcall GetHitPtr(void*);

namespace Base {
	//常用结构
	struct Vector3 {
		float x, y, z;
		Vector3(float x = 0, float y = 0, float z = 0) :x(x), y(y), z(z) { };
	};
	struct Vector2 {
		float x, y;
		Vector2(float x = 0, float y = 0) :x(x), y(y) { };
	};
#pragma region LuaHandle
	namespace LuaHandle {
		struct LuaCodeData {
			string name;
			string code;
			string file;
			bool start;
			bool hotReload;//hotReload模式下lua会直接读取文件而不通过缓存的数据执行代码
			void Update()
			{
				ifstream ifile(file);
				ostringstream buf;
				char ch;
				while (buf && ifile.get(ch))
					buf.put(ch);
				code = buf.str();
				if (string _Tmpy = "--NotHotReload"; string::npos != code.find(_Tmpy))
					hotReload = false;
				if (string _Tmpy = "--Disable"; string::npos != code.find(_Tmpy))
					start = false;
			};
			LuaCodeData(
				string name = "",
				string code = "",
				string file = "",
				bool start = true,
				bool hotReload = true
			) :name(name), code(code), file(file), start(start), hotReload(hotReload) { };
		};
		vector<string> LuaFiles;
		vector<string> LuaError;
		map<string, LuaCodeData> LuaCode;
	}
#pragma endregion
#pragma region ModConfig
	namespace ModConfig {
		//内置参数
		bool GameDataInit = false;
		bool InitErrInfo = true;
		int InitErrCount = 0;
		vector<string> LuaFiles;
		vector<string> LuaError;
		bool ModConsole = false;
		bool HotKeyEdit = false;
		//可设置参数
		string ModName = "LuaScript";
		string ModAuthor = "Alcedo";
		string ModVersion = "v1.1.9";
		long long ModBuild = 119004141229;
		string Version = "421470";
	}
#pragma endregion
	//游戏基础地址
#pragma region BasicGameData
	//游戏基址数据
	namespace BasicGameData {
		void* PlayerPlot = nullptr;
		void* PlayerInfoPlot = nullptr;
		void* PlayerDataPlot = nullptr;
		void* MapPlot = nullptr;
		void* GameTimePlot = nullptr;
		void* XboxPadPlot = nullptr;
	}
#pragma endregion
	//世界信息
#pragma region World
	namespace World {
		//环境生物
		namespace EnvironmentalData {
			struct EnvironmentalData {
				void* Plot = nullptr;
				float CoordinatesX = 0;
				float CoordinatesY = 0;
				float CoordinatesZ = 0;
				int Id = 0;
				int SubId = 0;
				EnvironmentalData(
					void* Plot = nullptr,
					float CoordinatesX = 0,
					float CoordinatesY = 0,
					float CoordinatesZ = 0,
					int Id = 0,
					int SubId = 0)
					:Plot(Plot), CoordinatesX(CoordinatesX), CoordinatesY(CoordinatesY), CoordinatesZ(CoordinatesZ), Id(Id), SubId(SubId) {
				};
			};
			//环境生物列表
			map<void*, EnvironmentalData> Environmentals;
			//怪物筛选器
			pair<int, int> Filter(255, 255);
		}
		int MapId = 0;
	}
#pragma endregion
	//计时器
#pragma region Chronoscope
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
		//检查计时器是否存在
		static bool CheckPresenceChronoscope(string name) {
			if (ChronoscopeList.find(name) != ChronoscopeList.end()) {
				return true;
			}
			return false;
		}
		//检查计时器是否结束
		static bool CheckChronoscope(string name) {
			if (ChronoscopeList.find(name) != ChronoscopeList.end()) {
				if (ChronoscopeList[name].EndTime < NowTime) {
					DelChronoscope(name);
					return true;
				}
				else
					return false;
			}
			return false;
		}
	}
#pragma endregion
	//计算
#pragma region Calculation
	namespace Calculation {
		static Vector3 GetVector(Vector3 p1, Vector3 p2, float l) {
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
		static Vector2 GetExtensionVector2D(Vector2 Coordinate,float r, float angle) {
			float x, y;
			x = Coordinate.x + r * cos((4 * atan(1.0) / 180 * angle));
			y = Coordinate.y + r * sin((4 * atan(1.0) / 180 * angle));
			return Vector2(x, y);
		}
		static float myRander(float min, float max)
		{
			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_real_distribution<float> dist(min, max);
			return dist(eng);
		}
		static float DistanceBetweenTwoCoordinates(Vector3 point1, Vector3 point2) {
			float RangeDistance = sqrt((point1.x - point2.x) * (point1.x - point2.x)) + sqrt((point1.z - point2.z) * (point1.z - point2.z));
			RangeDistance = sqrt((RangeDistance * RangeDistance) + sqrt((point1.y - point2.y) * (point1.y - point2.y)));
			return RangeDistance;
		}
		static string GetUUID() {
			char buffer[GUID_LEN] = { 0 };
			GUID guid;
			if (CoCreateGuid(&guid))
			{
				return "create guid error";
			}
			_snprintf_s(buffer, sizeof(buffer),
				"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
				guid.Data1, guid.Data2, guid.Data3,
				guid.Data4[0], guid.Data4[1], guid.Data4[2],
				guid.Data4[3], guid.Data4[4], guid.Data4[5],
				guid.Data4[6], guid.Data4[7]);
			return buffer;
		}
		static inline void QuaternionToAngleAxis(const float* quaternion,
			float* angle_axis) {
			const float q1 = quaternion[1];
			const float q2 = quaternion[2];
			const float q3 = quaternion[3];
			const float sin_squared_theta = q1 * q1 + q2 * q2 + q3 * q3;

			// For quaternions representing non-zero rotation, the conversion
			// is numerically stable.
			if (sin_squared_theta > 0.0f) {
				const float sin_theta = sqrt(sin_squared_theta);
				const float cos_theta = quaternion[0];


				const float two_theta =
					2.0 * ((cos_theta < 0.0)
						? atan2(-sin_theta, -cos_theta)
						: atan2(sin_theta, cos_theta));
				const float k = two_theta / sin_theta;
				angle_axis[0] = q1 * k;
				angle_axis[1] = q2 * k;
				angle_axis[2] = q3 * k;
			}
			else {
				// For zero rotation, sqrt() will produce NaN in the derivative since
				// the argument is zero. By approximating with a Taylor series,
				// and truncating at one term, the value and first derivatives will be
				// computed correctly when Jets are used.
				angle_axis[0] = q1 * 2.0f;
				angle_axis[1] = q2 * 2.0f;
				angle_axis[2] = q3 * 2.0f;
			}
		}
	}
#pragma endregion
	//图形绘制
#pragma region Draw
	namespace Draw {
		struct NewImage {
			float BgAlpha = 0;
			Vector2 Pos = Vector2();
			string Name = "";
			string ImageFile = "";
			NewImage(
				float BgAlpha = 0,
				Vector2 Pos = Vector2(),
				string Name = "",
				string ImageFile = ""
				) :BgAlpha(BgAlpha), Pos(Pos), Name(Name), ImageFile(ImageFile) { };
		};
		map<string, NewImage> Img;
	}
#pragma endregion
	//委托
#pragma region Commission
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
#pragma endregion
	//怪物信息
#pragma region Monster
	namespace Monster {
		struct MonsterData {
			void* Plot;
			float CoordinatesX;
			float CoordinatesY;
			float CoordinatesZ;
			int Id;
			int SubId;
			MonsterData(
				void* Plot = nullptr,
				float CoordinatesX = 0,
				float CoordinatesY = 0,
				float CoordinatesZ = 0,
				int Id = 0,
				int SubId = 0) 
				:Plot(Plot), CoordinatesX(CoordinatesX), CoordinatesY(CoordinatesY), CoordinatesZ(CoordinatesZ), Id(Id), SubId(SubId){
			};
		};
		//怪物列表
		map<void*, MonsterData> Monsters;
		//怪物筛选器
		pair<int, int> Filter(255,255);
		//给怪物设置buff
		static void SetBuff(void* monster,string buff){
			MonsterBuff::MonsterBuffState monsterBuff = MonsterBuff::GetMonsterBuffState(monster,buff);
			if (monsterBuff.MaxStateValue != 0) {
				MonsterBuff::SetMonsterBuffState(monster, buff);
			}
		}
		//获取怪物buff状态
		static MonsterBuff::MonsterBuffState GetBuff(void* monster, string buff) {
			return MonsterBuff::GetMonsterBuffState(monster, buff);
		}
		//获取怪物buff状态
		static void* GetHateTarget(void* monster) {
			void* HateTargetOffset1 = *offsetPtr<undefined**>((undefined(*)())monster, 0x98);
			void* HateTargetOffset2 = nullptr;
			if (HateTargetOffset1 != nullptr)
				HateTargetOffset2 = *offsetPtr<undefined**>((undefined(*)())HateTargetOffset1, 0x1B0);
			void* HateTargetOffset3 = nullptr;
			if (HateTargetOffset2 != nullptr)
				HateTargetOffset3 = *offsetPtr<undefined**>((undefined(*)())HateTargetOffset2, 0x8);
			void* HateTargetOffset4 = nullptr;
			if (HateTargetOffset3 != nullptr)
				HateTargetOffset4 = *offsetPtr<undefined**>((undefined(*)())HateTargetOffset3, 0x970);
			if (HateTargetOffset4 != nullptr)
				return *offsetPtr<void*>(HateTargetOffset4, 0x5D0);
			return nullptr;
		}
		//设置怪物派生动作
		static void BehaviorControl(void* monster, int Fsm) {
			//感谢南风焓大佬提供的地址
			MH::Monster::BehaviorControl((undefined*)monster, Fsm);
		}
	}
#pragma endregion
	//玩家信息
#pragma region PlayerData
	namespace PlayerData {
		struct FsmData {
			//对象 0为人物3为武器
			int Target = 0;
			//执行Id
			int Id = 0;
			FsmData(int Target = 0, int Id = 0) :Target(Target), Id(Id) {
			};
		};

		//缓存数据
		namespace TempData {
			FsmData t_ManualFsmAction;
			bool t_executingFsmAction = false;
			void* t_HookCoordinate = nullptr;
			void* t_HookCoordinate2 = nullptr;
		}

		//坐标
		namespace Coordinate {
			//缓存数据
			namespace TempData {
				void* t_visual = nullptr;
				Vector3 t_SetVisualCoordinate;
				void* t_SetVisualBind = nullptr;
				bool t_SetVisual = false;
			}

			//玩家坐标
			Vector3 Entity = Vector3();
			//准星坐标
			Vector3 Collimator = Vector3();
			//抛物线准星坐标
			Vector3 Parabola = Vector3();
			//碰撞返回坐标
			Vector3 Collision = Vector3();
			//增量坐标
			Vector3 Increment = Vector3();
			//导航坐标
			Vector3 Navigation = Vector3();
			//相机坐标
			Vector3 Visual = Vector3();
			//武器坐标
			Vector3 Weapon = Vector3();
			//钩爪坐标
			Vector3 Hook = Vector3();
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
		//武器装饰物
		namespace WeaponOrnaments {
			//缓存数据
			namespace TempData {
				void* t_ornaments = nullptr;
				bool t_setOrnamentsCoordinate = false;
				Vector3 t_SetOrnamentsCoordinate;
				bool t_setOrnamentsSize = false;
				Vector3 t_SetOrnamentsSize;
			}
			//装饰物坐标
			Vector3 OrnamentsCoordinate = Vector3();
			//装饰物模型大小
			Vector3 OrnamentsSize = Vector3();

			//解除装饰物坐标控制
			static void DecontrolOrnamentsCoordinate() {
				TempData::t_setOrnamentsCoordinate = false;
			}
			//解除装饰物大小控制
			static void DecontrolOrnamentsSize() {
				TempData::t_setOrnamentsSize = false;
			}
			//装饰物坐标设置(X坐标,Y坐标,Z坐标)
			static void SetOrnamentsCoordinate(float X, float Y, float Z) {
				TempData::t_SetOrnamentsCoordinate = Vector3(X,Y,Z);
				TempData::t_setOrnamentsCoordinate = true;
			}
			//装饰物大小设置(X坐标,Y坐标,Z坐标)
			static void SetOrnamentsSize(float X, float Y, float Z) {
				TempData::t_SetOrnamentsSize = Vector3(X, Y, Z);
				TempData::t_setOrnamentsSize = true;
			}
		}
		//武器
		namespace Weapons {
			//缓存数据
			namespace TempData {
				void* t_mainWeapon = nullptr;
				void* t_secondaryWeapon = nullptr;
				void* t_weaponHit = nullptr;
				bool t_setMainWeaponCoordinate = false;
				Vector3 t_SetMainWeaponCoordinate;
				bool t_setMainWeaponSize = false;
				Vector3 t_SetMainWeaponSize;
				bool t_setSecondaryWeaponCoordinate = false;
				Vector3 t_SetSecondaryWeaponCoordinate;
				bool t_setSecondaryWeaponSize = false;
				Vector3 t_SetSecondaryWeaponSize;
			}
			//武器类型
			int WeaponType = 0;
			//武器ID
			int WeaponId = 0;
			//主武器坐标
			Vector3 MainWeaponCoordinate = Vector3();
			//主武器模型大小
			Vector3 MainWeaponSize = Vector3();
			//副武器坐标
			Vector3 SecondaryWeaponCoordinate = Vector3();
			//副武器模型大小
			Vector3 SecondaryWeaponSize = Vector3();
			//武器命中坐标
			Vector3 HitCoordinate = Vector3();
			//更换武器（武器类型，武器ID）
			static void ChangeWeapons(int type, int id, bool Complete = true) {
				if (type <= 13 and type >= 0 and id >= 0) {
					if (Complete) {
						*offsetPtr<int>(BasicGameData::PlayerPlot, 0x13860) = type;
						*offsetPtr<int>(BasicGameData::PlayerPlot, 0x13864) = id;
						MH::Weapon::CompleteChangeWeapon(BasicGameData::PlayerPlot, 1, 0);
					}
					else
						MH::Weapon::ChangeWeapon(BasicGameData::PlayerPlot, type, id);
				}
			}
			//解除主武器坐标控制
			static void DecontrolMainWeaponCoordinate() {
				TempData::t_setMainWeaponCoordinate = false;
			}
			//解除主武器大小控制
			static void DecontrolMainWeaponSize() {
				TempData::t_setMainWeaponSize = false;
			}
			//主武器坐标设置(X坐标,Y坐标,Z坐标)
			static void SetMainWeaponCoordinate(float X, float Y, float Z) {
				TempData::t_SetMainWeaponCoordinate = Vector3(X, Y, Z);
				TempData::t_setMainWeaponCoordinate = true;
			}
			//主武器大小设置(X坐标,Y坐标,Z坐标)
			static void SetMainWeaponSize(float X, float Y, float Z) {
				TempData::t_SetMainWeaponSize = Vector3(X, Y, Z);
				TempData::t_setMainWeaponSize = true;
			}

			//解除副武器坐标控制
			static void DecontrolSecondaryWeaponCoordinate() {
				TempData::t_setSecondaryWeaponCoordinate = false;
			}
			//解除副武器大小控制
			static void DecontrolSecondaryWeaponSize() {
				TempData::t_setSecondaryWeaponSize = false;
			}
			//副武器坐标设置(X坐标,Y坐标,Z坐标)
			static void SetSecondaryWeaponCoordinate(float X, float Y, float Z) {
				TempData::t_SetSecondaryWeaponCoordinate = Vector3(X, Y, Z);
				TempData::t_setSecondaryWeaponCoordinate = true;
			}
			//副武器大小设置(X坐标,Y坐标,Z坐标)
			static void SetSecondaryWeaponSize(float X, float Y, float Z) {
				TempData::t_SetSecondaryWeaponSize = Vector3(X, Y, Z);
				TempData::t_setSecondaryWeaponSize = true;
			}
		}
		//特效
		namespace Effects {
			//生成特效(特效组，特效id)
			static void GenerateSpecialEffects(int group, int record) {
				//感谢南风焓大佬提供的地址
				void* Effects = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x8808);
				//特效添加
				MH::Player::Effects((undefined*)Effects, group, record);
			}
		}
		//相机绑定
		static void SetVisual(void* bind, float Duration = 0) {
			Coordinate::TempData::t_SetVisualBind = bind;
			Coordinate::TempData::t_SetVisual = true;
		}
		//解除相机设置
		static void UnbindVisual() {
			Coordinate::TempData::t_SetVisual = false;
			Coordinate::TempData::t_SetVisualBind = nullptr;
		}
		//相机设置(X坐标,Y坐标,Z坐标,持续时间0=长期)
		static void SetVisual(float X, float Y, float Z, float Duration = 0) {
			Coordinate::TempData::t_SetVisualCoordinate.x = X;
			Coordinate::TempData::t_SetVisualCoordinate.y = Y;
			Coordinate::TempData::t_SetVisualCoordinate.z = Z;
			Coordinate::TempData::t_SetVisual = true;
		}
		//朝向角度
		float Angle = 0;
		//朝向弧度
		float Radian = 0;
		//欧拉角
		Vector3 EulerAngle = Vector3();
		//相机距离
		float VisualDistance = 0;
		//是否处于瞄准状态
		bool AimingState = false;
		//最后一次击中的怪物地址
		void* AttackMonsterPlot = nullptr;
		//动作id
		int ActionId = 0;
		//派生信息
		FsmData Fsm = FsmData();
		FsmData NowFsm = FsmData();
		//玩家名称
		string Name = "";
		//hr等级
		int Hr = 0;
		//mr等级
		int Mr = 0;
		//当前血量
		float CurrentHealth = 0;
		//基础血量（0-150）
		float BasicHealth = 0;
		//血量上限
		float MaxHealth = 0;
		//当前耐力
		float CurrentEndurance = 0;
		//耐力上限（25-150）
		float MaxEndurance = 0;
		//执行派生动作(执行对象,执行Id)
		static void RunDerivedAction(int type, int id) {
			TempData::t_ManualFsmAction = FsmData(type, id);
			TempData::t_executingFsmAction = true;
			*offsetPtr<int>(BasicGameData::PlayerPlot, 0x6284) = type;
			*offsetPtr<int>(BasicGameData::PlayerPlot, 0x6288) = id;
			*offsetPtr<int>(BasicGameData::PlayerPlot, 0x628C) = type;
			*offsetPtr<int>(BasicGameData::PlayerPlot, 0x6290) = id;
			Fsm = FsmData(type, id);
		}
		//检查执行派生动作是否结束
		static bool CheckDerivedAction() {
			if (TempData::t_executingFsmAction) {
				if (NowFsm.Id != TempData::t_ManualFsmAction.Id and NowFsm.Target != TempData::t_ManualFsmAction.Target) {
					TempData::t_executingFsmAction = false;
					return true;
				}
				else
					return false;
			}
			return false;
		}
		//获取玩家Buff持续时间
		static float GetPlayerBuff(string buff) {
			void* BuffsPlot = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x7D20);
			int buffPtr = PlayerBuff::GetBuffPtr(buff);
			return *offsetPtr<float>(BuffsPlot, buffPtr);
		}
		//设置玩家Buff持续时间
		static void SetPlayerBuff(string buff, float duration) {
			void* BuffsPlot = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x7D20);
			int buffPtr = PlayerBuff::GetBuffPtr(buff);
			*offsetPtr<float>(BuffsPlot, buffPtr) = duration;
		}
		//钩爪变更坐标
		Vector3 HookCoordinateChange = Vector3();
		//钩爪变更坐标
		bool HookChange = false;
		//玩家数据更新
		static void Updata() {
			Coordinate::Entity = Vector3(
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x160),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x164),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x168)
			);
			Coordinate::Collision = Vector3(
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0xA50),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0xA54),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0xA58)
			);
			Coordinate::Collimator = Vector3(
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x7D30),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x7D34),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x7D38)
			);
			Coordinate::Parabola = Vector3(
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x7D40),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x7D44),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x7D48)
			);
			void* WeaponEntityPlot = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x76B0);
			if(WeaponEntityPlot != nullptr)
				Coordinate::Weapon = Vector3(
					*offsetPtr<float>(WeaponEntityPlot, 0x160),
					*offsetPtr<float>(WeaponEntityPlot, 0x164),
					*offsetPtr<float>(WeaponEntityPlot, 0x168)
				);
			VisualDistance = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x7690);
			Coordinate::Increment = Vector3(
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x1530),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x1534),
				*offsetPtr<float>(BasicGameData::PlayerPlot, 0x1538));
			/*
			void* IncrementPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x468);
			if (IncrementPlot != nullptr) {
				Coordinate::Increment.x = *offsetPtr<float>(IncrementPlot, 0x7D30);
				Coordinate::Increment.y = *offsetPtr<float>(IncrementPlot, 0x7D34);
				Coordinate::Increment.z = *offsetPtr<float>(IncrementPlot, 0x7D38);
			}
			else {
				Coordinate::Increment.x = 0.0;
				Coordinate::Increment.y = 0.0;
				Coordinate::Increment.z = 0.0;
			}
			*/
			void* AimingStatePlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0xC0);
			if (AimingStatePlot != nullptr)
				AimingState = *offsetPtr<bool>(AimingStatePlot, 0xC28);
			else
				AimingState = false;
			if (BasicGameData::PlayerDataPlot != nullptr) {
				AttackMonsterPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerDataPlot, 0x2C8);
				EulerAngle = Vector3(
					*offsetPtr<float>(BasicGameData::PlayerDataPlot, 0x1F0),
					*offsetPtr<float>(BasicGameData::PlayerDataPlot, 0x1F4),
					*offsetPtr<float>(BasicGameData::PlayerDataPlot, 0x1F8)
				);
				Angle = EulerAngle.x * 180;
				Radian = 4 * atan(1.0) / 180 * PlayerData::Angle;
			}
			else {
				void* PlayerDataHandlePlot = *(undefined**)MH::Player::PlayerDataHandlePlot;
				void* PlayerDataHandleOffset1 = nullptr;
				if (PlayerDataHandlePlot != nullptr)
					PlayerDataHandleOffset1 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandlePlot, 0x48);
				void* PlayerDataHandleOffset2 = nullptr;
				if (PlayerDataHandleOffset1 != nullptr)
					PlayerDataHandleOffset2 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset1, 0x58);
				void* PlayerDataHandleOffset3 = nullptr;
				if (PlayerDataHandleOffset2 != nullptr)
					PlayerDataHandleOffset3 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset2, 0x58);
				void* PlayerDataHandleOffset4 = nullptr;
				if (PlayerDataHandleOffset3 != nullptr)
					PlayerDataHandleOffset4 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset3, 0x40);
				void* PlayerDataHandleOffset5 = nullptr;
				if (PlayerDataHandleOffset4 != nullptr)
					PlayerDataHandleOffset5 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset4, 0xD0);
				if (PlayerDataHandleOffset5 != nullptr)
					BasicGameData::PlayerDataPlot = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset5, 0x8);
			}
			void* ActionPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x468);
			if (ActionPlot != nullptr) {
				ActionId = *offsetPtr<int>(ActionPlot, 0xE9C4);
				void* HookOffset1 = *offsetPtr<undefined**>((undefined(*)())ActionPlot, 0x70);
				void* HookOffset2 = nullptr;
				if(HookOffset1 != nullptr)
					HookOffset2 = *offsetPtr<undefined**>((undefined(*)())HookOffset1, 0x10);
				void* HookOffset3 = nullptr;
				if (HookOffset2 != nullptr)
					HookOffset3 = *offsetPtr<undefined**>((undefined(*)())HookOffset2, 0x18);
				if (HookOffset3 != nullptr)
				Coordinate::Hook = Vector3(
					*offsetPtr<float>(HookOffset3, 0x160),
					*offsetPtr<float>(HookOffset3, 0x164),
					*offsetPtr<float>(HookOffset3, 0x168)
				);
			}
			else {
				ActionId = 0;
				Coordinate::Hook = Vector3();
			}
			void* WeaponPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0xc0);
			void* WeaponOffset1 = *offsetPtr<undefined**>((undefined(*)())WeaponPlot, 0x8);
			void* WeaponOffset2 = *offsetPtr<undefined**>((undefined(*)())WeaponOffset1, 0x78);
			Weapons::WeaponType = *offsetPtr<int>(WeaponOffset2, 0x2E8);
			Weapons::WeaponId = *offsetPtr<int>(WeaponOffset2, 0x2EC);
			Fsm = FsmData(
				*offsetPtr<int>(BasicGameData::PlayerPlot, 0x628C),
				*offsetPtr<int>(BasicGameData::PlayerPlot, 0x6290)
			);
			NowFsm = FsmData(
				*offsetPtr<int>(BasicGameData::PlayerPlot, 0x6274),
				*offsetPtr<int>(BasicGameData::PlayerPlot, 0x6278)
			);
			BasicHealth = *offsetPtr<float>(BasicGameData::PlayerPlot, 0x7628);
			void* StatusManagementPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x7630);
			if (StatusManagementPlot != nullptr) {
				CurrentHealth = *offsetPtr<float>(StatusManagementPlot, 0x64);
				MaxHealth = *offsetPtr<float>(StatusManagementPlot, 0x60);
				CurrentEndurance = *offsetPtr<float>(StatusManagementPlot, 0x13C);
				MaxEndurance = *offsetPtr<float>(StatusManagementPlot, 0x144);
			}
			else {
				CurrentHealth = 0;
				MaxHealth = 0;
				CurrentEndurance = 0;
				MaxEndurance = 0;
			}
			/*
			char* PlayerName = offsetPtr<char>(BasicGameData::PlayerInfoPlot, 0x50);
			if(strcmp(PlayerName, "\0")) Name = PlayerName;
			*/
			Hr = *offsetPtr<int>(BasicGameData::PlayerInfoPlot, 0x90);
			Mr = *offsetPtr<int>(BasicGameData::PlayerInfoPlot, 0xD4);
		}
	}
#pragma endregion
	//按键信息
#pragma region Keyboard
	namespace Keyboard {
		namespace TempData {
			map<int, bool> t_KeyDown;
			map<int, int> t_KeyCount;
		}
		//检查窗口
		static bool CheckWindows() {
			string GameName = "MONSTER HUNTER: WORLD(" + ModConfig::Version + ")";
			HWND wnd = GetForegroundWindow();;
			HWND mhd = FindWindow("MT FRAMEWORK", GameName.c_str());
			if (wnd == mhd)
				return true;
			else
				return false;
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
					if (Chronoscope::CheckChronoscope("KEY_" + to_string(vk))) {
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
#pragma endregion
	//投射物
#pragma region ProjectilesOperation
	namespace ProjectilesOperation {
		//执行投射物生成
		static bool CallProjectilesGenerate(int Id, float* Coordinate, int From = 0) {
			//武器发出的投射物
			void* Weapon = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x76B0);
			void* WeaponShlpPlot= *offsetPtr<void*>(Weapon, 0x1D90);
			//手弩发出的投射物
			void* BowgunShlpPlot = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x56E8);
			if (WeaponShlpPlot == nullptr || BowgunShlpPlot == nullptr)
				return false;

			void* ShlpPlot = nullptr;
			switch (From)
			{
			case 0:
				ShlpPlot = WeaponShlpPlot;
				break;
			case 1:
				ShlpPlot = BowgunShlpPlot;
				break;
			default:
				return false;
			}

			void* ShlpRoute = MH::Shlp::GetShlp(ShlpPlot, Id);
			if (ShlpRoute == nullptr)
				return false;
			ShlpRoute = *offsetPtr<void*>(ShlpRoute, 0x8);
			MH::Shlp::CallShlp(ShlpRoute, BasicGameData::PlayerPlot, BasicGameData::PlayerPlot, Coordinate);
			return true;
		}
		//处理投射物路径数据
		static void GenerateProjectilesCoordinateData(float*& CalculationCoordinates,Vector3 startPoint, Vector3 endPoint) {
			//缓存指针
			float* temp_float = CalculationCoordinates;
			//写入起始坐标
			*temp_float = startPoint.x;
			temp_float++;
			*temp_float = startPoint.y;
			temp_float++;
			*temp_float = startPoint.z;
			temp_float++;
			//起始坐标写入完成，空4个字节
			*temp_float = 0;
			temp_float++;
			//更换指针为单字节并写入1
			unsigned char* temp_byte = (unsigned char*)temp_float;
			*temp_byte = 1;

			//重设缓存指针至坐标地址40处
			temp_float = offsetPtr<float>(CalculationCoordinates, 0x40);
			//写入结束坐标
			*temp_float = endPoint.x;
			temp_float++;
			*temp_float = endPoint.y;
			temp_float++;
			*temp_float = endPoint.z;
			temp_float++;
			//结束坐标写入完成，空4个字节
			*temp_float = 0;
			temp_float++;
			//更换指针为单字节并写入1
			temp_byte = (unsigned char*)temp_float;
			*temp_byte = 1;

			//重设缓存指针至坐标地址A0处
			int* tempCoordinateTailData = offsetPtr<int>(CalculationCoordinates, 0xA0);
			//写入坐标数据尾部信息
			*tempCoordinateTailData = 0x12;
			tempCoordinateTailData++;
			longlong* tempCoordinateTailData_longlong = (longlong*)tempCoordinateTailData;
			*tempCoordinateTailData_longlong = -1;
		}
		//生成投射物
		static bool CreateProjectiles(int Id, Vector3 startPoint, Vector3 endPoint, int From = 0) {
			//创建投射物路径数据缓存指针
			float* CoordinatesData = new float[73];
			//填充缓存区数据
			memset(CoordinatesData, 0, 73 * 4);
			//处理投射物路径数据
			GenerateProjectilesCoordinateData(CoordinatesData, startPoint, endPoint);
			//执行生成投射物
			bool GenerateResults = CallProjectilesGenerate(Id, CoordinatesData, From);
			//清理缓冲区
			delete[]CoordinatesData;
			return GenerateResults;
		}
	}
#pragma endregion
	//Xbox手柄信息
#pragma region XboxPad
	namespace XboxPad {
		namespace TempData {
			map<int, bool> t_KeyDown;
			map<int, int> t_KeyCount;
		}
		namespace KeyState {
			bool LJoystickUp = false;
			bool LJoystickRight = false;
			bool LJoystickDown = false;
			bool LJoystickLeft = false;
			bool LJoystickPress = false;
			bool RJoystickUp = false;
			bool RJoystickRight = false;
			bool RJoystickDown = false;
			bool RJoystickLeft = false;
			bool RJoystickPress = false;
			bool LT = false;
			bool RT = false;
			bool LB = false;
			bool RB = false;
			bool Up = false;
			bool Right = false;
			bool Down = false;
			bool Left = false;
			bool Y = false;
			bool B = false;
			bool A = false;
			bool X = false;
			bool Window = false;
			bool Menu = false;
		}
		static bool KeyIdHandle(int Id) {
			switch (Id)
			{
			case 0:
				return KeyState::LJoystickUp;
			case 1:
				return KeyState::LJoystickRight;
			case 2:
				return KeyState::LJoystickDown;
			case 3:
				return KeyState::LJoystickLeft;
			case 4:
				return KeyState::LJoystickPress;
			case 5:
				return KeyState::RJoystickUp;
			case 6:
				return KeyState::RJoystickRight;
			case 7:
				return KeyState::RJoystickDown;
			case 8:
				return KeyState::RJoystickLeft;
			case 9:
				return KeyState::RJoystickPress;
			case 10:
				return KeyState::LT;
			case 11:
				return KeyState::RT;
			case 12:
				return KeyState::LB;
			case 13:
				return KeyState::RB;
			case 14:
				return KeyState::Up;
			case 15:
				return KeyState::Right;
			case 16:
				return KeyState::Down;
			case 17:
				return KeyState::Left;
			case 18:
				return KeyState::Y;
			case 19:
				return KeyState::B;
			case 20:
				return KeyState::A;
			case 21:
				return KeyState::X;
			case 22:
				return KeyState::Window;
			case 23:
				return KeyState::Menu;
			default:
				return false;
			}
		}
		//按键检查
		static bool CheckKey(int Key, int ComboClick = 1, float Duration = 0.3) {
			//建立按键档案
			if (TempData::t_KeyDown.find(Key) == TempData::t_KeyDown.end()) {
				TempData::t_KeyDown[Key] = false;
			}
			//按键检查
			if (KeyIdHandle(Key) and !TempData::t_KeyDown[Key]) {
				TempData::t_KeyDown[Key] = true;
				//连击检查
				if (TempData::t_KeyCount.find(Key) != TempData::t_KeyCount.end()) {
					//计时器检查
					if (TempData::t_KeyCount[Key] == 1)
						Chronoscope::AddChronoscope(Duration, "XKEY_" + to_string(Key), true);
					if (Chronoscope::CheckChronoscope("XKEY_" + to_string(Key))) {
						TempData::t_KeyCount[Key] = 0;
					}
					TempData::t_KeyCount[Key]++;
				}
				else {
					Chronoscope::AddChronoscope(Duration, "XKEY_" + to_string(Key), true);
					TempData::t_KeyCount[Key] = 1;
				}

				//检查结果
				if (TempData::t_KeyCount[Key] == ComboClick)
					return true;
				else
					return false;
			}
			else
				TempData::t_KeyDown[Key] = false;
			return false;
		}
		static void Updata() {
			KeyState::LJoystickUp = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC44) > 0.0;
			KeyState::LJoystickRight = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC40) > 0.0;
			KeyState::LJoystickDown = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC44) < 0.0;
			KeyState::LJoystickLeft = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC40) < 0.0;
			KeyState::RJoystickUp = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC48) > 0.0;
			KeyState::RJoystickRight = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC4C) > 0.0;
			KeyState::RJoystickDown = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC48) < 0.0;
			KeyState::RJoystickLeft = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC4C) < 0.0;
			KeyState::LJoystickPress = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC64) != 0.0;
			KeyState::RJoystickPress = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC68) != 0.0;
			KeyState::LT = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC88) != 0.0;
			KeyState::RT = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC8C) != 0.0;
			KeyState::LB = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC80) != 0.0;
			KeyState::RB = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC84) != 0.0;
			KeyState::Up = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC70) != 0.0;
			KeyState::Right = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC74) != 0.0;
			KeyState::Down = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC78) != 0.0;
			KeyState::Left = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC7C) != 0.0;
			KeyState::Y = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC90) != 0.0;
			KeyState::B = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC94) != 0.0;
			KeyState::A = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC98) != 0.0;
			KeyState::X = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC9C) != 0.0;
			KeyState::Window = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC60) != 0.0;
			KeyState::Menu = *offsetPtr<float>(BasicGameData::XboxPadPlot, 0xC6C) != 0.0;
		}
	}
#pragma endregion

	//初始化
	static bool Init() {
		if (ModConfig::GameDataInit) 
			return true;
		else
		{
			BasicGameData::XboxPadPlot = *(undefined**)MH::GamePad::XboxPadPtr;
			void* PlayerPlot = *(undefined**)MH::Player::PlayerBasePlot;
			void* PlayerInfoPlot = *(undefined**)MH::Player::BasePtr;
			BasicGameData::PlayerPlot = *offsetPtr<undefined**>((undefined(*)())PlayerPlot, 0x50);
			void* PlayerDataOffset1 = *offsetPtr<undefined**>((undefined(*)())PlayerPlot, 0x50);
			void* PlayerDataHandlePlot = *(undefined**)MH::Player::PlayerDataHandlePlot;
			void* PlayerDataHandleOffset1 = nullptr;
			if (PlayerDataHandlePlot != nullptr)
				PlayerDataHandleOffset1 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandlePlot, 0x48);
			void* PlayerDataHandleOffset2 = nullptr;
			if (PlayerDataHandleOffset1 != nullptr)
				PlayerDataHandleOffset2 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset1, 0x58);
			void* PlayerDataHandleOffset3 = nullptr;
			if (PlayerDataHandleOffset2 != nullptr)
				PlayerDataHandleOffset3 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset2, 0x58);
			void* PlayerDataHandleOffset4 = nullptr;
			if (PlayerDataHandleOffset3 != nullptr)
				PlayerDataHandleOffset4 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset3, 0x40);
			void* PlayerDataHandleOffset5 = nullptr;
			if (PlayerDataHandleOffset4 != nullptr)
				PlayerDataHandleOffset5 = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset4, 0xD0);
			if (PlayerDataHandleOffset5 != nullptr)
				BasicGameData::PlayerDataPlot = *offsetPtr<undefined**>((undefined(*)())PlayerDataHandleOffset5, 0x8);
			BasicGameData::PlayerInfoPlot = *offsetPtr<undefined**>((undefined(*)())PlayerInfoPlot, 0xA8);
			BasicGameData::GameTimePlot = (undefined(*)())MH::World::GameClock;
			BasicGameData::MapPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x7D20);
			if (
				BasicGameData::PlayerPlot != nullptr and
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
					[](auto environmental, auto id, auto subId) {
						auto ret = original(environmental, id, subId);
						Base::World::EnvironmentalData::Environmentals[environmental] = Base::World::EnvironmentalData::EnvironmentalData(
							environmental, 0, 0, 0, id, subId
						);
						return ret;
					});
				//怪物地址获取
				HookLambda(MH::Monster::ctor,
					[](auto monster, auto id, auto subId) {
						auto ret = original(monster, id, subId);
						Base::Monster::Monsters[monster] = Base::Monster::MonsterData(
							monster, 0, 0, 0, id, subId
						);
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
						GetRBXPtr(&Base::PlayerData::Coordinate::TempData::t_visual);
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
				//武器装饰物修改
				HookLambda(MH::Weapon::WeaponOrnaments,
					[]() {
						GetRBXPtr(&Base::PlayerData::WeaponOrnaments::TempData::t_ornaments);
						if (Base::PlayerData::WeaponOrnaments::TempData::t_ornaments != nullptr) {
							Base::PlayerData::WeaponOrnaments::OrnamentsCoordinate.x = *offsetPtr<float>(Base::PlayerData::WeaponOrnaments::TempData::t_ornaments, 0x160);
							Base::PlayerData::WeaponOrnaments::OrnamentsCoordinate.y = *offsetPtr<float>(Base::PlayerData::WeaponOrnaments::TempData::t_ornaments, 0x164);
							Base::PlayerData::WeaponOrnaments::OrnamentsCoordinate.z = *offsetPtr<float>(Base::PlayerData::WeaponOrnaments::TempData::t_ornaments, 0x168);
							Base::PlayerData::WeaponOrnaments::OrnamentsSize.x = *offsetPtr<float>(Base::PlayerData::WeaponOrnaments::TempData::t_ornaments, 0x180);
							Base::PlayerData::WeaponOrnaments::OrnamentsSize.y = *offsetPtr<float>(Base::PlayerData::WeaponOrnaments::TempData::t_ornaments, 0x184);
							Base::PlayerData::WeaponOrnaments::OrnamentsSize.z = *offsetPtr<float>(Base::PlayerData::WeaponOrnaments::TempData::t_ornaments, 0x188);
							if (Base::PlayerData::WeaponOrnaments::TempData::t_setOrnamentsCoordinate) {
								*offsetPtr<float>(Base::PlayerData::WeaponOrnaments::TempData::t_ornaments, 0x160) = Base::PlayerData::WeaponOrnaments::TempData::t_SetOrnamentsCoordinate.x;
								*offsetPtr<float>(Base::PlayerData::WeaponOrnaments::TempData::t_ornaments, 0x164) = Base::PlayerData::WeaponOrnaments::TempData::t_SetOrnamentsCoordinate.y;
								*offsetPtr<float>(Base::PlayerData::WeaponOrnaments::TempData::t_ornaments, 0x168) = Base::PlayerData::WeaponOrnaments::TempData::t_SetOrnamentsCoordinate.z;
							}
							if (Base::PlayerData::WeaponOrnaments::TempData::t_setOrnamentsSize) {
								*offsetPtr<float>(Base::PlayerData::WeaponOrnaments::TempData::t_ornaments, 0x180) = Base::PlayerData::WeaponOrnaments::TempData::t_SetOrnamentsSize.x;
								*offsetPtr<float>(Base::PlayerData::WeaponOrnaments::TempData::t_ornaments, 0x184) = Base::PlayerData::WeaponOrnaments::TempData::t_SetOrnamentsSize.y;
								*offsetPtr<float>(Base::PlayerData::WeaponOrnaments::TempData::t_ornaments, 0x188) = Base::PlayerData::WeaponOrnaments::TempData::t_SetOrnamentsSize.z;
							}
						}
						return original();
					});
				//武器坐标修改
				HookLambda(MH::Weapon::MainWeaponPtr,
					[]() {
						GetRBXPtr(&Base::PlayerData::Weapons::TempData::t_mainWeapon);
						if (Base::PlayerData::Weapons::TempData::t_mainWeapon != nullptr) {
							Base::PlayerData::Weapons::MainWeaponCoordinate = Vector3(
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_mainWeapon, 0x160),
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_mainWeapon, 0x164),
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_mainWeapon, 0x168)
							);
							Base::PlayerData::Weapons::MainWeaponSize = Vector3(
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_mainWeapon, 0x180),
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_mainWeapon, 0x184),
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_mainWeapon, 0x188)
							);
							if (Base::PlayerData::Weapons::TempData::t_setMainWeaponCoordinate) {
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_mainWeapon, 0x160) = Base::PlayerData::Weapons::TempData::t_SetMainWeaponCoordinate.x;
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_mainWeapon, 0x164) = Base::PlayerData::Weapons::TempData::t_SetMainWeaponCoordinate.y;
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_mainWeapon, 0x168) = Base::PlayerData::Weapons::TempData::t_SetMainWeaponCoordinate.z;
							}
							if (Base::PlayerData::Weapons::TempData::t_setMainWeaponSize) {
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_mainWeapon, 0x160) = Base::PlayerData::Weapons::TempData::t_SetMainWeaponSize.x;
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_mainWeapon, 0x164) = Base::PlayerData::Weapons::TempData::t_SetMainWeaponSize.y;
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_mainWeapon, 0x168) = Base::PlayerData::Weapons::TempData::t_SetMainWeaponSize.z;
							}
						}
						return original();
					});
				HookLambda(MH::Weapon::SecondaryWeaponPtr,
					[]() {
						GetRBXPtr(&Base::PlayerData::Weapons::TempData::t_secondaryWeapon);
						if (Base::PlayerData::Weapons::TempData::t_secondaryWeapon != nullptr) {
							Base::PlayerData::Weapons::SecondaryWeaponCoordinate = Vector3(
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_secondaryWeapon, 0x160),
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_secondaryWeapon, 0x164),
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_secondaryWeapon, 0x168)
							);
							Base::PlayerData::Weapons::SecondaryWeaponSize = Vector3(
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_secondaryWeapon, 0x180),
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_secondaryWeapon, 0x184),
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_secondaryWeapon, 0x188)
							);
							if (Base::PlayerData::Weapons::TempData::t_setSecondaryWeaponCoordinate) {
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_secondaryWeapon, 0x160) = Base::PlayerData::Weapons::TempData::t_SetSecondaryWeaponCoordinate.x;
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_secondaryWeapon, 0x164) = Base::PlayerData::Weapons::TempData::t_SetSecondaryWeaponCoordinate.y;
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_secondaryWeapon, 0x168) = Base::PlayerData::Weapons::TempData::t_SetSecondaryWeaponCoordinate.z;
							}
							if (Base::PlayerData::Weapons::TempData::t_setSecondaryWeaponSize) {
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_secondaryWeapon, 0x160) = Base::PlayerData::Weapons::TempData::t_SetSecondaryWeaponSize.x;
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_secondaryWeapon, 0x164) = Base::PlayerData::Weapons::TempData::t_SetSecondaryWeaponSize.y;
								*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_secondaryWeapon, 0x168) = Base::PlayerData::Weapons::TempData::t_SetSecondaryWeaponSize.z;
							}
						}
						return original();
					});
				//获取命中信息
				HookLambda(MH::Weapon::Hit,
					[]() {
						GetHitPtr(&Base::PlayerData::Weapons::TempData::t_weaponHit);
						Base::PlayerData::Weapons::HitCoordinate = Vector3(
							*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_weaponHit, 0x60),
							*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_weaponHit, 0x64),
							*offsetPtr<float>(Base::PlayerData::Weapons::TempData::t_weaponHit, 0x68)
						);
						return original();
					});
				//修改钩爪坐标
				HookLambda(MH::Player::HookCoordinateChange,
					[](auto ptr) {
						if (Base::PlayerData::HookChange) {
							*offsetPtr<float>(ptr, 0x60) = Base::PlayerData::HookCoordinateChange.x;
							*offsetPtr<float>(ptr, 0x64) = Base::PlayerData::HookCoordinateChange.y;
							*offsetPtr<float>(ptr, 0x68) = Base::PlayerData::HookCoordinateChange.z;
						}
						return original(ptr);
					});
				HookLambda(MH::Player::HookCoordinateChange2,
					[](auto RCX, auto RDX,auto ptr) {
						if (Base::PlayerData::HookChange) {
							*offsetPtr<float>(ptr, 0x0) = Base::PlayerData::HookCoordinateChange.x;
							*offsetPtr<float>(ptr, 0x4) = Base::PlayerData::HookCoordinateChange.y;
							*offsetPtr<float>(ptr, 0x8) = Base::PlayerData::HookCoordinateChange.z;
						}
						return original(RCX,RDX,ptr);
					});
				HookLambda(MH::Player::HookCoordinateChange3,
					[]() {
						GetRDIPtr(&Base::PlayerData::TempData::t_HookCoordinate);
						if (Base::PlayerData::HookChange) {
							*offsetPtr<float>(Base::PlayerData::TempData::t_HookCoordinate, 0x0) = Base::PlayerData::HookCoordinateChange.x;
							*offsetPtr<float>(Base::PlayerData::TempData::t_HookCoordinate, 0x4) = Base::PlayerData::HookCoordinateChange.y;
							*offsetPtr<float>(Base::PlayerData::TempData::t_HookCoordinate, 0x8) = Base::PlayerData::HookCoordinateChange.z;
						}
						return original();
					});
				HookLambda(MH::Player::HookCoordinateChange4,
					[]() {
						GetRBXPtr(&Base::PlayerData::TempData::t_HookCoordinate2);
						if (Base::PlayerData::HookChange) {
							*offsetPtr<float>(Base::PlayerData::TempData::t_HookCoordinate2, 0x130) = Base::PlayerData::HookCoordinateChange.x;
							*offsetPtr<float>(Base::PlayerData::TempData::t_HookCoordinate2, 0x134) = Base::PlayerData::HookCoordinateChange.y;
							*offsetPtr<float>(Base::PlayerData::TempData::t_HookCoordinate2, 0x138) = Base::PlayerData::HookCoordinateChange.z;
						}
						return original();
					});
				
				MH_ApplyQueued();
				ModConfig::GameDataInit = true;
				LOG(INFO) << ModConfig::ModName << " : Game data initialization complete!";
				LOG(INFO) << " |  Mod：" << ModConfig::ModName;
				LOG(INFO) << " |  Author：" << ModConfig::ModAuthor;
				LOG(INFO) << " |  Version：" << ModConfig::ModVersion;
				//Draw::GameInit = true;
				return true;
			}
			else {
				if (ModConfig::InitErrInfo) {
					LOG(ERR) << ModConfig::ModName << " : Game data initialization failed!";
					LOG(ERR) << "The following address failed to complete the initialization. We will try again later. If the address is still not initialized successfully, please contact the mod author for solution.";
					if (BasicGameData::PlayerPlot == nullptr)
						LOG(ERR) << " |  PlayerPlot";
					if (BasicGameData::PlayerDataPlot == nullptr)
						LOG(ERR) << " |  PlayerDataPlot";
					if (BasicGameData::MapPlot == nullptr)
						LOG(ERR) << " |  MapPlot";
					if (BasicGameData::GameTimePlot == nullptr)
						LOG(ERR) << " |  GameTimePlot";
					if (BasicGameData::XboxPadPlot == nullptr)
						LOG(ERR) << " |  XboxPadPlot";
					ModConfig::InitErrCount++;
					if (ModConfig::InitErrCount > 10)
						ModConfig::InitErrInfo = false;
				}
				return false;
			}
		}
	}
	//实时更新的数据
	static void RealTimeUpdate() {
		if (ModConfig::GameDataInit) {
			//实时更新地图地址信息
			BasicGameData::MapPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x7D20);
			//写入地图信息和清除数据
			if (Chronoscope::NowTime > *offsetPtr<float>(BasicGameData::MapPlot, 0xC24)) {
				World::MapId = *offsetPtr<int>(BasicGameData::MapPlot, 0xB88);
				//清除计时器数据
				Chronoscope::ChronoscopeList.clear();
				//清除环境生物数据
				World::EnvironmentalData::Environmentals.clear();
				//清除相机数据
				PlayerData::Coordinate::TempData::t_SetVisualBind = nullptr;
				PlayerData::Coordinate::TempData::t_SetVisual = false;
				//清理委托
				Commission::CleanCommission();
				//清理怪物筛选器
				Monster::Filter = pair<int, int>(255, 255);
				//清理玩家击中的怪物地址
				PlayerData::AttackMonsterPlot = nullptr;
				//清理玩家Fsm
				PlayerData::Fsm = PlayerData::FsmData(0, 0);
				PlayerData::NowFsm = PlayerData::FsmData(0, 0);
				PlayerData::TempData::t_ManualFsmAction = PlayerData::FsmData(0, 0);
				PlayerData::TempData::t_executingFsmAction = false;
				//更新地址信息
				void* PlayerPlot = *(undefined**)MH::Player::PlayerBasePlot;
				BasicGameData::PlayerPlot = *offsetPtr<undefined**>((undefined(*)())PlayerPlot, 0x50);
				//清除按键数据
				Keyboard::TempData::t_KeyCount.clear();
				Keyboard::TempData::t_KeyDown.clear();
				//清除Xbox手柄数据
				XboxPad::TempData::t_KeyCount.clear();
				XboxPad::TempData::t_KeyDown.clear();
			}
			//更新玩家数据
			PlayerData::Updata();
			//清除死亡的环境生物,此处最好能找到环境生物吊销的地址，目前先这样用着
			for (auto [Environmental, EData] : World::EnvironmentalData::Environmentals) {
				if (EData.Plot == nullptr) {
					World::EnvironmentalData::Environmentals.erase(Environmental);
				}
			}
			//更新环境生物数据
			for (auto [environmental, environmentalData] : Base::World::EnvironmentalData::Environmentals) {
				if (environmental != nullptr) {
					Base::World::EnvironmentalData::Environmentals[environmental].CoordinatesX = *offsetPtr<float>(environmental, 0x160);
					Base::World::EnvironmentalData::Environmentals[environmental].CoordinatesY = *offsetPtr<float>(environmental, 0x164);
					Base::World::EnvironmentalData::Environmentals[environmental].CoordinatesZ = *offsetPtr<float>(environmental, 0x168);
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
			//更新Xbox手柄信息
			XboxPad::Updata();
		}
	}
}