namespace UnrealBuildTool.Rules
{
    public class WorldActorRegistry : ModuleRules
    {
        public WorldActorRegistry( ReadOnlyTargetRules Target )
            : base( Target )
        {
            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
            bEnforceIWYU = true;

            PrivateIncludePaths.AddRange(
                new string[]
                {
                    "WorldActorRegistry/Private"
                }
            );

            PublicDependencyModuleNames.AddRange(
                new string[] { 
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "GameplayTags"
                }
            );
        }
    }
}
