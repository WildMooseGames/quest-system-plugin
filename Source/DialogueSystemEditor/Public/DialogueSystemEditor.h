#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Modules/ModuleManager.h"
#include "EdGraphUtilities.h"
#include "IAssetTypeActions.h"

class FDialogueGraphEditor; 

class FDialogueSystemEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility
{
public:
  /** IModuleInterface implementation */
  virtual void StartupModule() override;
  virtual void ShutdownModule() override;

  virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override { return MenuExtensibilityManager; }
  virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override { return ToolBarExtensibilityManager; }

  virtual TSharedRef<FDialogueGraphEditor> CreateDialogueGraphEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UObject* Object);

private:

	TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;

	TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;

	TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;

	TSharedPtr<FGraphPanelNodeFactory> DialogueGraphPanelNodeFactory;
};