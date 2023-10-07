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
	
	//属性点变更时
	FOnPlayerStatChanged OnAttributePointsChangedDelegate;

	//技能点变更时
	FOnPlayerStatChanged OnSpellPointsChangedDelegate;

	FORCEINLINE int32 GetPlayerLevel()const;
	FORCEINLINE int32 GetXP()const {return XP;};
	FORCEINLINE int32 GetAttributePoints()const{return AttributePoints;};
	FORCEINLINE int32 GetSpellPoints()const {return SpellPoints;};

	void AddToXP(int32 InXP);
	void SetXP(int32 InXP);
	void AddToAttributePoints(int32 InPoints);
	void AddToSpellPoints(int32 InPoints);

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

	//属性点
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_AttributePoints)
	int32 AttributePoints = 0;

	//属性点
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_SpellPoints)
	int32 SpellPoints = 1;

private:
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_XP(int32 OldXP);

	UFUNCTION()
	void OnRep_AttributePoints(int32 OldAttributePoints);

	UFUNCTION()
	void OnRep_SpellPoints(int32 OldSpellPoints);
};
