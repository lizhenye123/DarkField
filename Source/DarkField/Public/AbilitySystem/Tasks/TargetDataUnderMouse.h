// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature,const FGameplayAbilityTargetDataHandle&,Data);
/**
 * 
 */
UCLASS()
class DARKFIELD_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,Category="Ability|Tasks",meta=(DisplayName="TargetDataUnderMouse",HidePin="OwningAbility",DefaultToSelf="OwningAbility",BlueprintInternalUseOnly="true"))
	static UTargetDataUnderMouse*CreateTargetDataUnderMouse(UGameplayAbility*OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValidData;

private:
	virtual void Activate() override;
	//客户端给服务器发送当前鼠标的Hit
	void SendMouseCursorData();
	//服务器收到信息,验证返回的Handle
	void OnTargetDataReokucatedCallback(const FGameplayAbilityTargetDataHandle&DataHandle,FGameplayTag ActivationTag);
};
