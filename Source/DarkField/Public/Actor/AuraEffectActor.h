// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class USphereComponent;

//应用GE的策略
UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	//重叠时添加
	ApplyOnOverlap,
	//重叠结束后添加
	ApplyOnEndOverlap,
	//不添加
	DoNotApply
};

//删除GE的策略
UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	//重叠结束后删除
	RemoveOnEndOverlap,
	//不删除
	DoNotRemove
};
/*
 * 和角色重叠后要给角色添加某一些GE
 */
UCLASS()
class DARKFIELD_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

protected:	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effect")
	EEffectApplicationPolicy InstanctApplicationPolicy=EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effect")
	TSubclassOf<UGameplayEffect>DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effect")
	EEffectApplicationPolicy DurationApplicationPolicy=EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effect")
	TSubclassOf<UGameplayEffect>InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effect")
	EEffectApplicationPolicy InfiniteApplicationPolicy=EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effect")
	EEffectRemovalPolicy InfiniteRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effect")
	float ActorLevel=1.f;

	//GE应用后销毁吗
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effect")
	bool bDestroyOnEffectApplication = false;

	//GE可以给敌人施加吗
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied Effect")
	bool bApplyEffectsToEnemies = false;
	
	TMap<FActiveGameplayEffectHandle,UAbilitySystemComponent*>ActiveEffectHandles;
public:	
	AAuraEffectActor();
protected:
	virtual void BeginPlay() override;

	//应用GE
	UFUNCTION(BlueprintCallable,Category="Applied Effect")
	void ApplyEffectToTarget(AActor*TargetActor,TSubclassOf<UGameplayEffect>GameplayEffectClass);

	//重叠时
	UFUNCTION(BlueprintCallable,Category="Applied Effect")
	void OnOverlap(AActor*TargetActor);

	//离开时
	UFUNCTION(BlueprintCallable,Category="Applied Effect")
	void OnEndOverlap(AActor*TargetActor);

	
};
