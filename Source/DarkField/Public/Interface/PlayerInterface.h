// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DARKFIELD_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//添加XP
	UFUNCTION(BlueprintNativeEvent)
	void AddToXP(int32 InXP);

	//获取XP
	UFUNCTION(BlueprintNativeEvent)
	int32 GetXP()const;

	//获取角色此次升级时要奖励的属性点数量
	UFUNCTION(BlueprintNativeEvent)
	int32 GetAttributePointReward(int32 InLevel)const;

	//获取角色此次升级时要奖励的技能点数量
	UFUNCTION(BlueprintNativeEvent)
	int32 GetSpellPointsReward(int32 InLevel)const;
	
	//角色升级
	UFUNCTION(BlueprintNativeEvent)
	void LevelUp();

	//通过经验插值等级
	UFUNCTION(BlueprintNativeEvent)
	int32 FindLevelForXP(int32 InXP)const;

	//添加玩家等级
	UFUNCTION(BlueprintNativeEvent)
	void AddToPlayerLevel(int32 InPlayerLevel);

	//添加属性点
	UFUNCTION(BlueprintNativeEvent)
	void AddToAttributePoints(int32 InAttributePoints);

	//添加技能点
	UFUNCTION(BlueprintNativeEvent)
	void AddToSpellPoints(int32 InSpellPoints);
};
