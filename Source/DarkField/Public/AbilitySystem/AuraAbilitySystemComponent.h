// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags,const FGameplayTagContainer&/*AssetTags*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitiesGiven,UAuraAbilitySystemComponent*);
DECLARE_DELEGATE_OneParam(FForEachAbility,const FGameplayAbilitySpec&);

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

	//能力注册时的广播
	FAbilitiesGiven AbilitiesGivenDelegate;

	//能力注册时,为了防止OverlayWidget先被初始化,调用注册能力广播,只有当这个值为true的时候OverlayWidget那块才会更新
	bool bStartupAbilitiesGiven = false;

	void AbilityInputTagHeld(const FGameplayTag&InputTag);
	void AbilityInputTagReleased(const FGameplayTag&InputTag);

	void ForEachAbility(const FForEachAbility &Delegate);

	//通过FGameplayAbilitySpec获取他的标签
	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec&AbilitySpec);

	//通过FGameplayAbilitySpec获取他的Input标签
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec&AbilitySpec);
protected:
	UFUNCTION(Client,Reliable)
	void ClientEffectApplied(UAbilitySystemComponent*AbilitySystemComponent,const FGameplayEffectSpec&EffectSpec,FActiveGameplayEffectHandle ActiveEffectHandle);

	//可以激活的能力变更时
	virtual void OnRep_ActivateAbilities() override;
};
