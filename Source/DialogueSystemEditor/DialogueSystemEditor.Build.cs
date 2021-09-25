using UnrealBuildTool;

public class DialogueSystemEditor : ModuleRules
{
  public DialogueSystemEditor(ReadOnlyTargetRules Target) : base(Target)
  {
    PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

    PublicIncludePaths.AddRange(
      new string[] {
				// ... add public include paths required here ...
			}
      );

    PrivateIncludePaths.AddRange(
      new string[] {
                // ... add other private include paths required here ...
                "DialogueSystemEditor/Private",
      }
      );

    PublicDependencyModuleNames.AddRange(
      new string[]
      {
        "Core",
        "CoreUObject",
        "Engine",
        "UnrealEd",
				// ... add other public dependencies that you statically link with here ...
			}
      );

    PrivateDependencyModuleNames.AddRange(
      new string[]
      {
                "DialogueSystem",
                "QuestEventSystem",
                "AssetTools",
                "Slate",
                "SlateCore",
                "Engine",
                "GraphEditor",
                "PropertyEditor",
                "EditorStyle",
                "Kismet",
                "KismetWidgets",
                "ApplicationCore",
                "ToolMenus",
				// ... add private dependencies that you statically link with here ...
			}
      );

    DynamicallyLoadedModuleNames.AddRange(
      new string[]
      {
				// ... add any modules that your module loads dynamically here ...
            }
      );
  }
}