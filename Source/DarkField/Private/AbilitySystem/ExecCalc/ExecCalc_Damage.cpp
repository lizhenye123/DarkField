// Dark Field


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"

struct AuraDamageStatics
{
	//声明了 没赋值
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	AuraDamageStatics()
	{
		//定义捕获的目标
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,BlockChance,Target,false);
	}
};

static const AuraDamageStatics&DamageStatics()
{
	static AuraDamageStatics DStatic;
	return DStatic;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent*SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent*TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor*SourceAvater = SourceASC==nullptr?nullptr:SourceASC->GetAvatarActor();
	const AActor*TargetAvater = TargetASC==nullptr?nullptr:TargetASC->GetAvatarActor();

	const FGameplayEffectSpec&Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer*SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer*TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float Damage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);
	
	float TargetBlockChance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef,EvaluateParameters,TargetBlockChance);
	TargetBlockChance = FMath::Max(TargetBlockChance,0);

	const bool bBlocked = FMath::RandRange(1,100)<TargetBlockChance;
	Damage = bBlocked==true ? Damage/2 : Damage;

	const FGameplayModifierEvaluatedData EvalautedData(UAuraAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive,Damage);
	OutExecutionOutput.AddOutputModifier(EvalautedData);
}
