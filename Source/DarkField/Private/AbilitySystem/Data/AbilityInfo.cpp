// Dark Field


#include "AbilitySystem/Data/AbilityInfo.h"

#include "DarkField/AuraLogChannels.h"

FAuraAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogFound)
{
	for (const FAuraAbilityInfo&Info:AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}

	if (bLogFound)
	{
		UE_LOG(LogAura,Error,TEXT("Can`t find info for AbilityTag [%s] On AbilityInfo [%s]"),*AbilityTag.ToString(),*GetNameSafe(this));
	}
	
	return FAuraAbilityInfo();
}
