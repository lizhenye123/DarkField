// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
/*
 * 包含GameplayTags的单例
 */
struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags&Get(){return GameplayTags;};
	static void InitializeNativeGameplayTags();

	/*
	 * 属性标签,主要属性
	 */
	//力量
	FGameplayTag Attributes_Primary_Strength;
	//智力
	FGameplayTag Attributes_Primary_Intelligence;
	//恢复
	FGameplayTag Attributes_Primary_Resilience;
	//精力
	FGameplayTag Attributes_Primary_Vigor;
	

	/*
	 * 属性标签,次级属性
	 */
	//护甲,
	FGameplayTag Attributes_Secondary_Armor;
	//护甲穿透
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	//格挡几率
	FGameplayTag Attributes_Secondary_BlockChance;
	//暴击概率
	FGameplayTag Attributes_Secondary_CriticalHitChanage;
	//暴击伤害
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	//抗暴击性
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	//生命值恢复力
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	//蓝量恢复量
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	//最大生命值
	FGameplayTag Attributes_Secondary_MaxHealth;
	//最大蓝条
	FGameplayTag Attributes_Secondary_MaxMana;

	//伤害抵抗
	//火
	FGameplayTag Attributes_Resistance_Fire;
	//闪电
	FGameplayTag Attributes_Resistance_Lightning;
	//奥术
	FGameplayTag Attributes_Resistance_Arcane;
	//物理
	FGameplayTag Attributes_Resistance_Physical;

	//输入的Tag
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	//伤害Tag
	FGameplayTag Damage;
	//火焰
	FGameplayTag Damage_Fire;
	//闪电
	FGameplayTag Damage_Lightning;
	//奥术
	FGameplayTag Damage_Arcane;
	//物理
	FGameplayTag Damage_Physical;

	//技能
	//攻击
	FGameplayTag Abilities_Attack;
	//召唤
	FGameplayTag Abilities_Summon;
	//火球术
	FGameplayTag Abilities_Fire_FireBolt;

	//冷却
	//火球术冷却
	FGameplayTag Cooldown_Fire_FireBolt;

	//Socket
	//武器
	FGameplayTag CombatSocket_Weapon;
	//右手
	FGameplayTag CombatSocket_RightHand;
	//左手
	FGameplayTag CombatSocket_LeftHand;
	//尾巴
	FGameplayTag CombatSocket_Tail;

	//Montage
	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

	
	//所有的伤害标签和抵抗标签
	TMap<FGameplayTag,FGameplayTag> DamageTypesToResistances;

	//受击的Tag
	FGameplayTag Effects_HitReact;
private:
	static FAuraGameplayTags GameplayTags;
};