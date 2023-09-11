// Dark Field

#pragma once

#include "CoreMinimal.h"
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

	UFUNCTION(BlueprintCallable,Category="AuraAbilitySystemLibrary|CharacterClassDefault")
	static void InitialzeDefaultAttributes(const UObject*WorldContextObject, ECharacterClass CharacterClass,float Level,UAbilitySystemComponent*ASC);
};
