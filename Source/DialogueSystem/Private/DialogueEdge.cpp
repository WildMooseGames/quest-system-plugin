#include "DialogueEdge.h"
#include "QuestEventSubsystem.h"
#include "DialogueGraph.h"
#include "DialogueNode_Base.h"

UDialogueNode_Base* UDialogueEdge::GetOriginNode() const
{
	return OriginNode;
}

UDialogueNode_Base* UDialogueEdge::GetDestinationNode() const
{
	return DestinationNode; 
}

bool UDialogueEdge::CanMakeTransition() const
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();

	if (ensure(GameInstance))
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (ensure(QuestEventSS))
		{
			for (auto Condition : QuestEventConditions_Bool)
			{
				FQuestEventResult_Bool QuestEventResult = QuestEventSS->GetEventValue_Bool(Condition.Key); 

				if (!QuestEventResult.bIsValid || QuestEventResult.Value != Condition.Value)
				{
					return false; 
				}
			}

			for (auto Condition : QuestEventConditions_Int)
			{
				FQuestEventResult_Int QuestEventResult = QuestEventSS->GetEventValue_Int(Condition.Key);

				if (!QuestEventResult.bIsValid || QuestEventResult.Value != Condition.Value)
				{
					return false;
				}
			}

			for (auto Condition : QuestEventConditions_String)
			{
				FQuestEventResult_String QuestEventResult = QuestEventSS->GetEventValue_String(Condition.Key);

				if (!QuestEventResult.bIsValid || QuestEventResult.Value != Condition.Value)
				{
					return false;
				}
			}

			return true; 
		}
	}

	return false; 
}

void UDialogueEdge::DoTransition()
{
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();

	if (ensure(GameInstance))
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (ensure(QuestEventSS))
		{
			Graph->TriggerOnDialogueEvent(OnTransitionEvent);

			for (auto QuestEvent : OnTransitionQuestEvent_Bool)
			{
				QuestEventSS->SetEventValue_Bool(QuestEvent.Event.Key, QuestEvent.Event.Value);

				if (QuestEvent.bIsTemp) 
				{
					Graph->RegisterTempEvent(FQuestEventData(QuestEvent.Event.Key, EQuestEventType::BOOL));
				}
			}

			for (auto QuestEvent : OnTransitionQuestEvent_Int)
			{
				QuestEventSS->SetEventValue_Int(QuestEvent.Event.Key, QuestEvent.Event.Value);

				if (QuestEvent.bIsTemp) 
				{
					Graph->RegisterTempEvent(FQuestEventData(QuestEvent.Event.Key, EQuestEventType::INT));
				}
			}

			for (auto QuestEvent : OnTransitionQuestEvent_String)
			{
				QuestEventSS->SetEventValue_String(QuestEvent.Event.Key, QuestEvent.Event.Value);

				if (QuestEvent.bIsTemp) // if temp event
				{
					Graph->RegisterTempEvent(FQuestEventData(QuestEvent.Event.Key, EQuestEventType::STRING));
				}
			}
		}
	}
}