#include "DialogueGraph.h"
#include "DialogueNode_Base.h"
#include "DialogueRootNode.h"
#include "DialogueEdge.h"
#include "SceneDialogueNode.h"
#include "InteractiveDialogueNode.h"
#include "QuestEventSubsystem.h"


UWorld* UDialogueGraph::GetWorld() const
{
	return Owner->GetWorld(); 
}

void UDialogueGraph::Initialize()
{
	for (UDialogueNode_Base* Node_Base : Nodes)
	{
		if (UDialogueNode* Node = Cast<UDialogueNode>(Node_Base))
		{
			for (UDialogueEdge* InEdge : Node->InEdges)
			{
				InEdge->DestinationNode = Node; 
			}

			for (UDialogueEdge* OutEdge : Node->OutEdges)
			{
				OutEdge->OriginNode = Node;
			}
		}
	}
}

FDialogueNodeWrapper UDialogueGraph::StartDialogue(UObject* pOwner)
{
	if (!Owner)
	{
		Owner = pOwner;
	}

	if (RootNode)
	{
		CurrentNode = RootNode; 

		return GetNextNode(); 
	}

	return FDialogueNodeWrapper();
}

void UDialogueGraph::EndDialogue()
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance(); 

	if (!GameInstance)
		return; 


	UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>(); 

	if (QuestEventSS)
	{
		for (FQuestEventData TempEvent : TempEvents)
		{
			QuestEventSS->ClearEventValue(TempEvent); 
		}
	}

	CurrentNode = nullptr;
	CurrentHistoryIndex = 0;
	TempEvents.Empty();
	 DialogueHistory.Empty();

}


FDialogueNodeWrapper UDialogueGraph::GetNextNode()
{
	if (CurrentNode && !CurrentNode->IsEndNode())
	{
		DialogueHistory.Add(CurrentNode); 

		CurrentNode = CurrentNode->GetNextNode();

		if (Cast<USceneDialogueNode>(CurrentNode))
		{
			return FDialogueNodeWrapper(CurrentNode, EDialogueSceneType::SCENE);
		}
		else if (Cast<UInteractiveDialogueNode>(CurrentNode))
		{
			return FDialogueNodeWrapper(CurrentNode, EDialogueSceneType::INTERACTIVE);
		}
	}

	return FDialogueNodeWrapper();
}

FDialogueNodeWrapper UDialogueGraph::GetPreviousNode()
{
	if (CurrentHistoryIndex != 0 && DialogueHistory.IsValidIndex(CurrentHistoryIndex))
	{
		UDialogueNode_Base* PreviousNode =  DialogueHistory[CurrentHistoryIndex];

		if (Cast<USceneDialogueNode>(PreviousNode))
		{
			return FDialogueNodeWrapper(PreviousNode, EDialogueSceneType::SCENE);
		}
		else if (Cast<UInteractiveDialogueNode>(PreviousNode))
		{
			return FDialogueNodeWrapper(PreviousNode, EDialogueSceneType::INTERACTIVE);
		}
	}

	return FDialogueNodeWrapper();
}

void UDialogueGraph::RegisterTempEvent(FQuestEventData EventData)
{
	TempEvents.Add(EventData);
}

void UDialogueGraph::TriggerOnDialogueEvent(FString EventKey)
{
	OnDialogueEvent.Broadcast(EventKey); 
}