// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Character/AuraCharacter.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class UAuraAbilitySystemComponent;
struct FGameplayTag;
class UAuraInputConfig;
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
class USplineComponent;
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
	//鼠标检测扫到的敌人
	void CursorTrace();

	//点击目标后自动行走的目标点
	void AutoRun();

	UAuraAbilitySystemComponent*GetASC();
	
//Input	
	//移动输入的绑定
	void Move(const FInputActionValue&InputActionValue);
	
	//Config中的所有按键,都绑定的这些执行,主要通过Tag来判断他按下了什么
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	//Shift键
	void ShiftPressed(){bShiftKeyDown=true;};
	void ShiftReleased(){bShiftKeyDown=false;};

protected:
	
private:
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> ShiftAction;

	//输入的Action和Tag
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UAuraInputConfig>InputConfig;

	//Shift键按下了吗
	bool bShiftKeyDown=false;

//鼠标扫到描边	
	//上一个鼠标扫到的Actor
	IEnemyInterface*LastActor;

	//当前鼠标扫到的Actor
	IEnemyInterface*ThisActor;

	//当前鼠标扫到的Hit
	FHitResult CursorHit;
	
	//角色的ASC
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

//行走	
	//鼠标点击的目的地
	FVector CachedDestination = FVector::ZeroVector;
	
	//鼠标按下的时间
	float FollowTime=0;
	
	//认为是短按的时间
	float ShortPressThreshold=0.5;
	
	//自动走到目标点吗
	bool bAutoRunning=false;
	
	//鼠标现在点到敌人了吗
	bool bTargeting;
	
	//到达目标点允许的半径范围
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius=50.f;
	
	//自动行走时的样条线,人物跟着这个样条线走
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent>Spline;

	
};


