// Dark Field


#include "AI/BTService/BTService_FindNearestPlayer.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn*OwningPawn = AIOwner->GetPawn();
	
	const FName TargetTag = OwningPawn->ActorHasTag(FName("Player"))?FName("Enemy"):FName("Player");

	TArray<AActor*>ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(OwningPawn,TargetTag,ActorsWithTag);

	float ClosestDistance = TNumericLimits<float>::Max();
	AActor*ClosestActor=nullptr;
	for (AActor*Actor:ActorsWithTag)
	{
		if (IsValid(Actor) && IsValid(OwningPawn))
		{
			const float Distance = OwningPawn->GetDistanceTo(Actor);
			if (Distance<ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestActor = Actor;
			}
		}
	}
	UBTFunctionLibrary::SetBlackboardValueAsFloat(this,DistanceToTargetSelector,ClosestDistance);
	UBTFunctionLibrary::SetBlackboardValueAsObject(this,TargetToFollowSelector,ClosestActor);
}
