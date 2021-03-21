#pragma once
#include <io.h>

using namespace std;
using namespace loader;

namespace Component {
	struct Effect {
		bool Enable = false;
		int group = 0;
		int record = 0;
	};
	
	/*
		��Ŀ���ƶ��������
		��������ҡ����������������ɼ������ʵ��
		ע��
			�ٶ�ֵԽ���ٶ�Խ��
			��Һ͹����Ƽ�ʹ��MovePlayerToPoint��MoveMonsterToPoint���в���
	*/
#pragma region MoveTargetToPoint
	static void MoveTargetToPoint(void* Target, Base::Vector3 Point,bool Instant = true,float speed = 100.0) {
		if (Target == nullptr)
			return;
		if (Instant) {
			*offsetPtr<float>(Target, 0x160) = Point.x;
			*offsetPtr<float>(Target, 0x164) = Point.y;
			*offsetPtr<float>(Target, 0x168) = Point.z;
		}
		else {
			Base::Commission::MoveEntity::CommissionList[Target] = Base::Commission::MoveEntity::Parameter{
				Base::Vector3{ Point.x, Point.y, Point.z },
				nullptr,
				speed 
			};
		}
	}
#pragma endregion
	/*
		��Ŀ���ƶ���Ŀ��
		��������ҡ����������������ɼ������ʵ��
		ע��
			�ٶ�ֵԽ���ٶ�Խ��
			��Һ͹����Ƽ�ʹ��MovePlayerToTarget��MoveMonsterToTarget���в���
	*/
#pragma region MoveTargetToTarget
	static void MoveTargetToTarget(void* Target, void* ToTarget, bool Instant = true, float speed = 100.0) {
		if (Target == nullptr || ToTarget == nullptr)
			return;
		float TargetPointX = *offsetPtr<float>(Target, 0x160);
		float TargetPointY = *offsetPtr<float>(Target, 0x164);
		float TargetPointZ = *offsetPtr<float>(Target, 0x168);
		if (Instant) {
			*offsetPtr<float>(Target, 0x160) = TargetPointX;
			*offsetPtr<float>(Target, 0x164) = TargetPointY;
			*offsetPtr<float>(Target, 0x168) = TargetPointZ;
		}
		else {
			Base::Commission::MoveEntity::CommissionList[Target] = Base::Commission::MoveEntity::Parameter{
				Base::Vector3{ TargetPointX, TargetPointY, TargetPointZ },
				ToTarget,
				speed
			};
		}
	}
#pragma endregion
	/*
		������ƶ���Ŀ��
		ע��
			�ٶ�ֵԽ���ٶ�Խ��
	*/
#pragma region MovePlayerToPoint
	static void MovePlayerToPoint(Base::Vector3 Point, Effect effect = Effect{false}, bool Instant = true, float speed = 100.0) {
		if (effect.Enable) {
			Base::PlayerData::Effects::GenerateSpecialEffects(effect.group, effect.record);
		}

		if (Instant) {
			Base::PlayerData::Coordinate::TransportCoordinate(Point.x,Point.y,Point.z,true);
		}
		else {
			MoveTargetToPoint(Base::BasicGameData::PlayerPlot, Point, false, speed);
		}
	}
#pragma endregion
	/*
		����Ϸ�ڷ�����Ϣ
	*/
#pragma region ShowMessage
	static void ShowMessage(std::string message) {
		MH::Chat::ShowGameMessage(*(undefined**)MH::Chat::MainPtr, (undefined*)&message[0], -1, -1, 0);
	}
#pragma endregion
	/*
		���ù���ɸѡ��
	*/
#pragma region SetMonsterFilter
	static void SetMonsterFilter(int monsterId, int monsterSubId) {
		Base::Monster::Filter = pair<int, int>(monsterId, monsterSubId);
	}
#pragma endregion
	/*
		�������ɸѡ��
	*/
#pragma region DisableMonsterFilter
	static void DisableMonsterFilter() {
		Base::Monster::Filter = pair<int, int>(255, 255);
	}
#pragma endregion
	/*
		��ȡ�����Ĺ���
	*/
#pragma region GetNavigationMonster
	static void* GetNavigationMonster() {
		for (auto [monster, monsterData] : Base::Monster::Monsters) {
			if (monster != nullptr) {
				Base::Vector3 monsterCoordinates(
					*offsetPtr<float>(monster, 0x160),
					*offsetPtr<float>(monster, 0x164),
					*offsetPtr<float>(monster, 0x168)
				);
				float distance = Base::Calculation::DistanceBetweenTwoCoordinates(Base::PlayerData::Coordinate::Navigation, monsterCoordinates);
				if (distance < 5) {
					return monster;
				}
			}
		}
		return nullptr;
	}
#pragma endregion
	/*
		��ȡ��������Ĺ���
	*/
#pragma region GetNearestMonster
	static void* GetNearestMonster(float MinRange = 0, float MaxRange = 9999999.0) {
		pair<void*, float> tempMonster (nullptr,0);
		for (auto [monster, monsterData] : Base::Monster::Monsters) {
			if (monster != nullptr) {
				if (
					monsterData.Id != Base::Monster::Filter.first and
					monsterData.SubId != Base::Monster::Filter.second and
					Base::Monster::Filter.first != 255 and
					Base::Monster::Filter.second != 255
					)
					continue;
				Base::Vector3 monsterCoordinates(
					*offsetPtr<float>(monster, 0x160),
					*offsetPtr<float>(monster, 0x164),
					*offsetPtr<float>(monster, 0x168)
				);
				float distance = Base::Calculation::DistanceBetweenTwoCoordinates(Base::PlayerData::Coordinate::Entity, monsterCoordinates);
				if (distance < MaxRange and distance > MinRange) {
					if (tempMonster.first != nullptr) {
						if (tempMonster.second > distance)
							tempMonster = pair<void*, float>(monster, distance);
					}
					else
						tempMonster = pair<void*, float>(monster, distance);
				}
			}
		}
		return tempMonster.first;
	}
#pragma endregion
	/*
		ɱ��������ǵĹ���
	*/
#pragma region KillNavigationMonster
	static bool KillNavigationMonster() {
		void* monster = GetNavigationMonster();
		if (monster != nullptr) {
			void* healthMgr = *offsetPtr<void*>(monster, 0x7670);
			float health = *offsetPtr<float>(healthMgr, 0x64);
			if (health > 1) {
				*offsetPtr<float>(healthMgr, 0x60) = 0.1;
				return true;
			}
		}
		return false;
	}
#pragma endregion
	/*
		ɱ����������Ĺ���
	*/
#pragma region KillNearestMonster
	static bool KillNearestMonster(float MinRange = 0, float MaxRange = 9999999.0) {
		void* monster = GetNearestMonster(MinRange,MaxRange);
		if (monster != nullptr) {
			void* healthMgr = *offsetPtr<void*>(monster, 0x7670);
			float health = *offsetPtr<float>(healthMgr, 0x64);
			if (health > 1) {
				*offsetPtr<float>(healthMgr, 0x60) = 0.1;
				return true;
			}
		}
		return false;
	}
#pragma endregion
	/*
		ɱ�����һ�λ��еĹ���
	*/
#pragma region KillLastHitMonster
	static bool KillLastHitMonster() {
		if (Base::PlayerData::AttackMonsterPlot != nullptr) {
			void* healthMgr = *offsetPtr<void*>(Base::PlayerData::AttackMonsterPlot, 0x7670);
			float health = *offsetPtr<float>(healthMgr, 0x64);
			if (health > 1) {
				*offsetPtr<float>(healthMgr, 0x60) = 0.1;
				return true;
			}
		}
		return false;
	}
#pragma endregion
	/*
		���õ����������Ϊ
	*/
#pragma region NavigationMonsterBehaviorControl
	static bool NavigationMonsterBehaviorControl(int fsm) {
		void* monster = GetNavigationMonster();
		if (monster != nullptr) {
			Base::Monster::BehaviorControl(monster, fsm);
			return true;
		}
		return false;
	}
#pragma endregion
	/*
		���þ�������Ĺ������Ϊ
	*/
#pragma region NearestMonsterBehaviorControl
	static bool NearestMonsterBehaviorControl(int fsm) {
		void* monster = GetNearestMonster();
		if (monster != nullptr) {
			Base::Monster::BehaviorControl(monster, fsm);
			return true;
		}
		return false;
	}
#pragma endregion
	/*
		����������еĹ������Ϊ
	*/
#pragma region LastHitMonsterBehaviorControl
	static bool LastHitMonsterBehaviorControl(int fsm) {
		if (Base::PlayerData::AttackMonsterPlot != nullptr) {
			Base::Monster::BehaviorControl(Base::PlayerData::AttackMonsterPlot, fsm);
			return true;
		}
		return false;
	}
#pragma endregion
	/*
		���õ��������Buff
	*/
#pragma region SetNavigationMonsterBuff
	static bool SetNavigationMonsterBuff(string buff) {
		void* monster = GetNavigationMonster();
		if (monster != nullptr) {
			Base::Monster::SetBuff(monster, buff);
			return true;
		}
		return false;
	}
#pragma endregion
	/*
		���þ�������Ĺ����Buff
	*/
#pragma region SetNearestMonsterBuff
	static bool SetNearestMonsterBuff(string buff, float MinRange = 0, float MaxRange = 9999999.0) {
		void* monster = GetNearestMonster(MinRange, MaxRange);
		if (monster != nullptr) {
			Base::Monster::SetBuff(monster, buff);
			return true;
		}
		return false;
	}
#pragma endregion
	/*
		����������еĹ����Buff
	*/
#pragma region SetLastHitMonsterBuff
	static bool SetLastHitMonsterBuff(string buff) {
		if (Base::PlayerData::AttackMonsterPlot != nullptr) {
			Base::Monster::SetBuff(Base::PlayerData::AttackMonsterPlot, buff);
			return true;
		}
		return false;
	}
#pragma endregion
	/*
		���÷�Χ�����еĹ����Buff
	*/
#pragma region SetAllMonsterBuff
	static void SetAllMonsterBuff(string buff, float MinRange = 0, float MaxRange = 9999999.0) {
		for (auto [monster, monsterData] : Base::Monster::Monsters) {
			if (monster != nullptr) {
				if (
					monsterData.Id != Base::Monster::Filter.first and
					monsterData.SubId != Base::Monster::Filter.second and
					Base::Monster::Filter.first != 255 and
					Base::Monster::Filter.second != 255
					)
					continue;
				Base::Vector3 monsterCoordinates(
					*offsetPtr<float>(monster, 0x160),
					*offsetPtr<float>(monster, 0x164),
					*offsetPtr<float>(monster, 0x168)
				);
				float distance = Base::Calculation::DistanceBetweenTwoCoordinates(Base::PlayerData::Coordinate::Entity, monsterCoordinates);
				if (distance < MaxRange and distance > MinRange) {
					Base::Monster::SetBuff(monster, buff);
				}
			}
		}
	}
#pragma endregion
	/*
		ɱ����Χ�����й���
	*/
#pragma region KillAllMonster
	static void KillAllMonster(float MinRange = 0, float MaxRange = 9999999.0) {
		for (auto [monster, monsterData] : Base::Monster::Monsters) {
			if (monster != nullptr) {
				if (
					monsterData.Id != Base::Monster::Filter.first and
					monsterData.SubId != Base::Monster::Filter.second and
					Base::Monster::Filter.first != 255 and
					Base::Monster::Filter.second != 255
					)
					continue;
				Base::Vector3 monsterCoordinates(
					*offsetPtr<float>(monster, 0x160),
					*offsetPtr<float>(monster, 0x164),
					*offsetPtr<float>(monster, 0x168)
				);
				float distance = Base::Calculation::DistanceBetweenTwoCoordinates(Base::PlayerData::Coordinate::Entity, monsterCoordinates);
				if (distance < MaxRange and distance > MinRange) {
					void* healthMgr = *offsetPtr<void*>(monster, 0x7670);
					float health = *offsetPtr<float>(healthMgr, 0x64);
					if (health > 1) {
						*offsetPtr<float>(healthMgr, 0x60) = 0.1;
					}
				}
			}
		}
	}
#pragma endregion
	/*
		��ȡ�������������
	*/
#pragma region GetNavigationMonsterCoordinates
	static Base::Vector3 GetNavigationMonsterCoordinates() {
		void* monster = GetNavigationMonster();
		if (monster != nullptr) {
			return Base::Vector3(
				*offsetPtr<float>(monster, 0x160),
				*offsetPtr<float>(monster, 0x164),
				*offsetPtr<float>(monster, 0x168)
			);
		}
		return Base::Vector3();
	}
#pragma endregion
	/*
		��ȡ��������Ĺ��������
	*/
#pragma region GetNearestMonsterCoordinates
	static Base::Vector3 GetNearestMonsterCoordinates(float MinRange = 0, float MaxRange = 9999999.0) {
		void* monster = GetNearestMonster(MinRange, MaxRange);
		if (monster != nullptr) {
			return Base::Vector3(
				*offsetPtr<float>(monster, 0x160),
				*offsetPtr<float>(monster, 0x164),
				*offsetPtr<float>(monster, 0x168)
			);
		}
		return Base::Vector3();
	}
#pragma endregion
	/*
		��ȡ���һ�λ��еĹ��������
	*/
#pragma region GetLastHitMonsterCoordinates
	static Base::Vector3 GetLastHitMonsterCoordinates() {
		if (Base::PlayerData::AttackMonsterPlot != nullptr) {
			return Base::Vector3(
				*offsetPtr<float>(Base::PlayerData::AttackMonsterPlot, 0x160),
				*offsetPtr<float>(Base::PlayerData::AttackMonsterPlot, 0x164),
				*offsetPtr<float>(Base::PlayerData::AttackMonsterPlot, 0x168)
			);
		}
		return Base::Vector3();
	}
#pragma endregion
	/*
	���ù���ɸѡ��
	*/
#pragma region SetEnvironmentalFilter
	static void SetEnvironmentalFilter(int environmentalId, int environmentalSubId) {
		Base::World::EnvironmentalData::Filter = pair<int, int>(environmentalId, environmentalSubId);
	}
#pragma endregion
	/*
		�������ɸѡ��
	*/
#pragma region DisableEnvironmentalFilter
	static void DisableEnvironmentalFilter() {
		Base::World::EnvironmentalData::Filter = pair<int, int>(255, 255);
	}
#pragma endregion
	/*
		���÷�Χ�����л������������
	*/
#pragma region SetAllEnvironmentalCoordinates
	static void SetAllEnvironmentalCoordinates(Base::Vector3 Coordinates, float MinRange = 0, float MaxRange = 9999999.0) {
		for (auto [environmental, environmentalData] : Base::World::EnvironmentalData::Environmentals) {
			if (environmental != nullptr) {
				if (
					environmentalData.Id != Base::World::EnvironmentalData::Filter.first and
					environmentalData.SubId != Base::World::EnvironmentalData::Filter.second and
					Base::World::EnvironmentalData::Filter.first != 255 and
					Base::World::EnvironmentalData::Filter.second != 255
					)
					continue;
				Base::Vector3 environmentalCoordinates(
					*offsetPtr<float>(environmental, 0x160),
					*offsetPtr<float>(environmental, 0x164),
					*offsetPtr<float>(environmental, 0x168)
				);
				float distance = Base::Calculation::DistanceBetweenTwoCoordinates(Base::PlayerData::Coordinate::Entity, environmentalCoordinates);
				if (distance < MaxRange and distance > MinRange) {
					*offsetPtr<float>(environmental, 0x160) = Coordinates.x;
					*offsetPtr<float>(environmental, 0x164) = Coordinates.y;
					*offsetPtr<float>(environmental, 0x168) = Coordinates.z;
					//MoveTargetToPoint(environmental, environmentalCoordinates);
				}
			}
		}
	}
#pragma endregion
	/*
		�������Ѫ��������
	*/
#pragma region SetPlayerHealthAndEndurance
		static void SetPlayerBasicHealth(float health) {
			*offsetPtr<float>(Base::BasicGameData::PlayerPlot, 0x7628) = health;
		}
		static void SetPlayerHealth(float health) {
			void* StatusManagementPlot = *offsetPtr<undefined**>((undefined(*)())Base::BasicGameData::PlayerPlot, 0x7630);
			if (StatusManagementPlot != nullptr)
				*offsetPtr<float>(StatusManagementPlot, 0x64) = health;
		}
		static void SetPlayerMaxEndurance(float endurance) {
			void* StatusManagementPlot = *offsetPtr<undefined**>((undefined(*)())Base::BasicGameData::PlayerPlot, 0x7630);
			if (StatusManagementPlot != nullptr)
				*offsetPtr<float>(StatusManagementPlot, 0x144) = endurance;
		}
		static void SetPlayerEndurance(float endurance) {
			void* StatusManagementPlot = *offsetPtr<undefined**>((undefined(*)())Base::BasicGameData::PlayerPlot, 0x7630);
			if (StatusManagementPlot != nullptr)
				*offsetPtr<float>(StatusManagementPlot, 0x13C) = endurance;
		}
#pragma endregion
/*
	��ȡ���й��������
*/
#pragma region GetAllMonsterCoordinates
		static map<int, Base::Monster::MonsterData> GetAllMonsterCoordinates() {
			map<int, Base::Monster::MonsterData> monsterList;
			int installcount = 0;
			for (auto [monster, monsterData] : Base::Monster::Monsters) {
				if (monster != nullptr) {
					if (
						monsterData.Id != Base::Monster::Filter.first and
						monsterData.SubId != Base::Monster::Filter.second and
						Base::Monster::Filter.first != 255 and
						Base::Monster::Filter.second != 255
						)
						continue;
					monsterList[installcount] = monsterData;
					installcount++;
				}
			}
			return monsterList;
		}
		static map<int, Base::Monster::MonsterData> GetAllMonsterCoordinatesRelativeToTarget(Base::Vector3 Target, float MinRange = 0, float MaxRange = 9999999.0) {
			map<int, Base::Monster::MonsterData> monsterList;
			int installcount = 0;
			for (auto [monster, monsterData] : Base::Monster::Monsters) {
				if (monster != nullptr) {
					if (
						monsterData.Id != Base::Monster::Filter.first and
						monsterData.SubId != Base::Monster::Filter.second and
						Base::Monster::Filter.first != 255 and
						Base::Monster::Filter.second != 255
						)
						continue;
					float distance = Base::Calculation::DistanceBetweenTwoCoordinates(Target,
						Base::Vector3(monsterData.CoordinatesX, monsterData.CoordinatesY, monsterData.CoordinatesZ));
					if (distance < MaxRange and distance > MinRange) {
						monsterList[installcount] = monsterData;
						installcount++;
					}
				}
			}
			return monsterList;
		}
		static map<int, Base::Monster::MonsterData> GetAllMonsterCoordinatesRelativeToPlayers(float MinRange = 0, float MaxRange = 9999999.0) {
			map<int, Base::Monster::MonsterData> monsterList;
			int installcount = 0;
			for (auto [monster, monsterData] : Base::Monster::Monsters) {
				if (monster != nullptr) {
					if (
						monsterData.Id != Base::Monster::Filter.first and
						monsterData.SubId != Base::Monster::Filter.second and
						Base::Monster::Filter.first != 255 and
						Base::Monster::Filter.second != 255
						)
						continue;
					float distance = Base::Calculation::DistanceBetweenTwoCoordinates(Base::PlayerData::Coordinate::Entity,
						Base::Vector3(monsterData.CoordinatesX, monsterData.CoordinatesY, monsterData.CoordinatesZ));
					if (distance < MaxRange and distance > MinRange) {
						monsterList[installcount] = monsterData;
						installcount++;
					}
				}
			}
			return monsterList;
		}
#pragma endregion
/*
	��ȡ���й��������
*/
#pragma region GetAllMonsterHealth
		struct MonsterHealth {
			void* Plot;
			float Health;
			float MaxHealth;
			int Id;
			int SubId;
			MonsterHealth(
				void* Plot = nullptr,
				float Health = 0,
				float MaxHealth = 0,
				int Id = 0,
				int SubId = 0)
				:Plot(Plot), Health(Health), MaxHealth(MaxHealth), Id(Id), SubId(SubId) {
			};
		};

		static map<int, MonsterHealth> GetAllMonsterHealth() {
			map<int, MonsterHealth> monsterList;
			int installcount = 0;
			for (auto [monster, monsterData] : Base::Monster::Monsters) {
				if (monster != nullptr) {
					if (
						monsterData.Id != Base::Monster::Filter.first and
						monsterData.SubId != Base::Monster::Filter.second and
						Base::Monster::Filter.first != 255 and
						Base::Monster::Filter.second != 255
						)
						continue;
					void* healthMgr = *offsetPtr<void*>(monster, 0x7670);
					float health = *offsetPtr<float>(healthMgr, 0x64);
					float maxHealth = *offsetPtr<float>(healthMgr, 0x60);
					monsterList[installcount] = MonsterHealth(monster, health, maxHealth, monsterData.Id, monsterData.SubId);
					installcount++;
				}
			}
			return monsterList;
		}
		static map<int, MonsterHealth> GetAllMonsterHealthRelativeToTarget(Base::Vector3 Target, float MinRange = 0, float MaxRange = 9999999.0) {
			map<int, MonsterHealth> monsterList;
			int installcount = 0;
			for (auto [monster, monsterData] : Base::Monster::Monsters) {
				if (monster != nullptr) {
					if (
						monsterData.Id != Base::Monster::Filter.first and
						monsterData.SubId != Base::Monster::Filter.second and
						Base::Monster::Filter.first != 255 and
						Base::Monster::Filter.second != 255
						)
						continue;
					float distance = Base::Calculation::DistanceBetweenTwoCoordinates(Target,
						Base::Vector3(monsterData.CoordinatesX, monsterData.CoordinatesY, monsterData.CoordinatesZ));
					if (distance < MaxRange and distance > MinRange) {
						void* healthMgr = *offsetPtr<void*>(monster, 0x7670);
						float health = *offsetPtr<float>(healthMgr, 0x64);
						float maxHealth = *offsetPtr<float>(healthMgr, 0x60);
						monsterList[installcount] = MonsterHealth(monster, health, maxHealth, monsterData.Id, monsterData.SubId);
						installcount++;
					}
				}
			}
			return monsterList;
		}
		static map<int, MonsterHealth> GetAllMonsterHealthRelativeToPlayers(float MinRange = 0, float MaxRange = 9999999.0) {
			map<int, MonsterHealth> monsterList;
			int installcount = 0;
			for (auto [monster, monsterData] : Base::Monster::Monsters) {
				if (monster != nullptr) {
					if (
						monsterData.Id != Base::Monster::Filter.first and
						monsterData.SubId != Base::Monster::Filter.second and
						Base::Monster::Filter.first != 255 and
						Base::Monster::Filter.second != 255
						)
						continue;
					float distance = Base::Calculation::DistanceBetweenTwoCoordinates(Base::PlayerData::Coordinate::Entity,
						Base::Vector3(monsterData.CoordinatesX, monsterData.CoordinatesY, monsterData.CoordinatesZ));
					if (distance < MaxRange and distance > MinRange) {
						void* healthMgr = *offsetPtr<void*>(monster, 0x7670);
						float health = *offsetPtr<float>(healthMgr, 0x64);
						float maxHealth = *offsetPtr<float>(healthMgr, 0x60);
						monsterList[installcount] = MonsterHealth(monster, health, maxHealth, monsterData.Id, monsterData.SubId);
						installcount++;
					}
				}
			}
			return monsterList;
		}
#pragma endregion
/*
	��ȡ��Χ�����л������������
*/
#pragma region GetAllEnvironmentalCoordinates
		static map<int, Base::World::EnvironmentalData::EnvironmentalData> GetAllEnvironmentalCoordinates(float MinRange = 0, float MaxRange = 9999999.0) {
			map<int, Base::World::EnvironmentalData::EnvironmentalData> environmentaList;
			int installcount = 0;
			for (auto [environmental, environmentalData] : Base::World::EnvironmentalData::Environmentals) {
				if (environmental != nullptr) {
					if (
						environmentalData.Id != Base::World::EnvironmentalData::Filter.first and
						environmentalData.SubId != Base::World::EnvironmentalData::Filter.second and
						Base::World::EnvironmentalData::Filter.first != 255 and
						Base::World::EnvironmentalData::Filter.second != 255
						)
						continue;
					float distance = Base::Calculation::DistanceBetweenTwoCoordinates(Base::PlayerData::Coordinate::Entity,
						Base::Vector3(environmentalData.CoordinatesX, environmentalData.CoordinatesY, environmentalData.CoordinatesZ));
					if (distance < MaxRange and distance > MinRange) {
						environmentaList[installcount] = environmentalData;
						installcount++;
					}
				}
			}
			return environmentaList;
		}
#pragma endregion
/*
	��ȡ������쳣״̬
*/
#pragma region GetAllMonsterDeBuff
		struct MonsterDeBuff {
			void* Plot; 
			map<string, MonsterBuff::MonsterBuffState> DeBuff;
			int Id;
			int SubId;
			MonsterDeBuff(
				void* Plot = nullptr,
				map<string, MonsterBuff::MonsterBuffState> DeBuff = {},
				int Id = 0,
				int SubId = 0)
				:Plot(Plot), DeBuff(DeBuff), Id(Id), SubId(SubId) {
			};
		};
		static map<int, MonsterDeBuff> GetAllMonsterDeBuff() {
			map<int, MonsterDeBuff> monsterList;
			int installcount = 0;
			for (auto [monster, monsterData] : Base::Monster::Monsters) {
				if (monster != nullptr) {
					if (
						monsterData.Id != Base::Monster::Filter.first and
						monsterData.SubId != Base::Monster::Filter.second and
						Base::Monster::Filter.first != 255 and
						Base::Monster::Filter.second != 255
						)
						continue;
					map<string, MonsterBuff::MonsterBuffState> DeBuff;
					for (string debuff : vector<string>{"Covet","Dizziness","Paralysis","Sleep","Poisoning","Ride","Ridedowna","Reducebreath","Explode","Flicker","FlickerG","Smoke","Traphole","Stasistrap"}) {
						DeBuff[debuff] = MonsterBuff::GetMonsterBuffState(monster, debuff);
					}
					monsterList[installcount] = MonsterDeBuff(monster, DeBuff, monsterData.Id, monsterData.SubId);
					installcount++;
				}
			}
			return monsterList;
		}
		static map<int, MonsterDeBuff> GetAllMonsterDeBuffRelativeToTarget(Base::Vector3 Target, float MinRange = 0, float MaxRange = 9999999.0) {
			map<int, MonsterDeBuff> monsterList;
			int installcount = 0;
			for (auto [monster, monsterData] : Base::Monster::Monsters) {
				if (monster != nullptr) {
					if (
						monsterData.Id != Base::Monster::Filter.first and
						monsterData.SubId != Base::Monster::Filter.second and
						Base::Monster::Filter.first != 255 and
						Base::Monster::Filter.second != 255
						)
						continue;
					float distance = Base::Calculation::DistanceBetweenTwoCoordinates(Target,
						Base::Vector3(monsterData.CoordinatesX, monsterData.CoordinatesY, monsterData.CoordinatesZ));
					if (distance < MaxRange and distance > MinRange) {
						map<string, MonsterBuff::MonsterBuffState> DeBuff;
						for (string debuff : vector<string>{ "Covet","Dizziness","Paralysis","Sleep","Poisoning","Ride","Ridedowna","Reducebreath","Explode","Flicker","FlickerG","Smoke","Traphole","Stasistrap" }) {
							DeBuff[debuff] = MonsterBuff::GetMonsterBuffState(monster, debuff);
						}
						monsterList[installcount] = MonsterDeBuff(monster, DeBuff, monsterData.Id, monsterData.SubId);
						installcount++;
					}
				}
			}
			return monsterList;
		}
		static map<int, MonsterDeBuff> GetAllMonsterDebuffRelativeToPlayers(float MinRange = 0, float MaxRange = 9999999.0) {
			map<int, MonsterDeBuff> monsterList;
			int installcount = 0;
			for (auto [monster, monsterData] : Base::Monster::Monsters) {
				if (monster != nullptr) {
					if (
						monsterData.Id != Base::Monster::Filter.first and
						monsterData.SubId != Base::Monster::Filter.second and
						Base::Monster::Filter.first != 255 and
						Base::Monster::Filter.second != 255
						)
						continue;
					float distance = Base::Calculation::DistanceBetweenTwoCoordinates(Base::PlayerData::Coordinate::Entity,
						Base::Vector3(monsterData.CoordinatesX, monsterData.CoordinatesY, monsterData.CoordinatesZ));
					if (distance < MaxRange and distance > MinRange) {
						map<string, MonsterBuff::MonsterBuffState> DeBuff;
						for (string debuff : vector<string>{ "Covet","Dizziness","Paralysis","Sleep","Poisoning","Ride","Ridedowna","Reducebreath","Explode","Flicker","FlickerG","Smoke","Traphole","Stasistrap" }) {
							DeBuff[debuff] = MonsterBuff::GetMonsterBuffState(monster, debuff);
						}
						monsterList[installcount] = MonsterDeBuff(monster, DeBuff, monsterData.Id, monsterData.SubId);
						installcount++;
					}
				}
			}
			return monsterList;
		}
#pragma endregion
/*
	��ȡ��������ֵ
*/
#pragma region GetWeaponCharacteristicValue
		static int GetWeaponCharacteristicIntValue(string ptr) {
			int Ptr = 0;
			sscanf_s(ptr.c_str(), "%x", &Ptr);
			void* WeaponEntityPlot = *offsetPtr<void*>(Base::BasicGameData::PlayerPlot, 0x76B0);
			if (WeaponEntityPlot != nullptr){
				return *offsetPtr<int>(WeaponEntityPlot, Ptr);
			}
		}
		static float GetWeaponCharacteristicFloatValue(string ptr) {
			int Ptr = 0;
			sscanf_s(ptr.c_str(), "%x", &Ptr);
			void* WeaponEntityPlot = *offsetPtr<void*>(Base::BasicGameData::PlayerPlot, 0x76B0);
			if (WeaponEntityPlot != nullptr) {
				return *offsetPtr<float>(WeaponEntityPlot, Ptr);
			}
		}
#pragma endregion

//��ȡĿ¼�е��ļ�
	void getFiles(string path, vector<string>& files)
		{
			//�ļ����
			long   hFile = 0;
			//�ļ���Ϣ
			struct _finddata_t fileinfo;
			string p;
			if ((hFile = _findfirst(p.assign(path).append("\\*.lua").c_str(), &fileinfo)) != -1)
			{
				do
				{
					if (!(fileinfo.attrib & _A_SUBDIR))
					{
						files.push_back(p.assign(path).append("\\").append(fileinfo.name));
					}
				} while (_findnext(hFile, &fileinfo) == 0);
				_findclose(hFile);
			}
		}
}


