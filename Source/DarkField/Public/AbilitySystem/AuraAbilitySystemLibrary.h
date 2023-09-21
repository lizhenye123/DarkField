// Dark Field

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAbilitySystemComponent;
enum class ECharacterClass : uint8;
class UAttributeWidgetController;
class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class DARKFIELD_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//获取OverlayWidgetController
	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController*GetOverlayWidgetController(const UObject*WorldContextObject);

	//获取AttributeWidgetController
	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|WidgetController")
	static UAttributeWidgetController*GetAttributeWidgetController(const UObject*WorldContextObject);

	//初始化角色的默认属性
	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|CharacterClassDefault")
	static void InitialzeDefaultAttributes(const UObject*WorldContextObject, ECharacterClass CharacterClass,float Level,UAbilitySystemComponent*ASC);

	//注册角色的技能
	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|CharacterClassDefault")
	static void GiveStartupAbilities(const UObject*WorldContextObject,UAbilitySystemComponent*ASC,ECharacterClass CharacterClass);

	//获取GameMode里的ClassInfo
	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|CharacterClassDefault")
	static UCharacterClassInfo *GetCharacterClassInfo(const UObject*WorldContextObject);

	//当前的GE是不是伤害减半
	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|CharacterClassDefault")
	static bool IsBlockedHit(const FGameplayEffectContextHandle&EffectContextHandle);

	//当前的GE是不是暴击
	UFUNCTION(BlueprintPure,Category="AuraAbilitySystemLibrary|CharacterClassDefault")
	static bool IsCriticalHit(const FGameplayEffectContextHandle&EffectContextHandle);

	//设置当前GE是否阻挡
	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|CharacterClassDefault")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle&EffectContextHandle,bool bInIsBlockedHit);

	//设置当前GE是否暴击
	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|CharacterClassDefault")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle&EffectContextHandle,bool bInIsCriticalHit);
};
