// Dark Field


#include "UI/HUD/AuraHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
	UUserWidget*UserWidget = CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	UserWidget->AddToViewport();
	
}
