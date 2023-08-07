// Dark Field

using UnrealBuildTool;
using System.Collections.Generic;

public class DarkFieldTarget : TargetRules
{
	public DarkFieldTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "DarkField" } );
	}
}
