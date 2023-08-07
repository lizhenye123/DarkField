// Dark Field

using UnrealBuildTool;
using System.Collections.Generic;

public class DarkFieldEditorTarget : TargetRules
{
	public DarkFieldEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "DarkField" } );
	}
}
