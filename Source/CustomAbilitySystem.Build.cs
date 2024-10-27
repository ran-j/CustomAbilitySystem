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
