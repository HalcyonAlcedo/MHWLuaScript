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
		将目标移动到坐标点
		适用于玩家、怪物、环境生物、环境采集物、环境实体
		注：
			速度值越大，速度越慢
			玩家和怪物推荐使用MovePlayerToPoint和MoveMonsterToPoint进行操作
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
		将目标移动到目标
		适用于玩家、怪物、环境生物、环境采集物、环境实体
		注：
			速度值越大，速度越慢
			玩家和怪物推荐使用MovePlayerToTarget和MoveMonsterToTarget进行操作
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
		将玩家移动到目标
		注：
			速度值越大，速度越慢
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
		向游戏内发送消息
	*/
#pragma region ShowMessage
	static void ShowMessage(std::string message) {
		MH::Chat::ShowGameMessage(*(undefined**)MH::Chat::MainPtr, (undefined*)&message[0], -1, -1, 0);
	}
#pragma endregion
	/*
		设置怪物筛选器
	*/
#pragma region SetMonsterFilter
	static void SetMonsterFilter(int monsterId, int monsterSubId) {
		Base::Monster::Filter = pair<int, int>(monsterId, monsterSubId);
	}
#pragma endregion
	/*
		清除怪物筛选器
	*/
#pragma region DisableMonsterFilter
	static void DisableMonsterFilter() {
		Base::Monster::Filter = pair<int, int>(255, 255);
	}
#pragma endregion
	/*
		获取导航的怪物
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
		获取距离最近的怪物
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
		杀死导航标记的怪物
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
		杀死距离最近的怪物
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
		杀死最后一次击中的怪物
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
		设置导航怪物的行为
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
		设置距离最近的怪物的行为
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
		设置最近击中的怪物的行为
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
		设置导航怪物的Buff
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
		设置距离最近的怪物的Buff
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
		设置最近击中的怪物的Buff
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
		设置范围内所有的怪物的Buff
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
		杀死范围内所有怪物
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
		获取导航怪物的坐标
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
		获取距离最近的怪物的坐标
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
		获取最后一次击中的怪物的坐标
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
	设置怪物筛选器
	*/
#pragma region SetEnvironmentalFilter
	static void SetEnvironmentalFilter(int environmentalId, int environmentalSubId) {
		Base::World::EnvironmentalData::Filter = pair<int, int>(environmentalId, environmentalSubId);
	}
#pragma endregion
	/*
		清除怪物筛选器
	*/
#pragma region DisableEnvironmentalFilter
	static void DisableEnvironmentalFilter() {
		Base::World::EnvironmentalData::Filter = pair<int, int>(255, 255);
	}
#pragma endregion
	/*
		设置范围内所有环境生物的坐标
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
		设置玩家血量和耐力
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
	获取所有怪物的坐标
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
	获取所有怪物的生命
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
	获取范围内所有环境生物的坐标
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
	获取怪物的异常状态
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
	获取武器特性值
*/
#pragma region GetWeaponCharacteristicValue
		static int GetWeaponCharacteristicIntValue(string ptr) {
			long long Ptr = 0;
			sscanf_s(ptr.c_str(), "%p", &Ptr, sizeof(long long));
			void* ptrAddress = (void*)Ptr;
			if (ptrAddress != nullptr) {
				void* WeaponEntityPlot = *offsetPtr<void*>(Base::BasicGameData::PlayerPlot, 0x76B0);
				if (WeaponEntityPlot != nullptr) {
					return *offsetPtr<int>(WeaponEntityPlot, Ptr);
				}
			}
			return 0;
		}
		static float GetWeaponCharacteristicFloatValue(string ptr) {
			long long Ptr = 0;
			sscanf_s(ptr.c_str(), "%p", &Ptr, sizeof(long long));
			void* ptrAddress = (void*)Ptr;
			if (ptrAddress != nullptr) {
				void* WeaponEntityPlot = *offsetPtr<void*>(Base::BasicGameData::PlayerPlot, 0x76B0);
				if (WeaponEntityPlot != nullptr) {
					return *offsetPtr<float>(WeaponEntityPlot, Ptr);
				}
			}
			return 0;
		}
		static char GetWeaponCharacteristicByteValue(string ptr) {
			long long Ptr = 0;
			sscanf_s(ptr.c_str(), "%p", &Ptr, sizeof(long long));
			void* ptrAddress = (void*)Ptr;
			if (ptrAddress != nullptr) {
				void* WeaponEntityPlot = *offsetPtr<void*>(Base::BasicGameData::PlayerPlot, 0x76B0);
				if (WeaponEntityPlot != nullptr) {
					return *offsetPtr<char>(WeaponEntityPlot, Ptr);
				}
			}
			return 0;
		}
#pragma endregion
/*
	获取对玩家仇恨的怪物
*/
#pragma region GetMonstersHateToPlayers
		static vector<void*> GetMonstersHateToPlayers() {
			vector<void*> monsterList;
			for (auto [monster, monsterData] : Base::Monster::Monsters) {
				if (monster != nullptr) {
					if (
						monsterData.Id != Base::Monster::Filter.first and
						monsterData.SubId != Base::Monster::Filter.second and
						Base::Monster::Filter.first != 255 and
						Base::Monster::Filter.second != 255
						)
						continue;
					if(Base::Monster::GetHateTarget(monster) != nullptr)
					monsterList.push_back(Base::Monster::GetHateTarget(monster));
				}
			}
			return monsterList;
		}
#pragma endregion
/*
	实体属性操作
*/
#pragma region EntityProperties
		struct EntityProperties {
			Base::Vector3 Coordinate;
			Base::Vector3 Size;
			Base::Vector3 Action;
			EntityProperties(
				Base::Vector3 Coordinate = Base::Vector3(),
				Base::Vector3 Size = Base::Vector3(),
				Base::Vector3 Action = Base::Vector3())
				:Coordinate(Coordinate), Size(Size), Action(Action) {
			};
		};
		static EntityProperties GetEntityProperties(string ptr) {
			long long Ptr = 0;
			sscanf_s(ptr.c_str(), "%p", &Ptr, sizeof(long long));
			void* EntityAddress = (double*)Ptr;
			if (EntityAddress != nullptr) {
				void* ActionPlot = *offsetPtr<undefined**>((undefined(*)())Ptr, 0x468);
				Base::Vector3 Action = Base::Vector3();
				if (ActionPlot != nullptr) {
					Action = Base::Vector3(
						*offsetPtr<float>(ActionPlot, 0xE9C4),
						*offsetPtr<float>(ActionPlot, 0x10c), 
						*offsetPtr<float>(ActionPlot, 0x114)
					);
				}
					
				return EntityProperties(
					Base::Vector3(
						*(float*)(Ptr + 0x160),
						*(float*)(Ptr + 0x164),
						*(float*)(Ptr + 0x168)
					),
					Base::Vector3(
						*(float*)(Ptr + 0x180),
						*(float*)(Ptr + 0x184),
						*(float*)(Ptr + 0x188)
					),
					Action
				);
			}
			return EntityProperties();
		}
		static void SetEntityCoordinate(string ptr, Base::Vector3 Coordinate) {
			long long Ptr = 0;
			sscanf_s(ptr.c_str(), "%p", &Ptr, sizeof(long long));
			void* EntityAddress = (double*)Ptr;
			if (EntityAddress != nullptr) {
				*(float*)(Ptr + 0x160) = Coordinate.x;
				*(float*)(Ptr + 0x164) = Coordinate.y;
				*(float*)(Ptr + 0x168) = Coordinate.z;
			}
		}
		static void SetEntitySize(string ptr, Base::Vector3 Size) {
			long long Ptr = 0;
			sscanf_s(ptr.c_str(), "%p", &Ptr, sizeof(long long));
			void* EntityAddress = (double*)Ptr;
			if (EntityAddress != nullptr) {
				*(float*)(Ptr + 0x180) = Size.x;
				*(float*)(Ptr + 0x184) = Size.y;
				*(float*)(Ptr + 0x188) = Size.z;
			}
		}
		static void SetEntityActionFrame(string ptr, float ActionFrame) {
			long long Ptr = 0;
			sscanf_s(ptr.c_str(), "%p", &Ptr, sizeof(long long));
			void* EntityAddress = (double*)Ptr;
			if (EntityAddress != nullptr) {
				void* ActionPlot = *offsetPtr<undefined**>((undefined(*)())Ptr, 0x468);
				if (ActionPlot != nullptr)
					*offsetPtr<float>(ActionPlot, 0x10c) = ActionFrame;
			}
		}
#pragma endregion
#pragma region GetMonstersName_CN
		static string GetMonstersName_CN(int id) {
			if( id == 0 ) return u8"蠻顎龍";    if( id == 1 ) return u8"火龍";    if( id == 2 ) return u8"草食龍";    if( id == 3 ) return u8"凶豺龍";
			if( id == 4 ) return u8"熔山龍";    if( id == 5 ) return u8"菌豬";    if( id == 6 ) return u8"咬魚";    if( id == 7 ) return u8"大凶豺龍";
			if( id == 8 ) return u8"冠突龍♂";    if( id == 9 ) return u8"雌火龍";    if( id == 10 ) return u8"櫻火龍";    if( id == 11 ) return u8"蒼火龍";
			if( id == 12 ) return u8"角龍";    if( id == 13 ) return u8"黑角龍";    if( id == 14 ) return u8"麒麟";    if( id == 15 ) return u8"貝希摩斯";
			if( id == 16 ) return u8"鋼龍";    if( id == 17 ) return u8"炎妃龍";    if( id == 18 ) return u8"炎王龍";    if( id == 19 ) return u8"熔岩龍";
			if( id == 20 ) return u8"恐暴龍";    if( id == 21 ) return u8"土砂龍";    if( id == 22 ) return u8"爆鎚龍";    if( id == 23 ) return u8"鹿首精";
			if( id == 24 ) return u8"毒妖鳥";    if( id == 25 ) return u8"滅盡龍";    if( id == 26 ) return u8"冥燈龍";    if( id == 27 ) return u8"搔鳥";
			if( id == 28 ) return u8"眩鳥";    if( id == 29 ) return u8"泥魚龍";    if( id == 30 ) return u8"飛雷龍";    if( id == 31 ) return u8"浮空龍";
			if( id == 32 ) return u8"風漂龍";    if( id == 33 ) return u8"大凶顎龍";    if( id == 34 ) return u8"慘爪龍";    if( id == 35 ) return u8"骨鎚龍";
			if( id == 36 ) return u8"屍套龍";    if( id == 37 ) return u8"岩賊龍";    if( id == 38 ) return u8"絢輝龍";    if( id == 39 ) return u8"爆鱗龍";
			if( id == 40 ) return u8"背甲龍";    if( id == 41 ) return u8"精靈鹿";    if( id == 42 ) return u8"精靈鹿";    if( id == 43 ) return u8"巨甲蟲";
			if( id == 44 ) return u8"巨蜂";    if( id == 45 ) return u8"行翼龍";    if( id == 46 ) return u8"冠突龍♀";    if( id == 47 ) return u8"芳翼龍";
			if( id == 48 ) return u8"貓蜥龍";    if( id == 49 ) return u8"酸翼龍";    if( id == 50 ) return u8"凶顎龍";    if( id == 51 ) return u8"古代鹿首精";
			if( id == 52 ) return u8"突擊龍";    if( id == 53 ) return u8"響翼龍";    if( id == 54 ) return u8"散熱器官";    if( id == 55 ) return u8"×副散熱器官";
			if( id == 56 ) return u8"奇面族";    if( id == 57 ) return u8"？？？";    if( id == 58 ) return u8"雌火龍？？？";    if( id == 59 ) return u8"冠突龍";
			if( id == 60 ) return u8"黃金奇面族";    if( id == 61 ) return u8"轟龍";    if( id == 62 ) return u8"迅龍";    if( id == 63 ) return u8"冰牙龍";
			if( id == 64 ) return u8"惶怒恐暴龍";    if( id == 65 ) return u8"碎龍";    if( id == 66 ) return u8"斬龍";    if( id == 67 ) return u8"硫斬龍";
			if( id == 68 ) return u8"雷顎龍";    if( id == 69 ) return u8"水妖鳥";    if( id == 70 ) return u8"殲世滅盡龍";    if( id == 71 ) return u8"痺毒龍";
			if( id == 72 ) return u8"浮眠龍";    if( id == 73 ) return u8"霜翼風漂龍";    if( id == 74 ) return u8"兇爪龍";    if( id == 75 ) return u8"霧瘴屍套龍";
			if( id == 76 ) return u8"紅蓮爆鱗龍";    if( id == 77 ) return u8"冰魚龍";    if( id == 78 ) return u8"猛牛龍";    if( id == 79 ) return u8"冰呪龍";
			if( id == 80 ) return u8"溟波龍";    if( id == 81 ) return u8"天地煌啼龍";    if( id == 82 ) return u8"波波";    if( id == 83 ) return u8"雪鹿";
			if( id == 84 ) return u8"冰豺狼";    if( id == 85 ) return u8"冬翼龍";    if( id == 86 ) return u8"獸纏族";    if( id == 87 ) return u8"煌黑龍";
			if( id == 88 ) return u8"金火龍";    if( id == 89 ) return u8"銀火龍";    if( id == 90 ) return u8"黑狼鳥";    if( id == 91 ) return u8"金獅子";
			if( id == 92 ) return u8"激昂金獅子";    if( id == 93 ) return u8"黑轟龍";    if( id == 94 ) return u8"雷狼龍";    if( id == 95 ) return u8"獄狼龍";
			if( id == 96 ) return u8"猛爆碎龍";    if( id == 97 ) return u8"冥赤龍";    if( id == 98 ) return u8"Unavailable";    if( id == 99 ) return u8"戰痕黑狼鳥";
			if( id == 100 ) return u8"霜刃冰牙龍";    if( id == 101 ) return u8"黑龍";
			return "未知";
		}
#pragma endregion
	//获取目录中的文件
	void getFiles(string path, vector<string>& files)
	{
		//文件句柄
		long   hFile = 0;
		//文件信息
		struct _finddata_t fileinfo;
		string p;
		if ((hFile = _findfirst(p.assign(path).append("\\*.lua").c_str(), &fileinfo)) != -1)
		{
			do
			{
				if (!(fileinfo.attrib & _A_SUBDIR))
				{
					Base::LuaHandle::LuaCode[fileinfo.name] = Base::LuaHandle::LuaCodeData(fileinfo.name,"", p.assign(path).append("\\").append(fileinfo.name),true);
					Base::LuaHandle::LuaCode[fileinfo.name].Update();
					files.push_back(fileinfo.name);
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
	}
	//utf8编码字符串
	std::string string_To_UTF8(const std::string& str)
	{
		int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

		wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
		ZeroMemory(pwBuf, nwLen * 2 + 2);

		::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

		int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

		char* pBuf = new char[nLen + 1];
		ZeroMemory(pBuf, nLen + 1);

		::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

		std::string retStr(pBuf);

		delete[]pwBuf;
		delete[]pBuf;

		pwBuf = NULL;
		pBuf = NULL;

		return retStr;
	}
}


