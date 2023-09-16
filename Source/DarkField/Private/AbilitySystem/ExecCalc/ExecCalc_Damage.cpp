// Dark Field


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interface/CombatInterface.h"

struct AuraDamageStatics
{
	//声明了 没赋值
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChanage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	AuraDamageStatics()
	{
		//定义捕获的目标
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,Armor,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,BlockChance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,ArmorPenetration,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitChanage,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitDamage,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet,CriticalHitResistance,Target,false);
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
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent*SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent*TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor*SourceAvater = SourceASC==nullptr?nullptr:SourceASC->GetAvatarActor();
	AActor*TargetAvater = TargetASC==nullptr?nullptr:TargetASC->GetAvatarActor();
	ICombatInterface*SourceCombatInterface = Cast<ICombatInterface>(SourceAvater);
	ICombatInterface*TargetCombatInterface = Cast<ICombatInterface>(TargetAvater);

	const FGameplayEffectSpec&Spec = ExecutionParams.GetOwningSpec();
	
	const FGameplayTagContainer*SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer*TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	//获取ByCaller发过来的伤害
	float Damage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);

	//Target阻断几率
	float TargetBlockChance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef,EvaluateParameters,TargetBlockChance);
	TargetBlockChance = FMath::Max(TargetBlockChance,0);

	const bool bBlocked = FMath::RandRange(1,100)<TargetBlockChance;
	Damage = bBlocked==true ? Damage/2 : Damage;
	FGameplayEffectContextHandle DamageEffectContextHandle = Spec.GetContext();
	UAuraAbilitySystemLibrary::SetIsBlockedHit(DamageEffectContextHandle,bBlocked);

	//Targte护甲
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef,EvaluateParameters,TargetArmor);
	TargetArmor = FMath::Max(TargetArmor,0);

	//Source护甲穿透
	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef,EvaluateParameters,SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max(SourceArmorPenetration,0);

	//获取护甲穿透的系数
	const UCharacterClassInfo*CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvater);
	const FRealCurve*ArmorPenetrationCurve= CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"),FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	
	//具体的护甲值
	const float EffectActiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f;

	//获取护甲抵消系数
	const FRealCurve*EffectActiveArmorCurve= CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectActiveArmor"),FString());
	const float EffectActiveArmorCoefficient = EffectActiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	
	//实际伤害
	Damage *= (100 - EffectActiveArmor *EffectActiveArmorCoefficient)/100.f;

	//Source暴击几率
	float SourceCriticalHitChanage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanageDef,EvaluateParameters,SourceCriticalHitChanage);
	SourceCriticalHitChanage = FMath::Max(SourceCriticalHitChanage,0);

	//Source暴击伤害
	float SourceCriticalHitDamage =0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef,EvaluateParameters,SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Max(SourceCriticalHitDamage,0);

	//Target抗暴击
	float TargetCriticalHitResistance =0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef,EvaluateParameters,TargetCriticalHitResistance);
	TargetCriticalHitResistance = FMath::Max(TargetCriticalHitResistance,0);

	//抗暴击的系数
	const FRealCurve*CriticalHitResistanceCurve= CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectActiveArmor"),FString());
	const float CriticalHitResistanceCoefficient = CriticalHitResistanceCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	
	const float EffectiveCriticalHitChange = SourceCriticalHitChanage - TargetCriticalHitResistance*CriticalHitResistanceCoefficient;
	const bool bCriticalHit = FMath::RandRange(1,100)<EffectiveCriticalHitChange;
	UAuraAbilitySystemLibrary::SetIsCriticalHit(DamageEffectContextHandle,bCriticalHit);
	
	//加完暴击的伤害
	Damage = bCriticalHit?2.f*Damage + SourceCriticalHitDamage:Damage;
	
	const FGameplayModifierEvaluatedData EvalautedData(UAuraAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive,Damage);
	OutExecutionOutput.AddOutputModifier(EvalautedData);
}
