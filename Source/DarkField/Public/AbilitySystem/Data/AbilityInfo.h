// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityInfo.generated.h"

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

	//GA的Tag
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag CooldownTag = FGameplayTag();

	//技能的图标
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<const UTexture2D>Icon = nullptr;

	//技能的背景元素
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<const UMaterialInterface> BackgroundMaterial=nullptr;
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
