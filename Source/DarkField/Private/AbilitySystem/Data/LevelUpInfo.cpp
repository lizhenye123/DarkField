// Dark Field


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP)const
{
	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		//针对的是0,1这个Index下的Level
		//Index为0的数据就是个占位符，根本不用
		if(LevelUpInforamtion.Num()-1 <= Level) return Level;

		if (XP>= LevelUpInforamtion[Level].LevelUpRequirement)
		{
			Level++;
		}else
		{
			bSearching=false;
		}
	}

	return Level;
}
