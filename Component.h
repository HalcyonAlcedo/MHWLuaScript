#pragma once

using namespace std;
using namespace loader;

namespace Component {
	struct Coordinate {
		float x, y, z;
		Coordinate(float x = 0, float y = 0, float z = 0) :x(x), y(y), z(z) {
		};
	};
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
	static void MoveTargetToPoint(void* Target, Coordinate Point,bool Instant = true,float speed = 100.0) {
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
	/*
		将目标移动到目标
		适用于玩家、怪物、环境生物、环境采集物、环境实体
		注：
			速度值越大，速度越慢
			玩家和怪物推荐使用MovePlayerToTarget和MoveMonsterToTarget进行操作
	*/
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
	/*
		将玩家移动到目标
		注：
			速度值越大，速度越慢
	*/
	static void MovePlayerToPoint(Coordinate Point, Effect effect = Effect{false}, bool Instant = true, float speed = 100.0) {
		if (effect.Enable) {
			Base::PlayerData::Effects::GenerateSpecialEffects(effect.group, effect.record);
		}

		if (Instant) {
			Base::PlayerData::Coordinate::TransportCoordinate(Point.x,Point.y,Point.z);
		}
		else {
			MoveTargetToPoint(Base::BasicGameData::PlayerPlot, Point, false, speed);
		}
	}
	/*
		向游戏内发送消息
	*/
	static void ShowMessage(std::string message) {
		MH::Chat::ShowGameMessage(*(undefined**)MH::Chat::MainPtr, (undefined*)&message[0], -1, -1, 0);
	}
	/*
		设置怪物筛选器
	*/
	static void SetMonsterFilter(int monsterId, int monsterSubId) {
		Base::Monster::Filter = pair<int, int>(monsterId, monsterSubId);
	}
	/*
		清除怪物筛选器
	*/
	static void DisableMonsterFilter() {
		Base::Monster::Filter = pair<int, int>(255, 255);
	}
	/*
		获取导航的怪物
	*/
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
	/*
		获取距离最近的怪物
	*/
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
	/*
		杀死导航标记的怪物
	*/
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
	/*
		杀死距离最近的怪物
	*/
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
	/*
		杀死最后一次击中的怪物
	*/
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
	/*
		设置导航怪物的行为
	*/
	static bool NavigationMonsterBehaviorControl(int fsm) {
		void* monster = GetNavigationMonster();
		if (monster != nullptr) {
			Base::Monster::BehaviorControl(monster, fsm);
			return true;
		}
		return false;
	}
	/*
		设置距离最近的怪物的行为
	*/
	static bool NearestMonsterBehaviorControl(int fsm) {
		void* monster = GetNearestMonster();
		if (monster != nullptr) {
			Base::Monster::BehaviorControl(monster, fsm);
			return true;
		}
		return false;
	}
	/*
		设置最近击中的怪物的行为
	*/
	static bool LastHitMonsterBehaviorControl(int fsm) {
		if (Base::PlayerData::AttackMonsterPlot != nullptr) {
			Base::Monster::BehaviorControl(Base::PlayerData::AttackMonsterPlot, fsm);
			return true;
		}
		return false;
	}
	/*
		设置导航怪物的Buff
	*/
	static bool SetNavigationMonsterBuff(string buff) {
		void* monster = GetNavigationMonster();
		if (monster != nullptr) {
			Base::Monster::SetBuff(monster, buff);
			return true;
		}
		return false;
	}
	/*
		设置距离最近的怪物的Buff
	*/
	static bool SetNearestMonsterBuff(string buff, float MinRange = 0, float MaxRange = 9999999.0) {
		void* monster = GetNearestMonster(MinRange, MaxRange);
		if (monster != nullptr) {
			Base::Monster::SetBuff(monster, buff);
			return true;
		}
		return false;
	}
	/*
		设置最近击中的怪物的Buff
	*/
	static bool SetLastHitMonsterBuff(string buff) {
		if (Base::PlayerData::AttackMonsterPlot != nullptr) {
			Base::Monster::SetBuff(Base::PlayerData::AttackMonsterPlot, buff);
			return true;
		}
		return false;
	}
}