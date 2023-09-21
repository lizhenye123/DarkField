// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/CombatInterface.h"
#include "AuraCharacterBase.generated.h"


class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(Abstract)
class DARKFIELD_API AAuraCharacterBase : public ACharacter,public IAbilitySystemInterface,public ICombatInterface
{
	GENERATED_BODY()
public:
	//角色的所有攻击蒙太奇
	UPROPERTY(EditAnywhere,Category="Combat")
	TArray<FTaggedMontage> AttackMonatges;
	
public:
	AAuraCharacterBase();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UAttributeSet*GetAttributeSet()const{return AttributeSet; }

	//ICombatInterface Begin
	//获取子弹发射的位置
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag&MontageTag)override;
	
	//受击动画
	virtual UAnimMontage*GetHitReactMontage_Implementation()override;
	
	//死亡
	virtual void Die() override;
	
	//是否死亡
	virtual bool IsDead_Implementation() const override;
	
	//获取化身
	virtual AActor* GetAvatar_Implementation() override;

	//获取所有攻击蒙太奇
	virtual  TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	//ICombatInterface End
	
	//死亡多播
	UFUNCTION(NetMulticast,Reliable)
	virtual void MulticastHandleDeath();
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo();
	
	//初始属性
	virtual void InitializeDefaultAttributes()const;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass,float Level)const;

	//给角色添加技能
	void AddCharacterAbilities();

	//溶解
	void Dissolve();

	//溶解 在蓝图中使用的Timeline
	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic*DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic*DynamicMaterialInstance);

protected:
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	//武器发射物体的Socket
	UPROPERTY(EditAnywhere,Category="Combat")
	FName WeaponTipSocketName;

	//左手插槽
	UPROPERTY(EditAnywhere,Category="Combat")
	FName LeftHandSocketName;

	//右手插槽
	UPROPERTY(EditAnywhere,Category="Combat")
	FName RightHandSocketName;

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

	//角色死亡时的溶解材质
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Dissolve")
	TObjectPtr<UMaterialInstance>DissolveMaterialInstance;

	//武器的溶解材质
	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Dissolve")
	TObjectPtr<UMaterialInstance>WeaponDissolveMaterialInstance;

	//死亡？
	bool bDead=false;
private:
	//出生时要携带的能力
	UPROPERTY(EditAnywhere,Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	//受击动画
	UPROPERTY(EditAnywhere,Category="Combat")
	TObjectPtr<UAnimMontage>HitReactMontage;
};
