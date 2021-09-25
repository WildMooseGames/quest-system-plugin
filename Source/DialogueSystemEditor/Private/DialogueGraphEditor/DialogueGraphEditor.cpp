#include "DialogueGraphEditor.h"
#include "DialogueGraph.h"
#include "DialogueEdGraph.h"
#include "DialogueEdNode.h"
#include "DialogueEdEdge.h"
#include "DialogueEdGraphSchema.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "DialogueGraphEditorToolbar.h"
#include "GraphEditorActions.h"
#include "Framework/Commands/GenericCommands.h"
#include "HAL/PlatformApplicationMisc.h"
#include "EdGraphUtilities.h"

#define LOCTEXT_NAMESPACE "DialogueGraphEditor"

const FName FDialogueGraphEditor::GraphCanvasTabId(TEXT("DialogueGraphEditor_GraphCanvas"));
const FName FDialogueGraphEditor::PropertiesTabId(TEXT("DialogueGraphEditor_Properties"));

FDialogueGraphEditor::FDialogueGraphEditor()
{
	DialogueGraph = nullptr; 

	OnPackageSavedDelegateHandle = UPackage::PackageSavedEvent.AddRaw(this, &FDialogueGraphEditor::OnPackageSaved);
}

FDialogueGraphEditor::~FDialogueGraphEditor()
{
	UPackage::PackageSavedEvent.Remove(OnPackageSavedDelegateHandle);
}

void FDialogueGraphEditor::InitDialogueGraphEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* InObject)
{
	DialogueGraph = Cast<UDialogueGraph>(InObject);

	if (DialogueGraph->DialogueEdGraph == nullptr)
	{
		DialogueGraph->DialogueEdGraph = CastChecked<UDialogueEdGraph>(FBlueprintEditorUtils::CreateNewGraph(DialogueGraph, NAME_None, UDialogueEdGraph::StaticClass(), UDialogueEdGraphSchema::StaticClass()));
		DialogueGraph->DialogueEdGraph->bAllowDeletion = false;

		// Give the schema a chance to fill out any required nodes (like the results node)
		const UEdGraphSchema* Schema = DialogueGraph->DialogueEdGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph(*DialogueGraph->DialogueEdGraph);

	}

	FGenericCommands::Register();
	FGraphEditorCommands::Register();

	if (!ToolbarBuilder.IsValid())
	{
		ToolbarBuilder = MakeShareable(new FDialogueGraphEditorToolbar(SharedThis(this)));
	}

	CreateInternalWidgets();

	// Layout
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_DialogueGraphEditor_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)->SetHideTabWell(true)
			)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)->SetSizeCoefficient(0.9f)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.80f)
					->AddTab(GraphCanvasTabId, ETabState::OpenedTab)->SetHideTabWell(true)
				)
				->Split
				(
					FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.5f)
						->AddTab(PropertiesTabId, ETabState::OpenedTab)->SetHideTabWell(true)
					)
				)
			)
		);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, TEXT("DialogueGraphEditorApp"), StandaloneDefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, DialogueGraph, false);

	RegenerateMenusAndToolbars();
}

void FDialogueGraphEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_SoundCueEditor", "Sound Cue Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(GraphCanvasTabId, FOnSpawnTab::CreateSP(this, &FDialogueGraphEditor::SpawnTab_Viewport))
		.SetDisplayName(LOCTEXT("GraphCanvasTab", "Viewport"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "GraphEditor.EventGraph_16x"));

	InTabManager->RegisterTabSpawner(PropertiesTabId, FOnSpawnTab::CreateSP(this, &FDialogueGraphEditor::SpawnTab_Details))
		.SetDisplayName(LOCTEXT("DetailsTab", "Details"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

}

void FDialogueGraphEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(GraphCanvasTabId);
	InTabManager->UnregisterTabSpawner(PropertiesTabId);
}

FName FDialogueGraphEditor::GetToolkitFName() const
{
	return FName("FDialogueGraphEditor");
}

FText FDialogueGraphEditor::GetBaseToolkitName() const
{
	return LOCTEXT("DialogueGraphEditorAppLabel", "Dialogue Graph Editor");
}

FText FDialogueGraphEditor::GetToolkitName() const
{
	const bool bDirtyState = DialogueGraph->GetOutermost()->IsDirty();

	FFormatNamedArguments Args;
	Args.Add(TEXT("DialogueGraphName"), FText::FromString(DialogueGraph->GetName()));
	Args.Add(TEXT("DirtyState"), bDirtyState ? FText::FromString(TEXT("*")) : FText::GetEmpty());
	return FText::Format(LOCTEXT("DialogueGraphEditorToolkitName", "{DialogueGraphName}{DirtyState}"), Args);
}

FText FDialogueGraphEditor::GetToolkitToolTipText() const
{
	return FAssetEditorToolkit::GetToolTipTextForObject(DialogueGraph);
}

FLinearColor FDialogueGraphEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

FString FDialogueGraphEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("DialogueGraphEditor");
}

FString FDialogueGraphEditor::GetDocumentationLink() const
{
	return TEXT("");
}

void FDialogueGraphEditor::SaveAsset_Execute()
{
	if (DialogueGraph != nullptr)
	{
		UDialogueEdGraph* EdGraph = Cast<UDialogueEdGraph>(DialogueGraph->DialogueEdGraph);
		check(EdGraph != nullptr);

		EdGraph->UpdateAsset();
	}

	FAssetEditorToolkit::SaveAsset_Execute();
}

void FDialogueGraphEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(DialogueGraph);
	Collector.AddReferencedObject(DialogueGraph->DialogueEdGraph);
}

void FDialogueGraphEditor::NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged)
{
	if (DialogueGraph != nullptr)
	{
		UDialogueEdGraph* EdGraph = Cast<UDialogueEdGraph>(DialogueGraph->DialogueEdGraph);
		check(EdGraph != nullptr);

		EdGraph->UpdateAsset();
	}
}

TSharedRef<SDockTab> FDialogueGraphEditor::SpawnTab_Viewport(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == GraphCanvasTabId);

	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.Label(LOCTEXT("DialogueGraphCanvasTitle", "Viewport"));

	if (GraphEditorWidget.IsValid())
	{
		SpawnedTab->SetContent(GraphEditorWidget.ToSharedRef());
	}

	return SpawnedTab;
}

TSharedRef<SDockTab> FDialogueGraphEditor::SpawnTab_Details(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == PropertiesTabId);

	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("LevelEditor.Tabs.Details"))
		.Label(LOCTEXT("Details_Title", "Property"))
		[
			DetailsView.ToSharedRef()
		];
}

void FDialogueGraphEditor::CreateInternalWidgets()
{
	GraphEditorWidget = CreateGraphEditorWidget(); 

	FDetailsViewArgs Args;
	Args.bHideSelectionTip = true;
	Args.NotifyHook = this;

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	DetailsView = PropertyModule.CreateDetailView(Args);
	DetailsView->SetObject(DialogueGraph);
	DetailsView->OnFinishedChangingProperties().AddSP(this, &FDialogueGraphEditor::OnFinishedChangingProperties);
}

TSharedRef<SGraphEditor> FDialogueGraphEditor::CreateGraphEditorWidget()
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("AppearanceCornerText_DialogueGraph", "Dialogue Graph");

	CreateCommandList();

	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FDialogueGraphEditor::OnSelectedNodesChanged);

	return SNew(SGraphEditor)
		.IsEditable(true)
		.Appearance(AppearanceInfo)
		.AdditionalCommands(GraphEditorCommands)
		.GraphToEdit(DialogueGraph->DialogueEdGraph)
		.GraphEvents(InEvents)
		.AutoExpandActionMenu(true)
		.ShowGraphStateOverlay(false);
}

void FDialogueGraphEditor::CreateCommandList()
{
	if (GraphEditorCommands.IsValid())
	{
		return;
	}

	GraphEditorCommands = MakeShareable(new FUICommandList);

	GraphEditorCommands->MapAction(FGenericCommands::Get().SelectAll,
		FExecuteAction::CreateSP(this, &FDialogueGraphEditor::SelectAllNodes),
		FCanExecuteAction::CreateSP(this, &FDialogueGraphEditor::CanSelectAllNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Delete,
		FExecuteAction::CreateSP(this, &FDialogueGraphEditor::DeleteSelectedNodes),
		FCanExecuteAction::CreateSP(this, &FDialogueGraphEditor::CanDeleteNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Copy,
		FExecuteAction::CreateSP(this, &FDialogueGraphEditor::CopySelectedNodes),
		FCanExecuteAction::CreateSP(this, &FDialogueGraphEditor::CanCopyNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Cut,
		FExecuteAction::CreateSP(this, &FDialogueGraphEditor::CutSelectedNodes),
		FCanExecuteAction::CreateSP(this, &FDialogueGraphEditor::CanCutNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Paste,
		FExecuteAction::CreateSP(this, &FDialogueGraphEditor::PasteNodes),
		FCanExecuteAction::CreateSP(this, &FDialogueGraphEditor::CanPasteNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Duplicate,
		FExecuteAction::CreateSP(this, &FDialogueGraphEditor::DuplicateNodes),
		FCanExecuteAction::CreateSP(this, &FDialogueGraphEditor::CanDuplicateNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Rename,
		FExecuteAction::CreateSP(this, &FDialogueGraphEditor::OnRenameNode),
		FCanExecuteAction::CreateSP(this, &FDialogueGraphEditor::CanRenameNodes)
	);

}

TSharedPtr<SGraphEditor> FDialogueGraphEditor::GetCurrentGraphEditor() const
{
	return GraphEditorWidget;
}

FGraphPanelSelectionSet FDialogueGraphEditor::GetSelectedNodes() const
{
	FGraphPanelSelectionSet CurrentSelection;
	TSharedPtr<SGraphEditor> FocusedGraphEd = GetCurrentGraphEditor();
	if (FocusedGraphEd.IsValid())
	{
		CurrentSelection = FocusedGraphEd->GetSelectedNodes();
	}

	return CurrentSelection;
}

void FDialogueGraphEditor::SelectAllNodes()
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrentGraphEditor();
	if (CurrentGraphEditor.IsValid())
	{
		CurrentGraphEditor->SelectAllNodes();
	}
}

bool FDialogueGraphEditor::CanSelectAllNodes()
{
	return true;
}

void FDialogueGraphEditor::DeleteSelectedNodes()
{

	if (GraphEditorWidget)
	{
		const FScopedTransaction Transaction(FGenericCommands::Get().Delete->GetDescription());

		GraphEditorWidget->GetCurrentGraph()->Modify();

		const FGraphPanelSelectionSet SelectedNodes = GraphEditorWidget->GetSelectedNodes();
		GraphEditorWidget->ClearSelectionSet();

		for (FGraphPanelSelectionSet::TConstIterator NodeIt(SelectedNodes); NodeIt; ++NodeIt)
		{
			UEdGraphNode* EdNode = Cast<UEdGraphNode>(*NodeIt);
			

			if (EdNode && EdNode->CanUserDeleteNode())
			{
				if (UDialogueEdNode* EdNode_Node = Cast<UDialogueEdNode>(EdNode))
				{
					EdNode_Node->Modify();

					const UEdGraphSchema* Schema = EdNode_Node->GetSchema();
					if (Schema != nullptr)
					{
						Schema->BreakNodeLinks(*EdNode_Node);
					}

					EdNode_Node->DestroyNode();
				}
				else
				{
					EdNode->Modify();
					EdNode->DestroyNode();
				}
			}
		}
	}


}

bool FDialogueGraphEditor::CanDeleteNodes()
{
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();

	if (SelectedNodes.Num() == 1)
	{
		for (FGraphPanelSelectionSet::TConstIterator NodeIt(SelectedNodes); NodeIt; ++NodeIt)
		{
			UEdGraphNode* Node = Cast<UEdGraphNode>(*NodeIt);

			if (!Node->CanUserDeleteNode())
			{
				// Return false if only root node is selected, as it can't be deleted
				return false;
			}
		}
	}

	return SelectedNodes.Num() > 0;
}

void FDialogueGraphEditor::DeleteSelectedDuplicatableNodes()
{

	if (GraphEditorWidget)
	{
		const FGraphPanelSelectionSet OldSelectedNodes = GraphEditorWidget->GetSelectedNodes();
		GraphEditorWidget->ClearSelectionSet();

		for (FGraphPanelSelectionSet::TConstIterator SelectedIter(OldSelectedNodes); SelectedIter; ++SelectedIter)
		{
			UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
			if (Node && Node->CanDuplicateNode())
			{
				GraphEditorWidget->SetNodeSelection(Node, true);
			}
		}

		// Delete the duplicatable nodes
		DeleteSelectedNodes();

		GraphEditorWidget->ClearSelectionSet();

		for (FGraphPanelSelectionSet::TConstIterator SelectedIter(OldSelectedNodes); SelectedIter; ++SelectedIter)
		{
			if (UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter))
			{
				GraphEditorWidget->SetNodeSelection(Node, true);
			}
		}
	}
}

void FDialogueGraphEditor::CutSelectedNodes()
{
	CopySelectedNodes();
	DeleteSelectedDuplicatableNodes();
}

bool FDialogueGraphEditor::CanCutNodes()
{
	return CanCopyNodes() && CanDeleteNodes();
}

void FDialogueGraphEditor::CopySelectedNodes()
{
	// Export the selected nodes and place the text on the clipboard
	FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();

	FString ExportedText;

	for (FGraphPanelSelectionSet::TIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (Node == nullptr)
		{
			SelectedIter.RemoveCurrent();
			continue;
		}

		if (UDialogueEdEdge* EdNode_Edge = Cast<UDialogueEdEdge>(*SelectedIter))
		{
			UDialogueEdNode* StartNode = EdNode_Edge->GetStartNode();
			UDialogueEdNode* EndNode = EdNode_Edge->GetEndNode();

			if (!SelectedNodes.Contains(StartNode) || !SelectedNodes.Contains(EndNode))
			{
				SelectedIter.RemoveCurrent();
				continue;
			}
		}

		Node->PrepareForCopying();
	}

	FEdGraphUtilities::ExportNodesToText(SelectedNodes, ExportedText);
	FPlatformApplicationMisc::ClipboardCopy(*ExportedText);
}

bool FDialogueGraphEditor::CanCopyNodes()
{
	// If any of the nodes can be duplicated then we should allow copying
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (Node && Node->CanDuplicateNode())
		{
			return true;
		}
	}

	return false;
}

void FDialogueGraphEditor::PasteNodes()
{
	if (GraphEditorWidget)
	{
		PasteNodesHere(GraphEditorWidget->GetPasteLocation());
	}
}

void FDialogueGraphEditor::PasteNodesHere(const FVector2D& Location)
{

	if (GraphEditorWidget)
	{
		// Select the newly pasted stuff
		UEdGraph* EdGraph = GraphEditorWidget->GetCurrentGraph();

		{
			const FScopedTransaction Transaction(FGenericCommands::Get().Paste->GetDescription());
			EdGraph->Modify();

			// Clear the selection set (newly pasted stuff will be selected)
			GraphEditorWidget->ClearSelectionSet();

			// Grab the text to paste from the clipboard.
			FString TextToImport;
			FPlatformApplicationMisc::ClipboardPaste(TextToImport);

			// Import the nodes
			TSet<UEdGraphNode*> PastedNodes;
			FEdGraphUtilities::ImportNodesFromText(EdGraph, TextToImport, PastedNodes);

			//Average position of nodes so we can move them while still maintaining relative distances to each other
			FVector2D AvgNodePosition(0.0f, 0.0f);

			for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
			{
				UEdGraphNode* Node = *It;
				AvgNodePosition.X += Node->NodePosX;
				AvgNodePosition.Y += Node->NodePosY;
			}

			float InvNumNodes = 1.0f / float(PastedNodes.Num());
			AvgNodePosition.X *= InvNumNodes;
			AvgNodePosition.Y *= InvNumNodes;

			for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
			{
				UEdGraphNode* Node = *It;
				GraphEditorWidget->SetNodeSelection(Node, true);

				Node->NodePosX = (Node->NodePosX - AvgNodePosition.X) + Location.X;
				Node->NodePosY = (Node->NodePosY - AvgNodePosition.Y) + Location.Y;

				Node->SnapToGrid(16);

				// Give new node a different Guid from the old one
				Node->CreateNewGuid();
			}
		}

		// Update UI
		GraphEditorWidget->NotifyGraphChanged();

		UObject* GraphOwner = EdGraph->GetOuter();
		if (GraphOwner)
		{
			GraphOwner->PostEditChange();
			GraphOwner->MarkPackageDirty();
		}
	}

}

bool FDialogueGraphEditor::CanPasteNodes()
{
	FString ClipboardContent;
	FPlatformApplicationMisc::ClipboardPaste(ClipboardContent);

	return FEdGraphUtilities::CanImportNodesFromText(DialogueGraph->DialogueEdGraph, ClipboardContent);
}

void FDialogueGraphEditor::DuplicateNodes()
{
	CopySelectedNodes();
	PasteNodes();
}

bool FDialogueGraphEditor::CanDuplicateNodes()
{
	return CanCopyNodes();
}

void FDialogueGraphEditor::OnRenameNode()
{
	if (GraphEditorWidget.IsValid())
	{
		const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
		for (FGraphPanelSelectionSet::TConstIterator NodeIt(SelectedNodes); NodeIt; ++NodeIt)
		{
			UEdGraphNode* SelectedNode = Cast<UEdGraphNode>(*NodeIt);
			if (SelectedNode != NULL && SelectedNode->bCanRenameNode)
			{
				GraphEditorWidget->IsNodeTitleVisible(SelectedNode, true);
				break;
			}
		}
	}
}

bool FDialogueGraphEditor::CanRenameNodes() const
{
		return GetSelectedNodes().Num() == 1;
}

void FDialogueGraphEditor::OnSelectedNodesChanged(const TSet<class UObject*>& NewSelection)
{
	TArray<UObject*> Selection;

	for (UObject* SelectionEntry : NewSelection)
	{
		Selection.Add(SelectionEntry);
	}

	if (Selection.Num() == 0)
	{
		DetailsView->SetObject(DialogueGraph);
	}
	else
	{
		DetailsView->SetObjects(Selection);
	}
}

void FDialogueGraphEditor::OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent)
{
	if (DialogueGraph == nullptr)
		return;

	DialogueGraph->DialogueEdGraph->GetSchema()->ForceVisualizationCacheClear();
}

void FDialogueGraphEditor::OnPackageSaved(const FString& PackageFileName, UObject* Outer)
{
	if (DialogueGraph != nullptr)
	{
		UDialogueEdGraph* EdGraph = Cast<UDialogueEdGraph>(DialogueGraph->DialogueEdGraph);
		check(EdGraph != nullptr);

		EdGraph->UpdateAsset();
	}
}

void FDialogueGraphEditor::PostUndo(bool bSuccess)
{
	if (GraphEditorWidget.IsValid())
	{
		GraphEditorWidget->ClearSelectionSet();
		GraphEditorWidget->NotifyGraphChanged();
		FSlateApplication::Get().DismissAllMenus();
	}

}

void FDialogueGraphEditor::RegisterToolbarTab(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
}

#undef LOCTEXT_NAMESPACE