#pragma once
#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext:public FGameplayEffectContext
{
	GENERATED_BODY()
public:
	bool IsCriticalHit()const {return bIsCriticalHit;};
	bool IsBlockedHit()const {return bIsBlockedHit;};

	void SetIsBlockedHit(bool bInIsBlockedHit){bIsBlockedHit = bInIsBlockedHit;};
	void SetIsCriticalHit(bool bInIsCriticalHit){bIsCriticalHit = bInIsCriticalHit;};
	
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayEffectContext::StaticStruct();
	}

	/** 创建该上下文的副本，用于复制以便以后修改 */
	virtual FGameplayEffectContext* Duplicate() const
	{
		FGameplayEffectContext* NewContext = new FGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// 是否对命中结果进行深度复制
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}
	
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)override;
protected:
	//阻挡
	UPROPERTY()
	bool bIsBlockedHit = false;

	//暴击
	UPROPERTY()
	bool bIsCriticalHit = false;
};

template<>
struct TStructOpsTypeTraits< FAuraGameplayEffectContext > : public TStructOpsTypeTraitsBase2< FAuraGameplayEffectContext >
{
	enum
	{
		WithNetSerializer = true,// struct 有一个 NetSerialize 函数，用于将其状态序列化到用于网络复制的 FArchive 中。
		WithCopy = true		//结构体可以通过其 copy 赋值操作符进行复制。有必要这样做，以便将 TSharedPtr<FHitResult> 数据复制到各处
	};
};