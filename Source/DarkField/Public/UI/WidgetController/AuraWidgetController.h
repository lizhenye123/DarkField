// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class AAuraPlayerController;
class AAuraPlayerState;
class UAbilityInfo;
class UAuraAttributeSet;
class UAuraAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChangedSignature,int32,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityInfoSignature,const FAuraAbilityInfo&,Info);

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_USTRUCT_BODY()
	FWidgetControllerParams(){};
	FWidgetControllerParams(APlayerController*PC,APlayerState*PS,UAbilitySystemComponent*ASC,UAttributeSet*AS)
		:PlayerController(PC),PlayerState(PS),AbilitySystemComponent(ASC),AttributeSet(AS){};
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<APlayerController>PlayerController;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<APlayerState>PlayerState;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UAttributeSet>AttributeSet;
};

/**
 * UI需要拿到的所有参数 都在这
 */
UCLASS()
class DARKFIELD_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams&WCParams);

	//广播在UI中初始化显示
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();

	//绑定Attribute改变时的代理
	virtual void BindCallbacksToDependencies();

	AAuraPlayerController*GetAuraPC();
	AAuraPlayerState*GetAuraPS();
	UAuraAbilitySystemComponent*GetAuraASC();
	UAuraAttributeSet*GetAuraAS();
public:
	
	//通知主控端,技能变跟
	UPROPERTY(BlueprintAssignable,Category="GAS|Message")
	FAbilityInfoSignature AbilityInfoDelegate;
protected:
	//初始化当前拥有的技能在图标栏上
	void BroadcastAbilityInfo();
	
protected:
	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<APlayerController>PlayerController;

	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<APlayerState>PlayerState;

	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<UAttributeSet>AttributeSet;

	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<AAuraPlayerController>AuraPlayerController;

	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<AAuraPlayerState>AuraPlayerState;

	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<UAuraAbilitySystemComponent>AuraAbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly,Category="WidgetController")
	TObjectPtr<UAuraAttributeSet>AuraAttributeSet;

	//角色可以注册使用的技能信息
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Widget Data")
	TObjectPtr<UAbilityInfo> AbilityInfo;
};
