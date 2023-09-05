// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "AttributeWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class DARKFIELD_API UAttributeWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()
public:
	//广播在UI中初始化显示
	virtual void BroadcastInitialValues()override;

	//绑定Attribute改变时的代理
	virtual void BindCallbacksToDependencies()override;
};
