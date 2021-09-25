#include "DialogueSystemEditor.h"
#include "EdGraphUtilities.h"
#include "IAssetTools.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "DialogueGraphAssetActions.h"
#include "DialogueGraphEditor/DialogueGraphEditor.h"
#include "DialogueGraphEditor/DialogueEdNode.h"
#include "DialogueGraphEditor/DialogueEdEdge.h"
#include "DialogueGraphEditor/SDialogueGraphEdge.h"
#include "DialogueGraphEditor/SDialogueGraphNode.h"

#define LOCTEXT_NAMESPACE "DialogueSystemEditor"

class FDialogueGraphPanelNodeFactory : public FGraphPanelNodeFactory
{
	virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override
	{
		if (UDialogueEdNode* EdNode_GraphNode = Cast<UDialogueEdNode>(Node))
		{
			return SNew(SDialogueGraphNode, EdNode_GraphNode);
		}
		else if (UDialogueEdEdge* EdNode_Edge = Cast<UDialogueEdEdge>(Node))
		{
			return SNew(SDialogueGraphEdge, EdNode_Edge);
		}
		return nullptr;
	}
};

void FDialogueSystemEditorModule::StartupModule()
{
	DialogueGraphPanelNodeFactory = MakeShareable(new FDialogueGraphPanelNodeFactory());
	FEdGraphUtilities::RegisterVisualNodeFactory(DialogueGraphPanelNodeFactory);
	IAssetTools &AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	auto Action = MakeShareable(new FDialogueGraphAssetActions());
	AssetTools.RegisterAssetTypeActions(Action);
	RegisteredAssetTypeActions.Add(Action);

	MenuExtensibilityManager = MakeShareable(new FExtensibilityManager);
	ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);

	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FDialogueSystemEditorModule::ShutdownModule()
{

  FAssetToolsModule *AssetToolsModule = FModuleManager::GetModulePtr<FAssetToolsModule>("AssetTools");

  if (AssetToolsModule != nullptr)
  {
    IAssetTools &AssetTools = AssetToolsModule->Get();

    for (auto Action : RegisteredAssetTypeActions)
    {
      AssetTools.UnregisterAssetTypeActions(Action);
    }
  }

  if (DialogueGraphPanelNodeFactory.IsValid())
  {
	  FEdGraphUtilities::UnregisterVisualNodeFactory(DialogueGraphPanelNodeFactory);
	  DialogueGraphPanelNodeFactory.Reset();
  }

  MenuExtensibilityManager.Reset();
  ToolBarExtensibilityManager.Reset();
  // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
  // we call this function before unloading the module.
}

TSharedRef<FDialogueGraphEditor> FDialogueSystemEditorModule::CreateDialogueGraphEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost> &InitToolkitHost, class UObject *Object)
{
  // Initialize and spawn a new custom asset editor with the provided parameters
  TSharedRef<FDialogueGraphEditor> NewDialogueGraphEditor(new FDialogueGraphEditor());
  NewDialogueGraphEditor->InitDialogueGraphEditor(Mode, InitToolkitHost, Object);
  return NewDialogueGraphEditor;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDialogueSystemEditorModule, DialogueSystemEditor)