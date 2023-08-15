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

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth,Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHealth);

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana,Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,Mana);
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana,Category="Vital Attributes")
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

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData&Data,FEffectProperties&Props)const;
};

