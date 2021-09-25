#include "DialogueGraphAssetActions.h"
#include "DialogueGraph.h"
#include "DialogueSystemEditor.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions"

uint32 FDialogueGraphAssetActions::GetCategories()
{
  return EAssetTypeCategories::Misc;
}

FText FDialogueGraphAssetActions::GetName() const
{
  return NSLOCTEXT("AssetTypeActions", "DialogueGraphAssetActions", "Dialogue Graph Asset");
}

UClass *FDialogueGraphAssetActions::GetSupportedClass() const
{
  return UDialogueGraph::StaticClass();
}

FColor FDialogueGraphAssetActions::GetTypeColor() const
{
  return FColor::White;
}

void FDialogueGraphAssetActions::OpenAssetEditor(const TArray<UObject *> &InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
  EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()
                                ? EToolkitMode::WorldCentric
                                : EToolkitMode::Standalone;

  for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
  {
    auto DialogueGraph = Cast<UDialogueGraph>(*ObjIt);

    if (DialogueGraph != nullptr)
    {
        FDialogueSystemEditorModule* DialogueSystemEditorModule = &FModuleManager::LoadModuleChecked<FDialogueSystemEditorModule>("DialogueSystemEditor");
        DialogueSystemEditorModule->CreateDialogueGraphEditor(Mode, EditWithinLevelEditor, DialogueGraph);
    }
  }
}

#undef LOCTEXT_NAMESPACE