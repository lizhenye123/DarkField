// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class DARKFIELD_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
protected:
	//伤害的GE
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UGameplayEffect>DamageEffectClass;
	
	//伤害标签对应的伤害曲线
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Damage")
	TMap<FGameplayTag,FScalableFloat> DamageTypes;
};