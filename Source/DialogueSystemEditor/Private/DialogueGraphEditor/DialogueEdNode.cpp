#include "DialogueEdNode.h"
#include "DialogueEdGraph.h"
#include "DialogueEdEdge.h"
#include "DialogueNode_Base.h"
#include "DialogueEdGraphSchema.h"
#include "DialogueRootNode.h"

UDialogueEdNode::UDialogueEdNode()
{
	DialogueNode = nullptr; 
}

UDialogueEdGraph* UDialogueEdNode::GetDialogueEdGraph()
{
	return Cast<UDialogueEdGraph>(GetGraph());
}

void UDialogueEdNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "MultipleNodes", TEXT("In"));
	CreatePin(EGPD_Output, "MultipleNodes", TEXT("Out"));
}

FText UDialogueEdNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(DialogueNode->GetNodeName());
}

void UDialogueEdNode::PrepareForCopying()
{
	if (DialogueNode)
	{
		// Temporarily take ownership of the node instance, so that it is not deleted when cutting
		DialogueNode->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
	}
}

void UDialogueEdNode::AutowireNewNode(UEdGraphPin* FromPin)
{
	Super::AutowireNewNode(FromPin);

	if (FromPin != nullptr)
	{
		UEdGraphPin* OutputPin = GetOutputPin();

		if (GetSchema()->TryCreateConnection(FromPin, GetInputPin()))
		{
			FromPin->GetOwningNode()->NodeConnectionListChanged();
		}
		else if (OutputPin != nullptr && GetSchema()->TryCreateConnection(OutputPin, FromPin))
		{
			NodeConnectionListChanged();
		}
	}
}

void UDialogueEdNode::PostPlacedNewNode()
{
	if (DialogueNode == nullptr)
	{
		UDialogueEdGraph* MyGraph = GetDialogueEdGraph();
		UObject* GraphOwner = MyGraph ? MyGraph->GetOuter() : nullptr;
		if (GraphOwner)
		{
			DialogueNode = Cast<UDialogueNode_Base>(NewObject<UObject>(GraphOwner, NodeClass)); 
			DialogueNode->SetFlags(RF_Transactional);
		}
	}
}

bool UDialogueEdNode::CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const
{
	return DesiredSchema->GetClass()->IsChildOf(UDialogueEdGraphSchema::StaticClass());
}

bool UDialogueEdNode::CanUserDeleteNode() const
{
	return !Cast<UDialogueRootNode>(DialogueNode); 
}

FLinearColor UDialogueEdNode::GetBackgroundColor() const
{
	if (DialogueNode)
	{
		return DialogueNode->GetBackgroundColor(); 
	}
	else
	{
		return FLinearColor::Black;
	}
}

void UDialogueEdNode::GetTransitionList(TArray<class UDialogueEdEdge*>& OutTransitions)
{
	for (int32 LinkIndex = 0; LinkIndex < Pins[1]->LinkedTo.Num(); ++LinkIndex)
	{
		UEdGraphNode* TargetNode = Pins[1]->LinkedTo[LinkIndex]->GetOwningNode();
		if (UDialogueEdEdge* Transition = Cast<UDialogueEdEdge>(TargetNode))
		{
			OutTransitions.Add(Transition);
		}
	}
}

bool UDialogueEdNode::IsConnectedTo(UDialogueEdNode* NodeToCheck)
{
	for (int32 LinkIndex = 0; LinkIndex < Pins[1]->LinkedTo.Num(); ++LinkIndex)
	{
		UEdGraphNode* TargetNode = Pins[1]->LinkedTo[LinkIndex]->GetOwningNode();
		if (UDialogueEdEdge* Transition = Cast<UDialogueEdEdge>(TargetNode))
		{
			if (Transition->GetEndNode() == NodeToCheck)
			{
				return true; 
			}
		}
	}

	return false; 
}