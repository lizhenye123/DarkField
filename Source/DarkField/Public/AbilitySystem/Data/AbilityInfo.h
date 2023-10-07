// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityInfo.generated.h"

class UGameplayAbility;

USTRUCT(BlueprintType)
struct FAuraAbilityInfo
{
	GENERATED_BODY()

	//GA的Tag
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AbilityTag = FGameplayTag();

	//Input的Tag
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag InputTag = FGameplayTag();

	//冷却Tag
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag CooldownTag = FGameplayTag();

	//技能是否解锁的Tag
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag StatusTag = FGameplayTag();

	//技能的图标
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<const UTexture2D>Icon = nullptr;

	//技能的背景元素
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<const UMaterialInterface> BackgroundMaterial=nullptr;
	
	//技能的解锁等级
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 LevelRequirement;

	//技能类
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> Ability;
};

/**
 * 角色的技能栏信息
 */
UCLASS()
class DARKFIELD_API UAbilityInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	//角色可以注册使用的所有技能信息
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="AbilityInformation")
	TArray<FAuraAbilityInfo> AbilityInformation;

	//查找对应的技能信息
	FAuraAbilityInfo FindAbilityInfoForTag(const FGameplayTag& AbilityTag,bool bLogFound = false);
};
