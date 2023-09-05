// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags,const FGameplayTagContainer&/*AssetTags*/);

/**
 * 
 */
UCLASS()
class DARKFIELD_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();

	//有GE应用到身上时,返回GE的AssetTag,代理
	FEffectAssetTags EffectAssetTags;
protected:
	void EffectApplied(UAbilitySystemComponent*AbilitySystemComponent,const FGameplayEffectSpec&EffectSpec,FActiveGameplayEffectHandle ActiveEffectHandle);
};
