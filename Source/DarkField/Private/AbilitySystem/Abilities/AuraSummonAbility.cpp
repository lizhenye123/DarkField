// Dark Field


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocation()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread/NumMinions;

	TArray<FVector> SpawnLocations;
	for (int32 i=0;i<NumMinions;i++)
	{
		const FVector Direction = Forward.RotateAngleAxis(DeltaSpread*i,FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::RandRange(MinSpawnDistance, MaxSpawnDistance);

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult,ChosenSpawnLocation+FVector(0,0,400),ChosenSpawnLocation - FVector(0,0,400),ECC_Visibility);
		if (!HitResult.bBlockingHit)
		{
			ChosenSpawnLocation = HitResult.ImpactPoint;
		}
		
		SpawnLocations.Add(ChosenSpawnLocation);
	}

	return SpawnLocations;
}

TSubclassOf<APawn> UAuraSummonAbility::GetRandomMinionClass()
{
	const int32 Selection = FMath::RandRange(0,MinionClasses.Num()-1);
	return MinionClasses[Selection];
}
