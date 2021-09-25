#include "DialogueEdGraphSchema.h"
#include "DialogueEdEdge.h"
#include "DialogueEdNode.h"
#include "GraphEditorActions.h"
#include "ToolMenus.h"
#include "DialogueGraphConnectionDrawingPolicy.h"
#include "Framework/Commands/GenericCommands.h"
#include "DialogueEdGraph.h"
#include "SceneDialogueNode.h"
#include "InteractiveDialogueNode.h"
#include "DialogueNode_Base.h"
#include "DialogueRootNode.h"

#define LOCTEXT_NAMESPACE "DialogueEdGraphSchema"

int32 UDialogueEdGraphSchema::CurrentCacheRefreshID = 0;

UEdGraphNode* FDialogueAssetSchemaAction_NewSceneNode::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /*= true*/)
{
	UEdGraphNode* ResultNode = nullptr;

	if (NodeTemplate != nullptr)
	{
		const FScopedTransaction Transaction(LOCTEXT("DialogueGraphEditorNewSceneNode", "Dialogue Graph Editor: New Scene Node"));
		ParentGraph->Modify();
		if (FromPin != nullptr)
			FromPin->Modify();

		NodeTemplate->Rename(nullptr, ParentGraph);
		ParentGraph->AddNode(NodeTemplate, true, bSelectNewNode);

		NodeTemplate->CreateNewGuid();
		NodeTemplate->PostPlacedNewNode();
		NodeTemplate->AllocateDefaultPins();
		NodeTemplate->AutowireNewNode(FromPin);

		NodeTemplate->NodePosX = Location.X;
		NodeTemplate->NodePosY = Location.Y;

		NodeTemplate->DialogueNode->SetFlags(RF_Transactional);
		NodeTemplate->SetFlags(RF_Transactional);

		ResultNode = NodeTemplate;
	}

	return ResultNode;
}

void FDialogueAssetSchemaAction_NewSceneNode::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);
	Collector.AddReferencedObject(NodeTemplate);
}

UEdGraphNode* FDialogueAssetSchemaAction_NewInteractiveNode::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /*= true*/)
{
	UEdGraphNode* ResultNode = nullptr;

	if (NodeTemplate != nullptr)
	{
		const FScopedTransaction Transaction(LOCTEXT("DialogueGraphEditorNewInteractiveNode", "Dialogue Graph Editor: New Interactive Node"));
		ParentGraph->Modify();
		if (FromPin != nullptr)
			FromPin->Modify();

		NodeTemplate->Rename(nullptr, ParentGraph);
		ParentGraph->AddNode(NodeTemplate, true, bSelectNewNode);

		NodeTemplate->CreateNewGuid();
		NodeTemplate->PostPlacedNewNode();
		NodeTemplate->AllocateDefaultPins();
		NodeTemplate->AutowireNewNode(FromPin);

		NodeTemplate->NodePosX = Location.X;
		NodeTemplate->NodePosY = Location.Y;

		NodeTemplate->DialogueNode->SetFlags(RF_Transactional);
		NodeTemplate->SetFlags(RF_Transactional);

		ResultNode = NodeTemplate;
	}

	return ResultNode;
}

void FDialogueAssetSchemaAction_NewInteractiveNode::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);
	Collector.AddReferencedObject(NodeTemplate);
}

UEdGraphNode* FDialogueAssetSchemaAction_NewEdge::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /*= true*/)
{
	UEdGraphNode* ResultNode = nullptr;

	if (NodeTemplate != nullptr)
	{
		const FScopedTransaction Transaction(LOCTEXT("DialogueGraphEditorNewEdge", "Dialogue Graph Editor: New Edge"));
		ParentGraph->Modify();
		if (FromPin != nullptr)
			FromPin->Modify();

		NodeTemplate->Rename(nullptr, ParentGraph);
		ParentGraph->AddNode(NodeTemplate, true, bSelectNewNode);

		NodeTemplate->CreateNewGuid();
		NodeTemplate->PostPlacedNewNode();
		NodeTemplate->AllocateDefaultPins();
		NodeTemplate->AutowireNewNode(FromPin);

		NodeTemplate->NodePosX = Location.X;
		NodeTemplate->NodePosY = Location.Y;

		NodeTemplate->DialogueEdge->SetFlags(RF_Transactional);
		NodeTemplate->SetFlags(RF_Transactional);

		ResultNode = NodeTemplate;
	}

	return ResultNode;
}

void FDialogueAssetSchemaAction_NewEdge::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);
	Collector.AddReferencedObject(NodeTemplate);
}

void UDialogueEdGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	
	FGraphNodeCreator<UDialogueEdNode> NodeCreator(Graph);
	UDialogueEdNode* RootNode = NodeCreator.CreateNode();
	RootNode->NodeClass = UDialogueRootNode::StaticClass();
	NodeCreator.Finalize();
	SetNodeMetaData(RootNode, FNodeMetadata::DefaultGraphNode);

	
	if (UDialogueEdGraph* DialogueGraph = CastChecked<UDialogueEdGraph>(&Graph))
	{
		DialogueGraph->SetRootNode(RootNode);
		//DialogueGraph->AddNode(RootNode); 
	}
}

void UDialogueEdGraphSchema::GetBreakLinkToSubMenuActions(UToolMenu* Menu, UEdGraphPin* InGraphPin)
{
	// Make sure we have a unique name for every entry in the list
	TMap< FString, uint32 > LinkTitleCount;

	FToolMenuSection& Section = Menu->FindOrAddSection("DialogueGraphAssetGraphSchemaPinActions");

	// Add all the links we could break from
	for (TArray<class UEdGraphPin*>::TConstIterator Links(InGraphPin->LinkedTo); Links; ++Links)
	{
		UEdGraphPin* Pin = *Links;
		FString TitleString = Pin->GetOwningNode()->GetNodeTitle(ENodeTitleType::ListView).ToString();
		FText Title = FText::FromString(TitleString);
		if (Pin->PinName != TEXT(""))
		{
			TitleString = FString::Printf(TEXT("%s (%s)"), *TitleString, *Pin->PinName.ToString());

			// Add name of connection if possible
			FFormatNamedArguments Args;
			Args.Add(TEXT("NodeTitle"), Title);
			Args.Add(TEXT("PinName"), Pin->GetDisplayName());
			Title = FText::Format(LOCTEXT("BreakDescPin", "{NodeTitle} ({PinName})"), Args);
		}

		uint32& Count = LinkTitleCount.FindOrAdd(TitleString);

		FText Description;
		FFormatNamedArguments Args;
		Args.Add(TEXT("NodeTitle"), Title);
		Args.Add(TEXT("NumberOfNodes"), Count);

		if (Count == 0)
		{
			Description = FText::Format(LOCTEXT("BreakDesc", "Break link to {NodeTitle}"), Args);
		}
		else
		{
			Description = FText::Format(LOCTEXT("BreakDescMulti", "Break link to {NodeTitle} ({NumberOfNodes})"), Args);
		}
		++Count;

		Section.AddMenuEntry(NAME_None, Description, Description, FSlateIcon(), FUIAction(
			FExecuteAction::CreateUObject(this, &UDialogueEdGraphSchema::BreakSinglePinLink, const_cast<UEdGraphPin*>(InGraphPin), *Links)));
	}
}

EGraphType UDialogueEdGraphSchema::GetGraphType(const UEdGraph* TestEdGraph) const
{
	return GT_StateMachine;
}

void UDialogueEdGraphSchema::GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{

	if (Context->Node)
	{
		{
			FToolMenuSection& Section = Menu->AddSection("DialogueGraphSchemaNodeActions", LOCTEXT("ClassActionsMenuHeader", "Node Actions"));
			Section.AddMenuEntry(FGenericCommands::Get().Delete);
			Section.AddMenuEntry(FGenericCommands::Get().Cut);
			Section.AddMenuEntry(FGenericCommands::Get().Copy);
			Section.AddMenuEntry(FGenericCommands::Get().Duplicate);

			Section.AddMenuEntry(FGraphEditorCommands::Get().BreakNodeLinks);

			if (Context->Node->bCanRenameNode)
			{
				Section.AddMenuEntry(FGenericCommands::Get().Rename);
			}
		}
	}

	Super::GetContextMenuActions(Menu, Context);
}

const FPinConnectionResponse UDialogueEdGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const // TODO to review 
{
	// Make sure the pins are not on the same node
	if (A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorSameNode", "Both are on the same node"));
	}

	// Compare the directions
	if ((A->Direction == EGPD_Input) && (B->Direction == EGPD_Input))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorInput", "Can't connect input node to input node"));
	}

	UDialogueEdNode* EdNode_A = Cast<UDialogueEdNode>(A->GetOwningNode());
	UDialogueEdNode* EdNode_B = Cast<UDialogueEdNode>(B->GetOwningNode());

	if (EdNode_A == nullptr || EdNode_B == nullptr)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinError", "Not a valid UDialogueEdNode"));
	}

	if (A->Direction == EGPD_Output && B->Direction == EGPD_Output && (EdNode_B->DialogueNode->IsRootNode()))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinError", "Can't connect to root node"));
	}

	if ((A->Direction == EGPD_Input && EdNode_A->DialogueNode->IsRootNode()) || (B->Direction == EGPD_Input && EdNode_B->DialogueNode->IsRootNode()))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinErrorOutput", "Can't connect input to root node"));
	}

	if (EdNode_A->IsConnectedTo(EdNode_B))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("PinError", "Already connected"));
	}

	const bool bPinAIsTransition = A->GetOwningNode()->IsA(UDialogueEdEdge::StaticClass());
	const bool bPinBIsTransition = B->GetOwningNode()->IsA(UDialogueEdEdge::StaticClass());

	if (bPinAIsTransition && bPinBIsTransition)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Cannot wire a transition to a transition"));
	}

	if (bPinAIsTransition)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_A, TEXT(""));
	}
	else if (bPinBIsTransition)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_B, TEXT(""));
	}
	else if (!bPinAIsTransition && !bPinBIsTransition)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE, TEXT("Create an edge"));
	}
	else
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
	}
}

void UDialogueEdGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	UDialogueGraph* Graph = CastChecked<UDialogueGraph>(ContextMenuBuilder.CurrentGraph->GetOuter());

	const bool bNoParent = (ContextMenuBuilder.FromPin == NULL);

	TSharedPtr<FDialogueAssetSchemaAction_NewSceneNode> NewSceneNodeAction(new FDialogueAssetSchemaAction_NewSceneNode(LOCTEXT("DialogueGraphSceneNodeAction", "Dialogue Graph Scene Node"), LOCTEXT("AddSceneNode", "Add Scene Node..."), LOCTEXT("AddSceneNodeTooltip", "A new scene node"),0));
	ContextMenuBuilder.AddAction(NewSceneNodeAction);
	NewSceneNodeAction->NodeTemplate = NewObject<UDialogueEdNode>(ContextMenuBuilder.OwnerOfTemporaries);
	NewSceneNodeAction->NodeTemplate->NodeClass = USceneDialogueNode::StaticClass();

	TSharedPtr<FDialogueAssetSchemaAction_NewInteractiveNode> NewInteractiveNodeAction(new FDialogueAssetSchemaAction_NewInteractiveNode(LOCTEXT("DialogueGraphInteractiveNodeAction", "Dialogue Graph Interactive Node"), LOCTEXT("AddInteractiveNode", "Add Interactive Node..."), LOCTEXT("AddInteractiveNodeTooltip", "A new interactive node"), 1));
	ContextMenuBuilder.AddAction(NewInteractiveNodeAction);
	NewInteractiveNodeAction->NodeTemplate = NewObject<UDialogueEdNode>(ContextMenuBuilder.OwnerOfTemporaries);
	NewInteractiveNodeAction->NodeTemplate->NodeClass = UInteractiveDialogueNode::StaticClass();
}

bool UDialogueEdGraphSchema::CreateAutomaticConversionNodeAndConnections(UEdGraphPin* A, UEdGraphPin* B) const
{
	UDialogueEdNode* NodeA = Cast<UDialogueEdNode>(A->GetOwningNode());
	UDialogueEdNode* NodeB = Cast<UDialogueEdNode>(B->GetOwningNode());

	if (NodeA == nullptr || NodeB == nullptr)
		return false;

	if (NodeA->GetInputPin() == nullptr || NodeA->GetOutputPin() == nullptr || NodeB->GetInputPin() == nullptr || NodeB->GetOutputPin() == nullptr)
		return false;

	FVector2D InitPos((NodeA->NodePosX + NodeB->NodePosX) / 2, (NodeA->NodePosY + NodeB->NodePosY) / 2);

	FDialogueAssetSchemaAction_NewEdge Action;
	Action.NodeTemplate = NewObject<UDialogueEdEdge>(NodeA->GetGraph());
	Action.NodeTemplate->DialogueEdge = NewObject<UDialogueEdge>(Action.NodeTemplate);
	UDialogueEdEdge* EdgeNode = Cast<UDialogueEdEdge>(Action.PerformAction(NodeA->GetGraph(), nullptr, InitPos, false));

	if (A->Direction == EGPD_Output)
	{
		EdgeNode->CreateConnections(NodeA, NodeB);
	}
	else
	{
		EdgeNode->CreateConnections(NodeB, NodeA);
	}

	return true;
}

class FConnectionDrawingPolicy* UDialogueEdGraphSchema::CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const
{
	return new FDialogueGraphConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
}

FLinearColor UDialogueEdGraphSchema::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return FColor::White;
}

void UDialogueEdGraphSchema::BreakNodeLinks(UEdGraphNode& TargetNode) const
{
	const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "GraphEd_BreakNodeLinks", "Break Node Links"));

	Super::BreakNodeLinks(TargetNode);
}

void UDialogueEdGraphSchema::BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const
{
	const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "GraphEd_BreakPinLinks", "Break Pin Links"));

	Super::BreakPinLinks(TargetPin, bSendsNodeNotifcation);
}

void UDialogueEdGraphSchema::BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const
{
	const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "GraphEd_BreakSinglePinLink", "Break Pin Link"));

	Super::BreakSinglePinLink(SourcePin, TargetPin);
}

bool UDialogueEdGraphSchema::IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const
{
	return UDialogueEdGraphSchema::CurrentCacheRefreshID != InVisualizationCacheID;
}

int32 UDialogueEdGraphSchema::GetCurrentVisualizationCacheID() const
{
	return UDialogueEdGraphSchema::CurrentCacheRefreshID;
}

void UDialogueEdGraphSchema::ForceVisualizationCacheClear() const
{
	UDialogueEdGraphSchema::CurrentCacheRefreshID++;
}

#undef LOCTEXT_NAMESPACE