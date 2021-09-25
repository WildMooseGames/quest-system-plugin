#include "DialogueNode.h"
#include "QuestEventSubsystem.h"

FLinearColor UDialogueNode::GetBackgroundColor() const
{
	return FLinearColor(135,135,135,1);
}

void UDialogueNode::OnEnterNode()
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();

	if (!GameInstance)
		return;

	UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

	if (!QuestEventSS)
		return; 

	Graph->TriggerOnDialogueEvent(OnEnterNodeEvent);

	for (auto QuestEvent : OnEnterNodeQuestEvent_Bool)
	{
		QuestEventSS->SetEventValue_Bool(QuestEvent.Event.Key, QuestEvent.Event.Value);

		if (QuestEvent.bIsTemp)
		{
			Graph->RegisterTempEvent(FQuestEventData(QuestEvent.Event.Key, EQuestEventType::BOOL)); 
		}
	}

	for (auto QuestEvent : OnEnterNodeQuestEvent_Int)
	{
		QuestEventSS->SetEventValue_Int(QuestEvent.Event.Key, QuestEvent.Event.Value);

		if (QuestEvent.bIsTemp) 
		{
			Graph->RegisterTempEvent(FQuestEventData(QuestEvent.Event.Key, EQuestEventType::INT));
		}
	}

	for (auto QuestEvent : OnEnterNodeQuestEvent_String)
	{
		QuestEventSS->SetEventValue_String(QuestEvent.Event.Key, QuestEvent.Event.Value);

		if (QuestEvent.bIsTemp) 
		{
			Graph->RegisterTempEvent(FQuestEventData(QuestEvent.Event.Key, EQuestEventType::STRING));
		}
	}
}

FString UDialogueNode::GetNodeName() const
{
	return NodeName; 
}
