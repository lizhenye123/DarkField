// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class DARKFIELD_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	//按键的那个Tag，按键按下时会找这个按键类型的Tag来激活能力
	UPROPERTY(EditDefaultsOnly,Category="Input")
	FGameplayTag StartupInputTag;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Damage")
	FScalableFloat Damage;
};
