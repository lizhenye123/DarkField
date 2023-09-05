// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interface/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class DARKFIELD_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	
	/*Begin IEnemyInterface*/
	//高亮Actor
	virtual void HighLightActor()override;
	//取消高亮
	virtual void UnHighLightActor()override;
	/*End IEnemyInterface*/

	/*ICombatInterface*/
	virtual int32 GetPlayerLevel() override;
	/*End ICombatInterface*/
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo()override;
	
protected:
	//给敌人用的,这个Level不同步
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Character Class Defaults")
	int32 Level = 1;
};
