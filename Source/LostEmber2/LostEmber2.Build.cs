// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LostEmber2 : ModuleRules
{
    public LostEmber2(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "UMG"       
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "Slate",           
            "SlateCore",       
            "UMG"              
        });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");
    }
}