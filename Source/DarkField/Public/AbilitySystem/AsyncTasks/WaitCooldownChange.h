// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameplayTagContainer.h"
#include "GameplayEffect.h"
#include "WaitCooldownChange.generated.h"

struct FGameplayTag;
class UAbilitySystemComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCooldownChangeSignature, float, TimeRemaining);

/**
 * 
 */
//AsyncTask 这个标记返回Static创建的异步任务的示例对象
UCLASS(BlueprintType,meta=(ExposedAsyncProxy="AsyncTask"))
class DARKFIELD_API UWaitCooldownChange : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FCooldownChangeSignature CooldownStart;

	UPROPERTY(BlueprintAssignable)
	FCooldownChangeSignature CooldownEnd;

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly="true"))
	static UWaitCooldownChange *WaitForCooldownChange(UAbilitySystemComponent*AbilitySystemComponent,const FGameplayTag&InCooldownTag);

	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY()
	FGameplayTag CooldownTag;

	void CooldownTagChanged(const FGameplayTag InCooldownTag,int32 NewCount);

	void OnActiveEffectAdded(UAbilitySystemComponent*TargetASC,const FGameplayEffectSpec&SpecApplied,FActiveGameplayEffectHandle ActiveEffectHandle);
};
