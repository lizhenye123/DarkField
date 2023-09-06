// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributeWidgetController.generated.h"

struct FGameplayAttribute;
struct FGameplayTag;
struct FAuraAttributeInfo;
class UAttributeInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&,Info);

/**
 * 玩家属性页 需要拿到的所有属性参数
 */
UCLASS(BlueprintType,Blueprintable)
class DARKFIELD_API UAttributeWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	//广播在UI中初始化显示
	virtual void BroadcastInitialValues()override;

	//绑定Attribute改变时的代理
	virtual void BindCallbacksToDependencies()override;

	//属性值改变时的代理
	UPROPERTY(BlueprintAssignable,Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UAttributeInfo>AttributeInfo;

private:
	void BroadcastAttributeInfo(const FGameplayTag&AttributeTag,const FGameplayAttribute&Attribute)const;
};
