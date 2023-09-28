// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class ULevelUpInfo;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32);

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
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo>LevelUpInfo;
	
public:
	AAuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet*GetAttributeSet()const{return AttributeSet; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//经验值变更时
	FOnPlayerStatChanged OnXPChangedDelegate;

	//等级变更时
	FOnPlayerStatChanged OnLevelChangedDelegate;

	FORCEINLINE int32 GetPlayerLevel()const;
	FORCEINLINE int32 GetXP()const {return XP;};

	void AddToXP(int32 InXP);
	void SetXP(int32 InXP);

	void AddToLevel(int32 InLevel);
	void SetLevel(int32 InLevel);
protected:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet>AttributeSet;

private:
	//给角色使的,这个Level是同步的
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_Level)
	int32 Level=1;

	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_XP)
	int32 XP;

private:
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_XP(int32 OldXP);
};
