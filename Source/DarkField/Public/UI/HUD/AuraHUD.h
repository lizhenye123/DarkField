// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;

UCLASS()
class DARKFIELD_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:

	//玩家开始游戏后的主页面
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;
	
protected:

public:
	//获取Overlay的控制器
	UOverlayWidgetController*GetOverlayWidgetController(const FWidgetControllerParams&WCParams);

	//初始化Overlay控制器参数
	void InitOverlay(APlayerController*PC,APlayerState*PS,UAbilitySystemComponent*ASC,UAttributeSet*AS);
	
private:
	//Overlay的UI页面,玩家开始游戏后的主页面类
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget>OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	//Widget控制器的类
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
