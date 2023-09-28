// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraLevelUpInfo
{
	GENERATED_BODY()

	//升级要求
	UPROPERTY(EditDefaultsOnly)
	int32 LevelUpRequirement=0;

	//升级获得的属性点
	UPROPERTY(EditDefaultsOnly)
	int32 AttributePointAward=1;

	//升级获得的技能点
	UPROPERTY(EditDefaultsOnly)
	int32 SpellPointAward=1;
};

/**
 * 角色的升级信息
 */
UCLASS()
class DARKFIELD_API ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAuraLevelUpInfo> LevelUpInforamtion;

	int32 FindLevelForXP(int32 XP)const;
};
