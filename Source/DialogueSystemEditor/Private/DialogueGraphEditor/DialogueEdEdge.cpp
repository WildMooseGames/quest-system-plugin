#include "DialogueEdEdge.h"
#include "DialogueEdNode.h"

UDialogueEdEdge::UDialogueEdEdge()
{
	DialogueEdge = nullptr; 
}

void UDialogueEdEdge::AllocateDefaultPins()
{
	UEdGraphPin* Inputs = CreatePin(EGPD_Input, TEXT("Edge"), FName(), TEXT("In"));
	Inputs->bHidden = true;
	UEdGraphPin* Outputs = CreatePin(EGPD_Output, TEXT("Edge"), FName(), TEXT("Out"));
	Outputs->bHidden = true;
}


FText UDialogueEdEdge::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText();
}

void UDialogueEdEdge::PinConnectionListChanged(UEdGraphPin* Pin)
{
	if (Pin->LinkedTo.Num() == 0)
	{
		//  transitions must always have an input and output connection
		Modify();

		// Our parent graph will have our graph in SubGraphs so needs to be modified to record that.
		if (UEdGraph* ParentGraph = GetGraph())
		{
			ParentGraph->Modify();
		}

		DestroyNode();
	}
}

void UDialogueEdEdge::PrepareForCopying()
{
	if (DialogueEdge)
	{
		// Temporarily take ownership of the node instance, so that it is not deleted when cutting
		DialogueEdge->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
	}
}

UDialogueEdNode* UDialogueEdEdge::GetStartNode()
{
	if (Pins[0]->LinkedTo.Num() > 0)
	{
		return Cast<UDialogueEdNode>(Pins[0]->LinkedTo[0]->GetOwningNode());
	}
	else
	{
		return nullptr;
	}
}

UDialogueEdNode* UDialogueEdEdge::GetEndNode()
{
	if (Pins[1]->LinkedTo.Num() > 0)
	{
		return Cast<UDialogueEdNode>(Pins[1]->LinkedTo[0]->GetOwningNode());
	}
	else
	{
		return nullptr;
	}
}

void UDialogueEdEdge::CreateConnections(UDialogueEdNode* Start, UDialogueEdNode* End)
{
	Pins[0]->Modify();
	Pins[0]->LinkedTo.Empty();

	Start->GetOutputPin()->Modify();
	Pins[0]->MakeLinkTo(Start->GetOutputPin());

	// This to next
	Pins[1]->Modify();
	Pins[1]->LinkedTo.Empty();

	End->GetInputPin()->Modify();
	Pins[1]->MakeLinkTo(End->GetInputPin());
}