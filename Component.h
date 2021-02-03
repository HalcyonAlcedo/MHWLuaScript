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
	static void MovePlayerToPoint(Coordinate Point, Effect effect, bool Instant = true, float speed = 100.0) {
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
}