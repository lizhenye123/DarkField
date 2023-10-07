// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags,const FGameplayTagContainer&/*AssetTags*/);
DECLARE_MULTICAST_DELEGATE(FAbilitiesGiven);
DECLARE_DELEGATE_OneParam(FForEachAbility,const FGameplayAbilitySpec&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FAbilityStatusChanged,const FGameplayTag&/*AbilityTag*/,const FGameplayTag&/*StatusTag*/)

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
	
	//添加被动GA数组到角色
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities);
	
	//有GE应用到身上时,返回GE的AssetTag,代理
	FEffectAssetTags EffectAssetTags;

	//能力注册时的广播
	FAbilitiesGiven AbilitiesGivenDelegate;

	//技能解锁状态改变时
	FAbilityStatusChanged AbilityStatusChanged;

	//能力注册时,为了防止OverlayWidget先被初始化,调用注册能力广播,只有当这个值为true的时候OverlayWidget那块才会更新
	bool bStartupAbilitiesGiven = false;

	void AbilityInputTagHeld(const FGameplayTag&InputTag);
	void AbilityInputTagReleased(const FGameplayTag&InputTag);

	//广播应用的代理
	void ForEachAbility(const FForEachAbility &Delegate);

	//升级属性
	void UpgradeAttribute(const FGameplayTag&AttributeTag);

	//服务器 属性升级
	UFUNCTION(Server,Reliable)
	void ServerUpgradeAttribute(const FGameplayTag&AttributeTag);

	//升级的时候更新能力列表中的解锁状态
	void UpdateAbilityStatuses(int32 Level);
	
	//通过FGameplayAbilitySpec获取他的标签
	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec&AbilitySpec);

	//通过FGameplayAbilitySpec获取他的Input标签
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec&AbilitySpec);

	//通过FGameplayAbilitySpec获取他的Status标签
	static FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec&AbilitySpec);

	//通过Tag,只要这个GA带有这个Tag他就返回,查找能力
	FGameplayAbilitySpec*GetSpecFromAbilitySpec(const FGameplayTag&AbilityTag);

protected:
	UFUNCTION(Client,Reliable)
	void ClientEffectApplied(UAbilitySystemComponent*AbilitySystemComponent,const FGameplayEffectSpec&EffectSpec,FActiveGameplayEffectHandle ActiveEffectHandle);

	//通知客户端技能状态的变化
	UFUNCTION(Client,Reliable)
	void ClientUpdateAbilityStatus(const FGameplayTag&AbilityTag,const FGameplayTag&StatusTag);
	
	//可以激活的能力变更时
	virtual void OnRep_ActivateAbilities() override;
};
