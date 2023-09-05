// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 
 */
UCLASS()
class DARKFIELD_API AAuraPlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet*GetAttributeSet()const{return AttributeSet; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FORCEINLINE int32 GetPlayerLevel()const;
protected:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet>AttributeSet;

private:
	//给角色使的,这个Level是同步的
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_Level)
	int32 Level=1;

private:
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
};
