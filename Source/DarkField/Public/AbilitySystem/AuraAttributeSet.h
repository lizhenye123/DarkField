// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent*SourceASC=nullptr;

	UPROPERTY()
	AActor*SourceAvatarActor=nullptr;

	UPROPERTY()
	AController*SourceController=nullptr;

	UPROPERTY()
	ACharacter*SourceCharacter=nullptr;

	UPROPERTY()
	UAbilitySystemComponent*TargetASC=nullptr;

	UPROPERTY()
	AActor*TargetAvatarActor=nullptr;

	UPROPERTY()
	AController*TargetController=nullptr;

	UPROPERTY()
	ACharacter*TargetCharacter=nullptr;
};

template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T,FDefaultDelegateUserPolicy>::FFuncPtr;
/**
 * 
 */
UCLASS()
class DARKFIELD_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)override;
public:

	//拿对应的Tag,可以获取对应的Attribute
	TMap<FGameplayTag,TStaticFuncPtr<FGameplayAttribute()>>TagsToAttributes;
	/*
	 * 主要属性
	 */
	//力量
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Strength,Category="Primary Attribute")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Strength);

	//智力
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Intelligence,Category="Primary Attribute")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Intelligence);

	//恢复
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Resilience,Category="Primary Attribute")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Resilience);

	//精力
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Vigor,Category="Primary Attribute")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Vigor);
	
	/*
	 * 重要的属性
	 */
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Health,Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Health);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana,Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Mana);
	
	/*
	 *次要属性
	 */
	
	//护甲 减少伤害,提高格挡概率
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Armor,Category="Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Armor);

	//护甲穿透 忽略敌人护甲的百分比,添加暴击几率
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ArmorPenetration,Category="Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ArmorPenetration);

	//格挡几率 有几率将伤害减半
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_BlockChance,Category="Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,BlockChance);

	//暴击概率 有几率使伤害加倍
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_CriticalHitChanage,Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitChanage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitChanage);

	//暴击伤害
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_CriticalHitDamage,Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitDamage);

	//抗暴击性 降低攻击敌人的暴击几率
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_CriticalHitResistance,Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,CriticalHitResistance);

	//生命值恢复力
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_HealthRegeneration,Category="Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,HealthRegeneration);

	//蓝量恢复量
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ManaRegeneration,Category="Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,ManaRegeneration);

	//最大生命值
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth,Category="Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth);

	//最大蓝条
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana,Category="Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxMana);
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData&OldHealth)const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData&OldMaxHealth)const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData&OldMana)const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData&OldMaxMana)const;

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData&OldStrength)const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData&OldIntelligence)const;
	
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData&OldResilience)const;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData&OldVigor)const;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData&OldArmor)const;
	
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData&OldArmorPenetration)const;

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData&OldBlockChance)const;

	UFUNCTION()
	void OnRep_CriticalHitChanage(const FGameplayAttributeData&OldCriticalHitChanage)const;

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData&OldCriticalHitDamage)const;

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData&OldCriticalHitResistance)const;

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData&OldHealthRegeneration)const;

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData&OldManaRegeneration)const;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData&Data,FEffectProperties&Props)const;
};


