// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraProjectileSpell.generated.h"

class AAuraProjectile;

/**
 * 
 */
UCLASS()
class DARKFIELD_API UAuraProjectileSpell : public UAuraGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	//生成抛射类
	UFUNCTION(BlueprintCallable,Category="Projectile")
	void SpawnProjectile(const FVector&ProjectileTargetLocation);
protected:
	//能力激活时发射的类
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<AAuraProjectile>AuraProjectile;

	//伤害的GE
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UGameplayEffect>DamageEffectClass;
	
};
