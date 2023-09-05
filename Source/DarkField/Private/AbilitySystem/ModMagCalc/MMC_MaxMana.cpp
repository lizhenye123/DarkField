// Dark Field


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interface/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer*SourceTag = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer*TargetTag = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTag;
	EvaluateParameters.TargetTags = TargetTag;
	float Intelligence=0;
	GetCapturedAttributeMagnitude(IntelligenceDef,Spec,EvaluateParameters,Intelligence);
	Intelligence = FMath::Max<float>(Intelligence,0);

	ICombatInterface*CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	int32 PLayerLevel = CombatInterface->GetPlayerLevel();
	
	return	50+(Intelligence*2.5)+(15*PLayerLevel);
}
