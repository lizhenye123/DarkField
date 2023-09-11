// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass:uint8
{
	//元素师
	Elementalist,
	//战士
	Warrior,
	//游侠
	Ranger,
};

USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	//角色的默认主属性
	UPROPERTY(EditDefaultsOnly,Category="Class Defaults")
	TSubclassOf<UGameplayEffect>PrimaryAttributes;
	
};
/**
 * 所有角色的的初始化信息
 */
UCLASS(BlueprintType)
class DARKFIELD_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	//所有角色默认属性
	UPROPERTY(EditDefaultsOnly,Category="Character Class Defaults")
	TMap<ECharacterClass,FCharacterClassDefaultInfo>CharacterClassInfomation;
	
	//次要属性 所有角色初始化通用的角色属性
	UPROPERTY(EditDefaultsOnly,Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect>SecondaryAttributes;

	//血和蓝,所有角色初始化通用的角色属性
	UPROPERTY(EditDefaultsOnly,Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect>VitalAttributes;

	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass);
};
