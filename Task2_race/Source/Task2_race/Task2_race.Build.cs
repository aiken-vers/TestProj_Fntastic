// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Task2_race : ModuleRules
{
	public Task2_race(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Paper2D" });
	}
}
