// Dark Field


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/WidgetController/AuraWidgetController.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController*PC= UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if (AAuraHUD*AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState*PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent*ASC= PS->GetAbilitySystemComponent();
			UAttributeSet*AS = PS->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
			return AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	
	return nullptr;
}

UAttributeWidgetController* UAuraAbilitySystemLibrary::GetAttributeWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController*PC= UGameplayStatics::GetPlayerController(WorldContextObject,0))
	{
		if (AAuraHUD*AuraHUD = Cast<AAuraHUD>(PC->GetHUD()))
		{
			AAuraPlayerState*PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent*ASC= PS->GetAbilitySystemComponent();
			UAttributeSet*AS = PS->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PC,PS,ASC,AS);
			return AuraHUD->GetAttributeWidgetController(WidgetControllerParams);
		}
	}
	
	return nullptr;
}

void UAuraAbilitySystemLibrary::InitialzeDefaultAttributes(const UObject*WorldContextObject,ECharacterClass CharacterClass, float Level,UAbilitySystemComponent*ASC)
{
	AAuraGameModeBase*AuraGameModeBase=Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (AuraGameModeBase==nullptr) return;
	UCharacterClassInfo*CharacterClassInfo = AuraGameModeBase->CharacterClassInfo;
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	AActor*AvatarActor = ASC->GetAvatarActor();
	
	FGameplayEffectContextHandle AttributeContextHandle= ASC->MakeEffectContext();
	AttributeContextHandle.AddSourceObject(AvatarActor);
	
	const FGameplayEffectSpecHandle PrimaryAttributeSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes,Level,AttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributeSpecHandle.Data.Get());

	const FGameplayEffectSpecHandle SecondaryAttributSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes,Level,AttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributSpecHandle.Data.Get());

	const FGameplayEffectSpecHandle VitalAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes,Level,AttributeContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributeSpecHandle.Data.Get());
}
