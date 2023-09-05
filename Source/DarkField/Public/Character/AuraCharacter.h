// Dark Field

#pragma once

#include "CoreMinimal.h"

#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;
/**
 * 
 */
UCLASS()
class DARKFIELD_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	/*ACharacter*/
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	/*End ACharacter*/

	/*ICombatInterface*/
	virtual int32 GetPlayerLevel() override;
	/*End ICombatInterface*/
private:
	virtual void InitAbilityActorInfo()override;
};
