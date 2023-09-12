// Dark Field


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;
void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	//主要属性
	GameplayTags.Attributes_Primary_Strength=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"),FString("Increases Physical damage"));
	GameplayTags.Attributes_Primary_Intelligence=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"),FString("Increases magical damage"));
	GameplayTags.Attributes_Primary_Resilience=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"),FString("Increases Armor and Armor Penetration"));
	GameplayTags.Attributes_Primary_Vigor=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"),FString("Increases Health"));

	//次要属性
	GameplayTags.Attributes_Secondary_Armor=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"),FString("Reduces damage taken, imprvoes Block Change"));
	GameplayTags.Attributes_Secondary_ArmorPenetration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"),FString("Armor penetration Ignore the percentage of enemy armor, add critical strike chance"));
	GameplayTags.Attributes_Secondary_BlockChance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"),FString("Block chance to have a chance to halve the damage"));
	GameplayTags.Attributes_Secondary_CriticalHitChanage=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChanage"),FString("Crit probability has a chance to double damage"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"),FString("Critical strike damage"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"),FString("Growing seasonal Reduce the critical strike chance to attack the enemy"));
	GameplayTags.Attributes_Secondary_HealthRegeneration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"),FString("Health Resilience"));
	GameplayTags.Attributes_Secondary_ManaRegeneration=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"),FString("Blue restore quantity"));
	GameplayTags.Attributes_Secondary_MaxHealth=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"),FString("Maximum health"));
	GameplayTags.Attributes_Secondary_MaxMana=UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"),FString("Maximum mana"));

	//按键输入
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"),FString("Input Tag for Left Mouse Button"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"),FString("Input Tag for Right Mouse Button"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"),FString("Input Tag for 1 Key"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"),FString("Input Tag for 2 Key"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"),FString("Input Tag for 3 Key"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"),FString("Input Tag for 4 Key"));

	//伤害Tag
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"),FString("Damage"));
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"),FString("Tag granted when Hit Reacting"));
}
