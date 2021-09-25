#include "DialogueNode_Base.h"
#include "DialogueEdge.h"
#include "QuestEventSubsystem.h"
#include "DialogueNode.h"


UWorld* UDialogueNode_Base::GetWorld() const
{

	if (Graph != nullptr)
	{
		return Graph->GetWorld(); 
	}
	else if (GetOuter() != nullptr)
	{
		return GetOuter()->GetWorld();
	}

	return nullptr; 
}

FString UDialogueNode_Base::GetNodeName() const
{
	return "None"; 
}

FLinearColor UDialogueNode_Base::GetBackgroundColor() const
{
	return FLinearColor::Black;
}

EDialogueSceneType UDialogueNode_Base::GetSceneType() const
{
	return EDialogueSceneType::NONE; 
}

bool UDialogueNode_Base::IsRootNode() const
{
	return false; 
}

bool UDialogueNode_Base::IsConnectedTo(UDialogueNode_Base* NodeToCheck)
{
	for (UDialogueEdge* Edge : OutEdges)
	{
		if (Edge->GetDestinationNode() == NodeToCheck)
		{
			return true; 
		}
	}

	return false; 
}

bool UDialogueNode_Base::IsEndNode() const
{
	return OutEdges.Num() == 0;
}

UDialogueNode_Base* UDialogueNode_Base::GetNextNode() 
{
	OnLeaveNode();

	if (IsEndNode())
		return this;

	bool bFound = false;
	int Index = 0;

	while (!bFound && Index < OutEdges.Num())
	{
		if (OutEdges[Index]->CanMakeTransition())
		{
			OutEdges[Index]->DoTransition();

			UDialogueNode_Base* NextNode = OutEdges[Index]->GetDestinationNode();

			if (UDialogueNode* NextDialogueNode = Cast<UDialogueNode>(NextNode))
			{
				NextDialogueNode->OnEnterNode();
			}

			bFound = true;

			return NextNode;
		}

		Index++;
	}

	return nullptr;
}

void UDialogueNode_Base::SortOutEdges()
{
	OutEdges.Sort([&](UDialogueEdge& A, UDialogueEdge& B)
		{
			return A.Priority < B.Priority;
		}
	);
}

void UDialogueNode_Base::OnLeaveNode()
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();

	if (!GameInstance)
		return;

	UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

	if (!QuestEventSS)
		return;

	Graph->TriggerOnDialogueEvent(OnLeaveNodeEvent);

	for (auto QuestEvent : OnLeaveNodeQuestEvent_Bool)
	{
		QuestEventSS->SetEventValue_Bool(QuestEvent.Event.Key, QuestEvent.Event.Value);

		if (QuestEvent.bIsTemp) 
		{
			Graph->RegisterTempEvent(FQuestEventData(QuestEvent.Event.Key, EQuestEventType::BOOL));
		}
	}

	for (auto QuestEvent : OnLeaveNodeQuestEvent_Int)
	{
		QuestEventSS->SetEventValue_Int(QuestEvent.Event.Key, QuestEvent.Event.Value);

		if (QuestEvent.bIsTemp) 
		{
			Graph->RegisterTempEvent(FQuestEventData(QuestEvent.Event.Key, EQuestEventType::INT));
		}
	}

	for (auto QuestEvent : OnLeaveNodeQuestEvent_String)
	{
		QuestEventSS->SetEventValue_String(QuestEvent.Event.Key, QuestEvent.Event.Value);

		if (QuestEvent.bIsTemp)
		{
			Graph->RegisterTempEvent(FQuestEventData(QuestEvent.Event.Key, EQuestEventType::STRING));
		}
	}
}