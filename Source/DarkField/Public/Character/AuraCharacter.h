// Dark Field

#pragma once

#include "CoreMinimal.h"

#include "Character/AuraCharacterBase.h"
#include "Interface/PlayerInterface.h"
#include "AuraCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class DARKFIELD_API AAuraCharacter : public AAuraCharacterBase,public IPlayerInterface
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	/*ACharacter*/
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	/*End ACharacter*/

	/*IPlayerInterface*/
	virtual void AddToXP_Implementation(int32 InXP) override;
	virtual void LevelUp_Implementation() override;
	virtual int32 GetXP_Implementation()const override;
	virtual int32 FindLevelForXP_Implementation(int32 InXP) const override;
	virtual int32 GetAttributePointReward_Implementation(int32 InLevel) const override;
	virtual int32 GetSpellPointsReward_Implementation(int32 InLevel)const override;
	virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;
	virtual void AddToSpellPoints_Implementation(int32 InSpellPoints) override;
	virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevel) override;
	virtual int32 GetSpellPoints_Implementation() const override;
	virtual int32 GetAttributePoints_Implementation() const override;
	/*End IPlayerInterface*/

	/*ICombatInterface*/
	virtual int32 GetPlayerLevel_Implementation() override;
	/*End ICombatInterface*/

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent>LevelUpNiagaraComponent;
private:
	virtual void InitAbilityActorInfo()override;

	UFUNCTION(NetMulticast,Reliable)
	void MulticastLevelUpParticles()const;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent>TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent>CameraBoom;
};
