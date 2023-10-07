// Dark Field


#include "UI\WidgetController\OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/AuraPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChanged.Broadcast(GetAuraAS()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetAuraAS()->GetMaxHealth());
	OnManaChanged.Broadcast(GetAuraAS()->GetMana());
	OnMaxManaChange.Broadcast(GetAuraAS()->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	GetAuraPS()->OnXPChangedDelegate.AddUObject(this,&UOverlayWidgetController::OnXPChanged);
	GetAuraPS()->OnLevelChangedDelegate.AddLambda(
		[&](int32 NewLevel)
	{
			OnPlayerLevelChangedDelegate.Broadcast(NewLevel);
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChange.Broadcast(Data.NewValue);
		}
	);

	if(GetAuraASC())
	{
		if (GetAuraASC()->bStartupAbilitiesGiven)
		{
			BroadcastAbilityInfo();
		}else
		{
			GetAuraASC()->AbilitiesGivenDelegate.AddUObject(this,&UOverlayWidgetController::BroadcastAbilityInfo);
		}
		
		GetAuraASC()->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer&AssetTags)
		{
			for (const FGameplayTag&Tag:AssetTags)
			{
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag("Message");
				if (Tag.MatchesTag(MessageTag))
				{
					FUIWidgetRow*Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,Tag);
					MessageWidgetRowSignature.Broadcast(*Row);
				}
			}
		}
	);
	}
}

float UOverlayWidgetController::GetMaxHealthValue()
{
	return GetAuraAS()->GetMaxHealth();
}

float UOverlayWidgetController::GetMaxManaValue()
{
	return GetAuraAS()->GetMaxMana();
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP) 
{
	const ULevelUpInfo*LevelUpInfo = GetAuraPS()->LevelUpInfo;
	checkf(LevelUpInfo,TEXT("Unabled to find LevelUpInfo. Please fill out AuraPlayerState Blueprint"));

	//现在的等级
	const int32 Level =LevelUpInfo->FindLevelForXP(NewXP);
	//最大等级
	const int32 MaxLevel = LevelUpInfo->LevelUpInforamtion.Num();

	if (Level<=MaxLevel && Level>0)
	{
		//当前等级的经验要求
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInforamtion[Level].LevelUpRequirement;
		//上一个等级的经验要求
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInforamtion[Level-1].LevelUpRequirement;

		//上一级到当前等级需要的经验值之间的差值
		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		//NewXP是角色所有的经验 - 上一个等级的经验要求 
		const int32 XRForThisLevel = NewXP - PreviousLevelUpRequirement;

		//当前拥有的经验 / 当前等级的经验值上限
		const float XPBarPercent = static_cast<float>(XRForThisLevel) / static_cast<float>(DeltaLevelRequirement);
		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}
}





