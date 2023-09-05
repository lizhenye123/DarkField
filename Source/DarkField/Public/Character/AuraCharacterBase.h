// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/CombatInterface.h"
#include "AuraCharacterBase.generated.h"


class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class DARKFIELD_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()
	
public:
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet*GetAttributeSet()const{return AttributeSet; }
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo();
	
	//初始属性
	void InitializeDefaultAttributes()const;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass,float Level)const;
protected:
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	//初始化主要Attribute的GE
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect>DefaultPrimaryAttributes;

	//初始化次要Attribute的GE
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect>DefaultSecondaryAttributes;

	//初始化重要Attribute的GE
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Attributes")
	TSubclassOf<UGameplayEffect>DefaultVitalAttributes;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet>AttributeSet;
};
