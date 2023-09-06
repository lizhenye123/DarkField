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
	//角色信息设置了以后,在角色调的
	void AbilityActorInfoSet();

	//添加GA数组到角色
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	
	//有GE应用到身上时,返回GE的AssetTag,代理
	FEffectAssetTags EffectAssetTags;

protected:
	void EffectApplied(UAbilitySystemComponent*AbilitySystemComponent,const FGameplayEffectSpec&EffectSpec,FActiveGameplayEffectHandle ActiveEffectHandle);
};
