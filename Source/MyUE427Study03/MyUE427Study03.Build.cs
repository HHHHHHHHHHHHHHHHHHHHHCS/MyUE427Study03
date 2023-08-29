// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyUE427Study03 : ModuleRules
{
	public MyUE427Study03(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
			{ "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "UMG", "NavigationSystem", "Paper2D" });

		PrivateDependencyModuleNames.AddRange(new string[] { "MovieSceneCapture" });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}