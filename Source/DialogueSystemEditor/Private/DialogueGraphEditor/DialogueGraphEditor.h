#pragma once

#include "Misc/NotifyHook.h"
#include "EditorUndoClient.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class UDialogueGraph; 

class FDialogueGraphEditor : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook, public FGCObject
{
public:

	FDialogueGraphEditor();
	/** Destructor */
	virtual ~FDialogueGraphEditor();

	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;

	void InitDialogueGraphEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* InObject);

	//~ Begin IToolkit Interface
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetDocumentationLink() const override;
	virtual void SaveAsset_Execute() override;
	//~ End IToolkit Interface

		//Toolbar
	//void UpdateToolbar();
	TSharedPtr<class FDialogueGraphEditorToolbar> GetToolbarBuilder() { return ToolbarBuilder; }
	void RegisterToolbarTab(const TSharedRef<class FTabManager>& TabManager);

		//~ Begin FEditorUndoClient Interface
	virtual void PostUndo(bool bSuccess) override;
	//virtual void PostRedo(bool bSuccess) override;
	// End of FEditorUndoClient

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	//~ Begin FNotifyHook Interface
	virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;
	 //End of FNotifyHook

	// Delegates 
	//void OnGraphEditorFocused(const TSharedRef<SGraphEditor>& InGraphEditor);

	void OnPackageSaved(const FString& PackageFileName, UObject* Outer);


private : 

	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);

	void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);

	void CreateInternalWidgets();

	TSharedRef<SGraphEditor> CreateGraphEditorWidget();

	void CreateCommandList();

	TSharedPtr<SGraphEditor> GetCurrentGraphEditor() const;

	FGraphPanelSelectionSet GetSelectedNodes() const;

	void SelectAllNodes();
	bool CanSelectAllNodes();
	void DeleteSelectedNodes();
	bool CanDeleteNodes();
	void DeleteSelectedDuplicatableNodes();
	void CutSelectedNodes();
	bool CanCutNodes();
	void CopySelectedNodes();
	bool CanCopyNodes();
	void PasteNodes();
	void PasteNodesHere(const FVector2D& Location);
	bool CanPasteNodes();
	void DuplicateNodes();
	bool CanDuplicateNodes();
	void OnRenameNode();
	bool CanRenameNodes() const;

	void OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection);

	UDialogueGraph* DialogueGraph;

	/** Handle to the registered OnPackageSave delegate */
	FDelegateHandle OnPackageSavedDelegateHandle;

	TSharedPtr<class FDialogueGraphEditorToolbar> ToolbarBuilder;

	TSharedPtr<class IDetailsView> DetailsView;
	TSharedPtr<SGraphEditor> GraphEditorWidget;

	TSharedPtr<FUICommandList> GraphEditorCommands;

	static const FName GraphCanvasTabId;
	static const FName PropertiesTabId;

};
