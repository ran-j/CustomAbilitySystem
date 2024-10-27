// Copyright (c) 2024 Ranieri Abreu (Ran-j)
// 
// This source code is licensed under the MIT License found in the
// LICENSE file in the root directory of this source tree.
using UnrealBuildTool;

public class CustomAbilitySystem : ModuleRules
{
    public CustomAbilitySystem(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicIncludePaths.AddRange(
            new string[] {
                "CustomAbilitySystem/Public"
            }
        );
        PrivateIncludePaths.AddRange(
            new string[] {
                "CustomAbilitySystem/Private",
            }
        );
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "InputCore",
                // "GameplayTasks", // For tasks in future
            }
        );
    }
}
