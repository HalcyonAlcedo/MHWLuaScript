#pragma once
#include "loader.h"

using namespace std;
using namespace loader;

namespace Execution {
	void Main() {
		//瞄准状态下双击W
		if (Base::Keyboard::CheckKey(87,2) and Base::PlayerData::AimingState) {
			//添加特效
			Base::PlayerData::Effects::GenerateSpecialEffects(2003, 1);
			//设置坐标
			Base::PlayerData::Coordinate::TransportCoordinate(
				Base::PlayerData::Coordinate::Collimator.x,
				Base::PlayerData::Coordinate::Collimator.y,
				Base::PlayerData::Coordinate::Collimator.z);
		}
	}
}