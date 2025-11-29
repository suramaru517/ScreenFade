// Copyright Metaseven. All Rights Reserved.

using UnrealBuildTool;

public class ScreenFade : ModuleRules
{
	public ScreenFade(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new[]
		{
			"Core",
		});

		PrivateDependencyModuleNames.AddRange(new[]
		{
			"CoreUObject",
			"Engine",
			"SlateCore",
		});
	}
}
