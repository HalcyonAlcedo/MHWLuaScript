#pragma once
using namespace std;
namespace PlayerBuff {
	static int GetBuffPtr(std::string buff) {
		//笛子
			//笛·自我强化
		if (buff == "Whistle Self Improvement") {
			return 0x38;
		}
		//笛·攻击力UP大
		if (buff == "Whistle Attack Up") {
			return 0x40;
		}
		//笛·体力UP大
		if (buff == "Whistle Health Up") {
			return 0x48;
		}
		//笛·耐力消耗减轻大
		if (buff == "Whistle Stamina Use Reduced") {
			return 0x50;
		}
		//笛·风压无效
		if (buff == "Whistle All Wind Pressure Negated") {
			return 0x58;
		}
		//笛·防御力UP大
		if (buff == "Whistle Defense Up") {
			return 0x60;
		}
		//笛·特殊道具消耗减轻大
		if (buff == "Whistle Tool Use Drain Reduced") {
			return 0x68;
		}
		//笛·体力回复速度UP大
		if (buff == "Whistle Recovery Up") {
			return 0x84;
		}
		//笛·听觉保护大
		if (buff == "Whistle Earplugs") {
			return 0x8c;
		}
		//笛·精灵王的加护
		if (buff == "Whistle Divine Protection") {
			return 0x90;
		}
		//笛·导虫追踪力强化
		if (buff == "Whistle Scoutfly Power Up") {
			return 0x94;
		}
		//笛·地形伤害无效
		if (buff == "Whistle Envir. Damage Negated") {
			return 0x98;
		}
		//笛·晕厥无效
		if (buff == "Whistle Stun Negated") {
			return 0x9c;
		}
		//笛·麻痹无效
		if (buff == "Whistle Paralysis Negated") {
			return 0xa0;
		}
		//笛·震动无效
		if (buff == "Whistle Tremors Negated") {
			return 0xa4;
		}
		//笛·适应泥沙水场深雪
		if (buff == "Whistle Much/Water/Deep Snow Res") {
			return 0xa8;
		}
		//笛·火属性防御UP大
		if (buff == "Whistle Fire Res Up") {
			return 0xb0;
		}
		//笛·水属性防御UP大
		if (buff == "Whistle Water Res Up") {
			return 0xb8;
		}
		//笛·雷属性防御UP大
		if (buff == "Whistle Thunder Res Up") {
			return 0xc0;
		}
		//笛·冰属性防御UP大
		if (buff == "Whistle Ice Res Up") {
			return 0xc8;
		}
		//笛·龙属性防御UP大
		if (buff == "Whistle Dragon Res Up") {
			return 0xd0;
		}
		//笛·属性攻击力提升
		if (buff == "Whistle Elemental Attack Boost") {
			return 0xd4;
		}
		//笛·全属性异常状态无效
		if (buff == "Whistle Blight Negated") {
			return 0xd8;
		}
		//笛·后仰无效
		if (buff == "Whistle Knockbacks Negated") {
			return 0xe4;
		}
		//笛·全属性防御强化
		if (buff == "Whistle Blight Resistance Up") {
			return 0xec;
		}
		//笛·会心率提升
		if (buff == "Whistle Affinity Up") {
			return 0xf0;
		}
		//笛·全状态异常无效
		if (buff == "Whistle All Ailments Negated") {
			return 0xf4;
		}
		//笛·异常攻击力提升
		if (buff == "Whistle Abnormal Status Atk. Increase") {
			return 0xfc;
		}
		//笛·耐力最大值UP与回复
		if (buff == "Whistle Max Stamina Up / Recovery") {
			return 0x10c;
		}
		//笛·体力最大值UP与回复
		if (buff == "Whistle Extended Health Recovery") {
			return 0x110;
		}
		//笛·速度与回避性能UP
		if (buff == "Whistle Speed Boost / Evade Window Up") {
			return 0x114;
		}
		//笛·属性效果提升
		if (buff == "Whistle Elemental Effectiveness") {
			return 0x118;
		}
		//猫
		//猫·复苏
		if (buff == "Palico Resuscitate") {
			return 0x11c;
		}
		//猫·攻击力UP大
		if (buff == "Palico Attack Up") {
			return 0x124;
		}
		//猫·防御力UP大
		if (buff == "Palico Defense Up") {
			return 0x12c;
		}
		//猫·会心率提升
		if (buff == "Palico Affinity Up") {
			return 0x130;
		}
		//猫·恢复速度UP
		if (buff == "Palico Recovery Up") {
			return 0x134;
		}
		//猫·体力UP
		if (buff == "Palico Health Up") {
			return 0x138;
		}
		//猫·耐力消耗减轻
		if (buff == "Palico Stamina Up") {
			return 0x13c;
		}
		//猫·精灵王加护
		if (buff == "Palico Divine Protection") {
			return 0x144;
		}
		//猫·晕厥无效
		if (buff == "Palico Stun Negated") {
			return 0x14c;
		}
		//猫·麻痹无效
		if (buff == "Palico Thunder Negated") {
			return 0x150;
		}
		//猫·耐震
		if (buff == "Palico Seismic") {
			return 0x154;
		}
		//猫·听觉保护
		if (buff == "Palico Hearing Protection") {
			return 0x158;
		}
		//人debuff
		//火属性异常
		if (buff == "Fire Blight") {
			return 0x5ec;
		}
		//雷属性异常
		if (buff == "Thunder Blight") {
			return 0x5f0;
		}
		//水属性异常
		if (buff == "Water Blight") {
			return 0x5f4;
		}
		//冰属性异常
		if (buff == "Ice Blight") {
			return 0x5f8;
		}
		//龙属性异常
		if (buff == "Dragon Blight") {
			return 0x5fc;
		}
		//撕裂伤害
		if (buff == "Bleed") {
			return 0x600;
		}
		//瘴气伤害
		if (buff == "Effuvial") {
			return 0x608;
		}
		//中毒
		if (buff == "Poison") {
			return 0x5dc;
		}
		//猛毒
		if (buff == "High Poison") {
			return 0x5e0;
		}
		//爆破黏菌
		if (buff == "Blastscourge") {
			return 0x62c;
		}
		//防御下降
		if (buff == "Defense Down") {
			return 0x60c;
		}
		//属性耐性下降
		if (buff == "Whistle Down") {
			return 0x614;
		}
		//禁止使用物品
		if (buff == "Prohibited Articles") {
			return 0x61c;
		}
		//爆破属性异常
		if (buff == "blasting Blight") {
			return 0x620;
		}
		//人buff
		//撕裂恢复
		if (buff == "Bleed Recovery") {
			return 0x604;
		}
		//强走药
		if (buff == "Dash Juice") {
			return 0x690;
		}
		//耐力雷虫
		if (buff == "Wiggle Litch") {
			return 0x694;
		}
		//活力剂
		if (buff == "Recovery Up") {
			return 0x698;
		}
		//怪力种子
		if (buff == "Might Seed") {
			return 0x6A0;
		}
		//忍耐种子
		if (buff == "Adamant Seed") {
			return 0x6B0;
		}
		//鬼人粉尘
		if (buff == "Demon Powder") {
			return 0x6C4;
		}
		//硬化粉尘
		if (buff == "Hardshell Powder") {
			return 0x6C8;
		}
		//攻击力+12
		if (buff == "Attack +12") {
			return 0x6CC;
		}
		//防御力+30
		if (buff == "Defense +30") {
			return 0x6d0;
		}
		//冷饮
		if (buff == "Cool Drink") {
			return 0x6EC;
		}
		//热饮
		if (buff == "Hot Drink") {
			return 0x6F0;
		}
		//温泉：HP回复
		if (buff == "Hot Springs: HP Regen") {
			return 0x6F8;
		}
		//温泉：寒冷耐性
		if (buff == "Hot Springs: Cold Res") {
			return 0x6FC;
		}
		//冰耐草：冰耐性提升
		if (buff == "Thawpuff: Ice Res") {
			return 0x71C;
		}
		//鬼毬果：攻击力up
		if (buff == "Powercone") {
			return 0x718;
		}
		//振奋
		if (buff == "Encouraging") {
			return 0x754;
		}
		//不屈
		if (buff == "Surrender") {
			return 0x764;
		}
		//滑走强化
		if (buff == "Slip By Strengthening") {
			return 0x770;
		}
		//攻击守势
		if (buff == "Attacks On The Defensive") {
			return 0x79C;
		}
		//转祸为福
		if (buff == "Turn Calamity Into Blessing") {
			return 0x7A0;
		}
		//挑战者
		if (buff == "Challenger") {
			return 0x748;
		}
		//怨恨
		if (buff == "Resentment") {
			return 0x74C;
		}
		//猫的休息术
		if (buff == "Cat Rest") {
			return 0x7C8;
		}
		//雪人头
		if (buff == "Snowman Head") {
			return 0x704;
		}
		//雪人头持续时间*
		if (buff == "Snowman Head Duration") {
			return 0x708;
		}
		return 0x0;
	}
}