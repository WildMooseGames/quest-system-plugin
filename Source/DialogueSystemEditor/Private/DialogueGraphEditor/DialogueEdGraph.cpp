#include "DialogueEdGraph.h"
#include "DialogueEdNode.h"
#include "DialogueGraph.h"
#include "DialogueEdEdge.h"
#include "DialogueNode_Base.h"
#include "DialogueEdge.h"
#include "DialogueRootNode.h"
#include "DialogueNode.h"
#include "GraphEditAction.h"

UDialogueEdGraph::UDialogueEdGraph()
{
	//UpdateAssetOnGraphChangedHandler.
	UpdateAssetOnGraphChangedHandler.BindLambda([&](const FEdGraphEditAction& GraphAction)
		{
			UpdateAsset();
		});
		
		//BindUFunction(this, FName("UpdateAssetGraphOnChanged")); 
	//AddOnGraphChangedHandler(UpdateAssetOnGraphChangedHandler);
}

void UDialogueEdGraph::UpdateAsset()
{

	UDialogueGraph* Graph = GetDialogueGraph();

	Clear();

	for (int i = 0; i < Nodes.Num(); ++i)
	{
		if (UDialogueEdNode* EdNode = Cast<UDialogueEdNode>(Nodes[i]))
		{
			if (EdNode->DialogueNode == nullptr)
				continue;

			UDialogueNode_Base* DialogueNode = EdNode->DialogueNode;
			
			Graph->Nodes.Add(DialogueNode); 

			if (UDialogueRootNode* MyRootNode = Cast<UDialogueRootNode>(DialogueNode))
			{
				Graph->RootNode = MyRootNode;
			}

		}
		else if (UDialogueEdEdge* EdgeNode = Cast<UDialogueEdEdge>(Nodes[i]))
		{
			UDialogueEdNode* StartNode = EdgeNode->GetStartNode();
			UDialogueEdNode* EndNode = EdgeNode->GetEndNode();
			UDialogueEdge* Edge = EdgeNode->DialogueEdge;

			if (StartNode == nullptr || EndNode == nullptr || Edge == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("UEdGraph_GenericGraph::RebuildGenericGraph add edge failed."))
				continue;
			}

			Edge->Graph = Graph;
			Edge->Rename(nullptr, Graph, REN_DontCreateRedirectors | REN_DoNotDirty);
			Edge->OriginNode = StartNode->DialogueNode;
			Edge->DestinationNode = EndNode->DialogueNode;
			Edge->OriginNode->OutEdges.Add(Edge);

			if (UDialogueNode* Node = Cast<UDialogueNode>(Edge->DestinationNode))
			{
				Node->InEdges.Add(Edge);
			}
		}
	}

	for (int i = 0; i < Graph->Nodes.Num(); ++i)
	{
		UDialogueNode_Base* Node = Graph->Nodes[i];

		Node->Graph = Graph;
		Node->SortOutEdges();
		Node->Rename(nullptr, Graph, REN_DontCreateRedirectors | REN_DoNotDirty);
	}
}

void UDialogueEdGraph::SetRootNode(UDialogueEdNode* pRootNode)
{
	if (UDialogueRootNode* InternalRootNode = Cast<UDialogueRootNode>(pRootNode->DialogueNode))
	{
		RootNode = pRootNode;

		UDialogueGraph* Graph = GetDialogueGraph();
		Graph->RootNode = InternalRootNode;
	}
}


UDialogueGraph* UDialogueEdGraph::GetDialogueGraph() const
{
	return CastChecked<UDialogueGraph>(GetOuter());
}

void UDialogueEdGraph::PostEditUndo()
{
	Super::PostEditUndo();

	NotifyGraphChanged();
}

bool UDialogueEdGraph::Modify(bool bAlwaysMarkDirty /*= true*/)
{
	bool Rtn = Super::Modify(bAlwaysMarkDirty);

	GetDialogueGraph()->Modify();

	for (int32 i = 0; i < Nodes.Num(); ++i)
	{
		Nodes[i]->Modify();
	}

	return Rtn;
}

void UDialogueEdGraph::Clear()
{
	UDialogueGraph* Graph = GetDialogueGraph();

	Graph->RootNode = nullptr;
	Graph->Nodes.Empty();

	for (int i = 0; i < Nodes.Num(); ++i)
	{
		if (UDialogueEdNode* EdNode = Cast<UDialogueEdNode>(Nodes[i]))
		{
			UDialogueNode_Base* DialogueNodeBase = EdNode->DialogueNode;
			DialogueNodeBase->OutEdges.Reset();

			if (UDialogueNode* DialogueNode = Cast<UDialogueNode>(DialogueNodeBase))
			{
				DialogueNode->InEdges.Reset();
			}
		}
	}
}