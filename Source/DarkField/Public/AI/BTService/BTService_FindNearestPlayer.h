// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_FindNearestPlayer.generated.h"

/**
 * 
 */
UCLASS()
class DARKFIELD_API UBTService_FindNearestPlayer : public UBTService_BlueprintBase
{
	GENERATED_BODY()
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	//最近的Actor
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FBlackboardKeySelector TargetToFollowSelector;

	//最近的角色距离
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FBlackboardKeySelector DistanceToTargetSelector;
};
