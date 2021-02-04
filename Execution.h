#pragma once
#include "Component.h"

using namespace std;
using namespace loader;

namespace Execution {
	void Main() {
		//检查CD
		if (!Base::Chronoscope::CheckChronoscope("BlinkCD")) {
			//瞄准状态下双击W
			if (Base::Keyboard::CheckKey(87, 2) and Base::PlayerData::AimingState and Base::PlayerData::WeaponType != 9) {
				Component::MovePlayerToPoint(
					Component::Coordinate{
					Base::PlayerData::Coordinate::Collimator.x,
					Base::PlayerData::Coordinate::Collimator.y,
					Base::PlayerData::Coordinate::Collimator.z
					},
					Component::Effect{ true,2003,5 }
				);
				//添加5秒CD
				Base::Chronoscope::AddChronoscope(5.0, "BlinkCD", true);
			}
		}
		else
			//CD过程中添加CD特效
			Base::PlayerData::Effects::GenerateSpecialEffects(2002, 0);
	}
}