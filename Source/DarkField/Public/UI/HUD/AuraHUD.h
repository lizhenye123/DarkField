// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAttributeWidgetController;
class UAuraUserWidget;

UCLASS()
class DARKFIELD_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:
	
protected:

public:
	//获取Overlay的控制器
	UOverlayWidgetController*GetOverlayWidgetController(const FWidgetControllerParams&WCParams);

	//获取AttributeWidget的控制器
	UAttributeWidgetController*GetAttributeWidgetController(const FWidgetControllerParams&WCParams);

	//初始化Overlay控制器参数
	void InitOverlay(APlayerController*PC,APlayerState*PS,UAbilitySystemComponent*ASC,UAttributeSet*AS);
	
private:
	//玩家开始游戏后的主页面
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	
	//Overlay的UI页面,玩家开始游戏后的主页面类
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget>OverlayWidgetClass;
	
	//Widget控制器的类
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	//Widget控制器的实例
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	//Widget属性控制器的类
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeWidgetController> AttributeMenuWidgetControllerClass;
	
	//属性控制器的实例,用于技能点UI
	UPROPERTY()
	TObjectPtr<UAttributeWidgetController> AttributeMenuWidgetController;
};
