// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

/**
 * 召唤技能
 */
UCLASS()
class DARKFIELD_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:
	//获取生成的敌人位置
	UFUNCTION(BlueprintCallable)
	TArray<FVector>GetSpawnLocation();

	//随机获取生成的敌人类型
	UFUNCTION(BlueprintPure,Category="Summoning")
	TSubclassOf<APawn>GetRandomMinionClass();
public:
	//生成数量
	UPROPERTY(EditDefaultsOnly,Category="Summoning")
	int32 NumMinions=5;

	//生成的敌人类型
	UPROPERTY(EditDefaultsOnly,Category="Summoning")
	TArray<TSubclassOf<APawn>>MinionClasses;

	//生成敌人距离召唤者的最小距离
	UPROPERTY(EditDefaultsOnly,Category="Summoning")
	float MinSpawnDistance = 150.f;

	//生成敌人距离召唤者的最大距离
	UPROPERTY(EditDefaultsOnly,Category="Summoning")
	float MaxSpawnDistance = 400.f;
	
	//生成敌人在召唤者前方的角度
	UPROPERTY(EditDefaultsOnly,Category="Summoning")
	float SpawnSpread = 90.f;
};
