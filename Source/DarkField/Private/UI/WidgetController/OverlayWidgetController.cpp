// Dark Field


#include "UI\WidgetController\OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/AuraPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet*AuraAttributesSet=CastChecked<UAuraAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(AuraAttributesSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributesSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributesSet->GetMana());
	OnMaxManaChange.Broadcast(AuraAttributesSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	AAuraPlayerState*AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AuraPlayerState->OnXPChangedDelegate.AddUObject(this,&UOverlayWidgetController::OnXPChanged);
	
	const UAuraAttributeSet*AuraAttributeSet=CastChecked<UAuraAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChange.Broadcast(Data.NewValue);
		}
	);

	if(UAuraAbilitySystemComponent*AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (AuraASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(AuraASC);
		}else
		{
			AuraASC->AbilitiesGivenDelegate.AddUObject(this,&UOverlayWidgetController::OnInitializeStartupAbilities);
		}
		
		AuraASC->EffectAssetTags.AddLambda(
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
	const UAuraAttributeSet*AuraAttributesSet=CastChecked<UAuraAttributeSet>(AttributeSet);
	return AuraAttributesSet->GetMaxHealth();
}

float UOverlayWidgetController::GetMaxManaValue()
{
	const UAuraAttributeSet*AuraAttributesSet=CastChecked<UAuraAttributeSet>(AttributeSet);
	return AuraAttributesSet->GetMaxMana();
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UAuraAbilitySystemComponent*AuraAbilitySystemComponent)
{
	if(!AuraAbilitySystemComponent->bStartupAbilitiesGiven) return;

	//绑定好初始化技能时的代理
	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this,AuraAbilitySystemComponent](const FGameplayAbilitySpec& AbilitySpec)
	{
		FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AuraAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = AuraAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});

	//这的代理是给ASC里调的,ASC那边会吧注册过的带Ability标签的给返到这代理里去
	AuraAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP) const
{
	const AAuraPlayerState*AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	const ULevelUpInfo*LevelUpInfo = AuraPlayerState->LevelUpInfo;
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

		//上一级到当前等级需要的经验值
		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		//NewXP是角色所有的经验 - 上一个等级的经验要求 
		const int32 XRForThisLevel = NewXP - PreviousLevelUpRequirement;

		//当前拥有的经验 / 当前等级的经验值上限
		const float XPBarPercent = static_cast<float>(XRForThisLevel) / static_cast<float>(DeltaLevelRequirement);
		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}

	
}





