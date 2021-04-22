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
	//���ýṹ
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
			bool hotReload;//hotReloadģʽ��lua��ֱ�Ӷ�ȡ�ļ�����ͨ�����������ִ�д���
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
		//���ò���
		bool GameDataInit = false;
		bool InitErrInfo = true;
		int InitErrCount = 0;
		vector<string> LuaFiles;
		vector<string> LuaError;
		bool ModConsole = false;
		bool HotKeyEdit = false;
		//�����ò���
		string ModName = "LuaScript";
		string ModAuthor = "Alcedo";
		string ModVersion = "v1.1.9";
		long long ModBuild = 119004141229;
		string Version = "421470";
	}
#pragma endregion
	//��Ϸ������ַ
#pragma region BasicGameData
	//��Ϸ��ַ����
	namespace BasicGameData {
		void* PlayerPlot = nullptr;
		void* PlayerInfoPlot = nullptr;
		void* PlayerDataPlot = nullptr;
		void* MapPlot = nullptr;
		void* GameTimePlot = nullptr;
		void* XboxPadPlot = nullptr;
	}
#pragma endregion
	//������Ϣ
#pragma region World
	namespace World {
		//��������
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
			//���������б�
			map<void*, EnvironmentalData> Environmentals;
			//����ɸѡ��
			pair<int, int> Filter(255, 255);
		}
		int MapId = 0;
	}
#pragma endregion
	//��ʱ��
#pragma region Chronoscope
	namespace Chronoscope {
		struct ChronoscopeData {
			float StartTime = 0;
			float EndTime = 0;
		};

		//���ڵ�ʱ��
		float NowTime = 0;
		//��ʱ���б�
		map<string, ChronoscopeData> ChronoscopeList;
		//��Ӽ�ʱ��(ʱ������ʱ�����ƣ��Ƿ񸲸�)
		static bool AddChronoscope(float duration, string name, bool Overlay = false) {
			if (ChronoscopeList.find(name) == ChronoscopeList.end() || Overlay) {
				ChronoscopeList[name].EndTime = NowTime + duration;
				ChronoscopeList[name].StartTime = NowTime;
				return true;
			}
			else
				return false;
		}
		//ɾ����ʱ��
		static void DelChronoscope(string name) {
			if (ChronoscopeList.find(name) != ChronoscopeList.end()) {
				ChronoscopeList.erase(name);
			}
		}
		//����ʱ���Ƿ����
		static bool CheckPresenceChronoscope(string name) {
			if (ChronoscopeList.find(name) != ChronoscopeList.end()) {
				return true;
			}
			return false;
		}
		//����ʱ���Ƿ����
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
	//����
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
	//ͼ�λ���
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
	//ί��
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
						//�ƶ���Ŀ��
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
						//�ƶ�����
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
	//������Ϣ
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
		//�����б�
		map<void*, MonsterData> Monsters;
		//����ɸѡ��
		pair<int, int> Filter(255,255);
		//����������buff
		static void SetBuff(void* monster,string buff){
			MonsterBuff::MonsterBuffState monsterBuff = MonsterBuff::GetMonsterBuffState(monster,buff);
			if (monsterBuff.MaxStateValue != 0) {
				MonsterBuff::SetMonsterBuffState(monster, buff);
			}
		}
		//��ȡ����buff״̬
		static MonsterBuff::MonsterBuffState GetBuff(void* monster, string buff) {
			return MonsterBuff::GetMonsterBuffState(monster, buff);
		}
		//��ȡ����buff״̬
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
		//���ù�����������
		static void BehaviorControl(void* monster, int Fsm) {
			//��л�Ϸ��ʴ����ṩ�ĵ�ַ
			MH::Monster::BehaviorControl((undefined*)monster, Fsm);
		}
	}
#pragma endregion
	//�����Ϣ
#pragma region PlayerData
	namespace PlayerData {
		struct FsmData {
			//���� 0Ϊ����3Ϊ����
			int Target = 0;
			//ִ��Id
			int Id = 0;
			FsmData(int Target = 0, int Id = 0) :Target(Target), Id(Id) {
			};
		};

		//��������
		namespace TempData {
			FsmData t_ManualFsmAction;
			bool t_executingFsmAction = false;
			void* t_HookCoordinate = nullptr;
			void* t_HookCoordinate2 = nullptr;
		}

		//����
		namespace Coordinate {
			//��������
			namespace TempData {
				void* t_visual = nullptr;
				Vector3 t_SetVisualCoordinate;
				void* t_SetVisualBind = nullptr;
				bool t_SetVisual = false;
			}

			//�������
			Vector3 Entity = Vector3();
			//׼������
			Vector3 Collimator = Vector3();
			//������׼������
			Vector3 Parabola = Vector3();
			//��ײ��������
			Vector3 Collision = Vector3();
			//��������
			Vector3 Increment = Vector3();
			//��������
			Vector3 Navigation = Vector3();
			//�������
			Vector3 Visual = Vector3();
			//��������
			Vector3 Weapon = Vector3();
			//��צ����
			Vector3 Hook = Vector3();
			//��Ҵ���(X����,Y����,Z����,�Ƿ�ǽ)
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
		//����װ����
		namespace WeaponOrnaments {
			//��������
			namespace TempData {
				void* t_ornaments = nullptr;
				bool t_setOrnamentsCoordinate = false;
				Vector3 t_SetOrnamentsCoordinate;
				bool t_setOrnamentsSize = false;
				Vector3 t_SetOrnamentsSize;
			}
			//װ��������
			Vector3 OrnamentsCoordinate = Vector3();
			//װ����ģ�ʹ�С
			Vector3 OrnamentsSize = Vector3();

			//���װ�����������
			static void DecontrolOrnamentsCoordinate() {
				TempData::t_setOrnamentsCoordinate = false;
			}
			//���װ�����С����
			static void DecontrolOrnamentsSize() {
				TempData::t_setOrnamentsSize = false;
			}
			//װ������������(X����,Y����,Z����)
			static void SetOrnamentsCoordinate(float X, float Y, float Z) {
				TempData::t_SetOrnamentsCoordinate = Vector3(X,Y,Z);
				TempData::t_setOrnamentsCoordinate = true;
			}
			//װ�����С����(X����,Y����,Z����)
			static void SetOrnamentsSize(float X, float Y, float Z) {
				TempData::t_SetOrnamentsSize = Vector3(X, Y, Z);
				TempData::t_setOrnamentsSize = true;
			}
		}
		//����
		namespace Weapons {
			//��������
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
			//��������
			int WeaponType = 0;
			//����ID
			int WeaponId = 0;
			//����������
			Vector3 MainWeaponCoordinate = Vector3();
			//������ģ�ʹ�С
			Vector3 MainWeaponSize = Vector3();
			//����������
			Vector3 SecondaryWeaponCoordinate = Vector3();
			//������ģ�ʹ�С
			Vector3 SecondaryWeaponSize = Vector3();
			//������������
			Vector3 HitCoordinate = Vector3();
			//�����������������ͣ�����ID��
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
			//����������������
			static void DecontrolMainWeaponCoordinate() {
				TempData::t_setMainWeaponCoordinate = false;
			}
			//�����������С����
			static void DecontrolMainWeaponSize() {
				TempData::t_setMainWeaponSize = false;
			}
			//��������������(X����,Y����,Z����)
			static void SetMainWeaponCoordinate(float X, float Y, float Z) {
				TempData::t_SetMainWeaponCoordinate = Vector3(X, Y, Z);
				TempData::t_setMainWeaponCoordinate = true;
			}
			//��������С����(X����,Y����,Z����)
			static void SetMainWeaponSize(float X, float Y, float Z) {
				TempData::t_SetMainWeaponSize = Vector3(X, Y, Z);
				TempData::t_setMainWeaponSize = true;
			}

			//����������������
			static void DecontrolSecondaryWeaponCoordinate() {
				TempData::t_setSecondaryWeaponCoordinate = false;
			}
			//�����������С����
			static void DecontrolSecondaryWeaponSize() {
				TempData::t_setSecondaryWeaponSize = false;
			}
			//��������������(X����,Y����,Z����)
			static void SetSecondaryWeaponCoordinate(float X, float Y, float Z) {
				TempData::t_SetSecondaryWeaponCoordinate = Vector3(X, Y, Z);
				TempData::t_setSecondaryWeaponCoordinate = true;
			}
			//��������С����(X����,Y����,Z����)
			static void SetSecondaryWeaponSize(float X, float Y, float Z) {
				TempData::t_SetSecondaryWeaponSize = Vector3(X, Y, Z);
				TempData::t_setSecondaryWeaponSize = true;
			}
		}
		//��Ч
		namespace Effects {
			//������Ч(��Ч�飬��Чid)
			static void GenerateSpecialEffects(int group, int record) {
				//��л�Ϸ��ʴ����ṩ�ĵ�ַ
				void* Effects = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x8808);
				//��Ч���
				MH::Player::Effects((undefined*)Effects, group, record);
			}
		}
		//�����
		static void SetVisual(void* bind, float Duration = 0) {
			Coordinate::TempData::t_SetVisualBind = bind;
			Coordinate::TempData::t_SetVisual = true;
		}
		//����������
		static void UnbindVisual() {
			Coordinate::TempData::t_SetVisual = false;
			Coordinate::TempData::t_SetVisualBind = nullptr;
		}
		//�������(X����,Y����,Z����,����ʱ��0=����)
		static void SetVisual(float X, float Y, float Z, float Duration = 0) {
			Coordinate::TempData::t_SetVisualCoordinate.x = X;
			Coordinate::TempData::t_SetVisualCoordinate.y = Y;
			Coordinate::TempData::t_SetVisualCoordinate.z = Z;
			Coordinate::TempData::t_SetVisual = true;
		}
		//����Ƕ�
		float Angle = 0;
		//���򻡶�
		float Radian = 0;
		//ŷ����
		Vector3 EulerAngle = Vector3();
		//�������
		float VisualDistance = 0;
		//�Ƿ�����׼״̬
		bool AimingState = false;
		//���һ�λ��еĹ����ַ
		void* AttackMonsterPlot = nullptr;
		//����id
		int ActionId = 0;
		//������Ϣ
		FsmData Fsm = FsmData();
		FsmData NowFsm = FsmData();
		//�������
		string Name = "";
		//hr�ȼ�
		int Hr = 0;
		//mr�ȼ�
		int Mr = 0;
		//��ǰѪ��
		float CurrentHealth = 0;
		//����Ѫ����0-150��
		float BasicHealth = 0;
		//Ѫ������
		float MaxHealth = 0;
		//��ǰ����
		float CurrentEndurance = 0;
		//�������ޣ�25-150��
		float MaxEndurance = 0;
		//ִ����������(ִ�ж���,ִ��Id)
		static void RunDerivedAction(int type, int id) {
			TempData::t_ManualFsmAction = FsmData(type, id);
			TempData::t_executingFsmAction = true;
			*offsetPtr<int>(BasicGameData::PlayerPlot, 0x6284) = type;
			*offsetPtr<int>(BasicGameData::PlayerPlot, 0x6288) = id;
			*offsetPtr<int>(BasicGameData::PlayerPlot, 0x628C) = type;
			*offsetPtr<int>(BasicGameData::PlayerPlot, 0x6290) = id;
			Fsm = FsmData(type, id);
		}
		//���ִ�����������Ƿ����
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
		//��ȡ���Buff����ʱ��
		static float GetPlayerBuff(string buff) {
			void* BuffsPlot = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x7D20);
			int buffPtr = PlayerBuff::GetBuffPtr(buff);
			return *offsetPtr<float>(BuffsPlot, buffPtr);
		}
		//�������Buff����ʱ��
		static void SetPlayerBuff(string buff, float duration) {
			void* BuffsPlot = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x7D20);
			int buffPtr = PlayerBuff::GetBuffPtr(buff);
			*offsetPtr<float>(BuffsPlot, buffPtr) = duration;
		}
		//��צ�������
		Vector3 HookCoordinateChange = Vector3();
		//��צ�������
		bool HookChange = false;
		//������ݸ���
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
	//������Ϣ
#pragma region Keyboard
	namespace Keyboard {
		namespace TempData {
			map<int, bool> t_KeyDown;
			map<int, int> t_KeyCount;
		}
		//��鴰��
		static bool CheckWindows() {
			string GameName = "MONSTER HUNTER: WORLD(" + ModConfig::Version + ")";
			HWND wnd = GetForegroundWindow();;
			HWND mhd = FindWindow("MT FRAMEWORK", GameName.c_str());
			if (wnd == mhd)
				return true;
			else
				return false;
		}
		//�������
		static bool CheckKey(int vk, int ComboClick = 1,float Duration = 0.3) {
			if (!CheckWindows())
				return false;
			//������������
			if (TempData::t_KeyDown.find(vk) == TempData::t_KeyDown.end()) {
				TempData::t_KeyDown[vk] = false;
			}
			//�������
			if (GetKeyState(vk) < 0 and !TempData::t_KeyDown[vk]) {
				TempData::t_KeyDown[vk] = true;
				//�������
				if (TempData::t_KeyCount.find(vk) != TempData::t_KeyCount.end()) {
					//��ʱ�����
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

				//�����
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
	//Ͷ����
#pragma region ProjectilesOperation
	namespace ProjectilesOperation {
		//ִ��Ͷ��������
		static bool CallProjectilesGenerate(int Id, float* Coordinate, int From = 0) {
			//����������Ͷ����
			void* Weapon = *offsetPtr<void*>(BasicGameData::PlayerPlot, 0x76B0);
			void* WeaponShlpPlot= *offsetPtr<void*>(Weapon, 0x1D90);
			//���󷢳���Ͷ����
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
		//����Ͷ����·������
		static void GenerateProjectilesCoordinateData(float*& CalculationCoordinates,Vector3 startPoint, Vector3 endPoint) {
			//����ָ��
			float* temp_float = CalculationCoordinates;
			//д����ʼ����
			*temp_float = startPoint.x;
			temp_float++;
			*temp_float = startPoint.y;
			temp_float++;
			*temp_float = startPoint.z;
			temp_float++;
			//��ʼ����д����ɣ���4���ֽ�
			*temp_float = 0;
			temp_float++;
			//����ָ��Ϊ���ֽڲ�д��1
			unsigned char* temp_byte = (unsigned char*)temp_float;
			*temp_byte = 1;

			//���軺��ָ���������ַ40��
			temp_float = offsetPtr<float>(CalculationCoordinates, 0x40);
			//д���������
			*temp_float = endPoint.x;
			temp_float++;
			*temp_float = endPoint.y;
			temp_float++;
			*temp_float = endPoint.z;
			temp_float++;
			//��������д����ɣ���4���ֽ�
			*temp_float = 0;
			temp_float++;
			//����ָ��Ϊ���ֽڲ�д��1
			temp_byte = (unsigned char*)temp_float;
			*temp_byte = 1;

			//���軺��ָ���������ַA0��
			int* tempCoordinateTailData = offsetPtr<int>(CalculationCoordinates, 0xA0);
			//д����������β����Ϣ
			*tempCoordinateTailData = 0x12;
			tempCoordinateTailData++;
			longlong* tempCoordinateTailData_longlong = (longlong*)tempCoordinateTailData;
			*tempCoordinateTailData_longlong = -1;
		}
		//����Ͷ����
		static bool CreateProjectiles(int Id, Vector3 startPoint, Vector3 endPoint, int From = 0) {
			//����Ͷ����·�����ݻ���ָ��
			float* CoordinatesData = new float[73];
			//��仺��������
			memset(CoordinatesData, 0, 73 * 4);
			//����Ͷ����·������
			GenerateProjectilesCoordinateData(CoordinatesData, startPoint, endPoint);
			//ִ������Ͷ����
			bool GenerateResults = CallProjectilesGenerate(Id, CoordinatesData, From);
			//��������
			delete[]CoordinatesData;
			return GenerateResults;
		}
	}
#pragma endregion
	//Xbox�ֱ���Ϣ
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
		//�������
		static bool CheckKey(int Key, int ComboClick = 1, float Duration = 0.3) {
			//������������
			if (TempData::t_KeyDown.find(Key) == TempData::t_KeyDown.end()) {
				TempData::t_KeyDown[Key] = false;
			}
			//�������
			if (KeyIdHandle(Key) and !TempData::t_KeyDown[Key]) {
				TempData::t_KeyDown[Key] = true;
				//�������
				if (TempData::t_KeyCount.find(Key) != TempData::t_KeyCount.end()) {
					//��ʱ�����
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

				//�����
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

	//��ʼ��
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
				//��������
				MH_Initialize();
				//�������ݻ�ȡ
				HookLambda(MH::World::WaypointZLocal,
					[](auto x1, auto x2) {
						Navigation(
							&Base::PlayerData::Coordinate::Navigation.x,
							&Base::PlayerData::Coordinate::Navigation.y,
							&Base::PlayerData::Coordinate::Navigation.z
						);
						return original(x1, x2);
					});
				//���������ַ��ȡ
				HookLambda(MH::EnvironmentalBiological::ctor,
					[](auto environmental, auto id, auto subId) {
						auto ret = original(environmental, id, subId);
						Base::World::EnvironmentalData::Environmentals[environmental] = Base::World::EnvironmentalData::EnvironmentalData(
							environmental, 0, 0, 0, id, subId
						);
						return ret;
					});
				//�����ַ��ȡ
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
				//�ӽ���������޸�
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
				//����װ�����޸�
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
				//���������޸�
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
				//��ȡ������Ϣ
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
				//�޸Ĺ�צ����
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
				LOG(INFO) << " |  Mod��" << ModConfig::ModName;
				LOG(INFO) << " |  Author��" << ModConfig::ModAuthor;
				LOG(INFO) << " |  Version��" << ModConfig::ModVersion;
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
	//ʵʱ���µ�����
	static void RealTimeUpdate() {
		if (ModConfig::GameDataInit) {
			//ʵʱ���µ�ͼ��ַ��Ϣ
			BasicGameData::MapPlot = *offsetPtr<undefined**>((undefined(*)())BasicGameData::PlayerPlot, 0x7D20);
			//д���ͼ��Ϣ���������
			if (Chronoscope::NowTime > *offsetPtr<float>(BasicGameData::MapPlot, 0xC24)) {
				World::MapId = *offsetPtr<int>(BasicGameData::MapPlot, 0xB88);
				//�����ʱ������
				Chronoscope::ChronoscopeList.clear();
				//���������������
				World::EnvironmentalData::Environmentals.clear();
				//����������
				PlayerData::Coordinate::TempData::t_SetVisualBind = nullptr;
				PlayerData::Coordinate::TempData::t_SetVisual = false;
				//����ί��
				Commission::CleanCommission();
				//�������ɸѡ��
				Monster::Filter = pair<int, int>(255, 255);
				//������һ��еĹ����ַ
				PlayerData::AttackMonsterPlot = nullptr;
				//�������Fsm
				PlayerData::Fsm = PlayerData::FsmData(0, 0);
				PlayerData::NowFsm = PlayerData::FsmData(0, 0);
				PlayerData::TempData::t_ManualFsmAction = PlayerData::FsmData(0, 0);
				PlayerData::TempData::t_executingFsmAction = false;
				//���µ�ַ��Ϣ
				void* PlayerPlot = *(undefined**)MH::Player::PlayerBasePlot;
				BasicGameData::PlayerPlot = *offsetPtr<undefined**>((undefined(*)())PlayerPlot, 0x50);
				//�����������
				Keyboard::TempData::t_KeyCount.clear();
				Keyboard::TempData::t_KeyDown.clear();
				//���Xbox�ֱ�����
				XboxPad::TempData::t_KeyCount.clear();
				XboxPad::TempData::t_KeyDown.clear();
			}
			//�����������
			PlayerData::Updata();
			//��������Ļ�������,�˴�������ҵ�������������ĵ�ַ��Ŀǰ����������
			for (auto [Environmental, EData] : World::EnvironmentalData::Environmentals) {
				if (EData.Plot == nullptr) {
					World::EnvironmentalData::Environmentals.erase(Environmental);
				}
			}
			//���»�����������
			for (auto [environmental, environmentalData] : Base::World::EnvironmentalData::Environmentals) {
				if (environmental != nullptr) {
					Base::World::EnvironmentalData::Environmentals[environmental].CoordinatesX = *offsetPtr<float>(environmental, 0x160);
					Base::World::EnvironmentalData::Environmentals[environmental].CoordinatesY = *offsetPtr<float>(environmental, 0x164);
					Base::World::EnvironmentalData::Environmentals[environmental].CoordinatesZ = *offsetPtr<float>(environmental, 0x168);
				}
			}
			//���¹�����Ϣ
			for (auto [monster, monsterData] : Base::Monster::Monsters) {
				if (monster != nullptr) {
					Base::Monster::Monsters[monster].CoordinatesX = *offsetPtr<float>(monster, 0x160);
					Base::Monster::Monsters[monster].CoordinatesY = *offsetPtr<float>(monster, 0x164);
					Base::Monster::Monsters[monster].CoordinatesZ = *offsetPtr<float>(monster, 0x168);
				}
			}

			//���¼�ʱ��ʱ��
			Chronoscope::NowTime = *offsetPtr<float>(BasicGameData::MapPlot, 0xC24);

			//������������
			if (!PlayerData::Coordinate::TempData::t_SetVisual) {
				PlayerData::Coordinate::TempData::t_SetVisualBind = nullptr;
			}
			//�������������
			if (PlayerData::Coordinate::TempData::t_SetVisualBind != nullptr) {
				PlayerData::Coordinate::TempData::t_SetVisualCoordinate.x = *offsetPtr<float>(PlayerData::Coordinate::TempData::t_SetVisualBind, 0x160);
				PlayerData::Coordinate::TempData::t_SetVisualCoordinate.y = *offsetPtr<float>(PlayerData::Coordinate::TempData::t_SetVisualBind, 0x164);
				PlayerData::Coordinate::TempData::t_SetVisualCoordinate.z = *offsetPtr<float>(PlayerData::Coordinate::TempData::t_SetVisualBind, 0x168);
			}
			//����ί��
			Commission::Run();
			//����Xbox�ֱ���Ϣ
			XboxPad::Updata();
		}
	}
}