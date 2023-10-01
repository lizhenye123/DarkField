// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;
struct FOnAttributeChangeData;
class UAuraAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FUIWidgetRow:public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FText Message=FText();

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget>MessageWidget;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UTexture2D*Image=nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature,FUIWidgetRow,Row);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityInfoSignature,const FAuraAbilityInfo&,Info);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChangedSignature,int32,NewValue);

/**
 * 
 */
UCLASS(BlueprintType,Blueprintable)
class DARKFIELD_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	
	//广播在UI中初始化显示
	virtual void BroadcastInitialValues()override;
	
	//绑定Attribute改变时的代理
	virtual void BindCallbacksToDependencies()override;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable,Category="GAS|Attribute")
	FOnAttributeChangedSignature OnMaxManaChange;

	//通知当前客户端捡到东西时的信息
	UPROPERTY(BlueprintAssignable,Category="GAS|Message")
	FMessageWidgetRowSignature MessageWidgetRowSignature;

	//通知主控端,技能变跟
	UPROPERTY(BlueprintAssignable,Category="GAS|Message")
	FAbilityInfoSignature AbilityInfoDelegate;

	//经验值百分比变更
	UPROPERTY(BlueprintAssignable,Category="GAS|XP")
	FOnAttributeChangedSignature OnXPPercentChangedDelegate;

	//等级变化时的代理
	UPROPERTY(BlueprintAssignable,Category="GAS|XP")
	FOnPlayerStatChangedSignature OnPlayerLevelChangedDelegate;

	/*这个两个函数是因为代理更新时,两个最大值一直是0 所以写了一个直接获取的函数*/
	UFUNCTION(BlueprintPure)
	float GetMaxHealthValue();

	UFUNCTION(BlueprintPure)
	float GetMaxManaValue();

protected:

	//拾取物品时的弹窗信息
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Widget Data")
	TObjectPtr<UDataTable>MessageWidgetDataTable;

	//角色可以注册使用的技能信息
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Widget Data")
	TObjectPtr<UAbilityInfo> AbilityInfo;

	void BindPickUp(const FGameplayTagContainer&AssetTags);

	//初始化当前拥有的技能在图标栏上
	void OnInitializeStartupAbilities(UAuraAbilitySystemComponent*AuraAbilitySystemComponent);

	template<typename T>
	T* GetDataTableRowByTag(UDataTable*DataTable,const FGameplayTag&Tag);

	//经验值改变时
	void OnXPChanged(int32 NewXP)const;
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
}
