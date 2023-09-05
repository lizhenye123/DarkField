// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class IEnemyInterface;

struct FInputActionValue;
/**
 * 
 */
UCLASS()
class DARKFIELD_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual  void PlayerTick(float DeltaTime) override;
private:
	//移动
	void Move(const FInputActionValue&InputActionValue);
	
	//鼠标检测扫到的敌人
	void CursorTrace();
protected:
	
private:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	//上一个鼠标扫到的Actor
	IEnemyInterface*LastActor;

	//当前鼠标扫到的Actor
	IEnemyInterface*ThisActor;
};
