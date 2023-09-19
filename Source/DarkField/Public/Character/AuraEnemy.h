// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "AI/AuraAIController.h"
#include "Character/AuraCharacterBase.h"
#include "Interface/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;

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
	virtual void Die() override;
	/*End ICombatInterface*/

	//血条改变
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	//受击时,调用
	void HitReactTagChanged(const FGameplayTag CallbackTag,int32 NewCount);
public:
	//受击中？
	UPROPERTY(BlueprintReadOnly,Category="Combat")
	bool bHitReacting = false;

	//受击中？
	UPROPERTY(BlueprintReadOnly,Category="Combat")
	float BaseWalkSpeed = 250.f;

	//受击中？
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Combat")
	float LifeSpan = 5.f;
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo()override;

	virtual void InitializeDefaultAttributes()const override;

	virtual void PossessedBy(AController* NewController) override;
	
protected:
	//给敌人用的,这个Level不同步
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Character Class Defaults")
	int32 Level = 1;

	//AI的角色类型
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Character Class Defaults")
	ECharacterClass CharacterClass=ECharacterClass::Warrior;

	//血条组件
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UWidgetComponent>HealthBar;

	//这个角色要运行的行为树
	UPROPERTY(EditAnywhere,Category="AI")
	TObjectPtr<UBehaviorTree>BehaviorTree;

	//这个角色的AI控制器
	UPROPERTY()
	TObjectPtr<AAuraAIController>AuraAIController;
};
