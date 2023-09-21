// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DARKFIELD_API IEnemyInterface
{
	GENERATED_BODY()
public:
	//高亮Actor
	virtual void HighLightActor()=0;
	//取消高亮
	virtual void UnHighLightActor()=0;

	//设置战斗目标
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void SetCombatTarget(AActor*InCombatTarget);

	//回去攻击目标
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	AActor* GetCombatTarget()const;
	
};
