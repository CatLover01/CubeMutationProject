// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class CubeMutationProject : ModuleRules
{
	public CubeMutationProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = false;
																												// For LootLockerSDK
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "LootLockerSDK", "UE5Coro" });

		PrivateDependencyModuleNames.AddRange(new string[] { "EnhancedInput", "Niagara" });
		
		
        // For LootLockerSDK
        PrivateDependencyModuleNames.AddRange(new string[] { "HTTP", "Json", "JsonUtilities" });
        
        
        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
