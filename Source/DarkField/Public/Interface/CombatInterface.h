// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "CombatInterface.generated.h"

//蒙太奇标记
USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()

	//蒙太奇
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UAnimMontage*Montage=nullptr;
	//蒙太奇对应的标签
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag MontageTag;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI,BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DARKFIELD_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 GetPlayerLevel();

	//攻击的插槽位置
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	FVector GetCombatSocketLocation(const FGameplayTag&MontageTag);

	//更新当前瞄准的目标位置
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateFacingTarget(const FVector&Target);

	//受击动画
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	UAnimMontage*GetHitReactMontage();

	//死亡
	virtual void Die()=0;

	//是否死亡
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	bool IsDead()const;

	//获取化身
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	AActor*GetAvatar();

	//获取攻击蒙太奇
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	TArray<FTaggedMontage>GetAttackMontages();
};
