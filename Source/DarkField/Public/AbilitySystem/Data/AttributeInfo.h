// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfo.generated.h"

/*
 * 属性表页面的 单个属性的详细信息
 */
USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeName = FText();
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

/**
 * 属性点页面的属性信息
 */
UCLASS()
class DARKFIELD_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	//查找这个Tag的属性
	FAuraAttributeInfo FindAttributeInfoForTag(const FGameplayTag&AttributeTag,bool bLogNotFound) const;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAuraAttributeInfo>AttributeInformation;
};
