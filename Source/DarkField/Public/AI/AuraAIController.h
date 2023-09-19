// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AuraAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class DARKFIELD_API AAuraAIController : public AAIController
{
	GENERATED_BODY()
public:
	AAuraAIController();

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
