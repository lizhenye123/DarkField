// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "Interface/CombatInterface.h"
#include "AuraDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class DARKFIELD_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
public:
	//给这个目标添加伤害GE
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor*TargetActor);
protected:
	//伤害的GE
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UGameplayEffect>DamageEffectClass;
	
	//伤害标签对应的伤害曲线
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Damage")
	TMap<FGameplayTag,FScalableFloat> DamageTypes;

	//从蒙太奇数组中获取一个随机的
	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages)const;
};
