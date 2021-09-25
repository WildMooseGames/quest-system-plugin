// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestEventSubsystem.h"

FQuestEventResult_Bool UQuestEventSubsystem::GetEventValue_Bool(FString EventKey) const
{
	if (QuestEvents_Bool.Contains(EventKey))
	{
		FQuestEventResult_Bool Result = FQuestEventResult_Bool(QuestEvents_Bool[EventKey], true);

		return Result;
	}
	else
	{
		return FQuestEventResult_Bool();
	}
}

FQuestEventResult_Int UQuestEventSubsystem::GetEventValue_Int(FString EventKey) const
{
	if (QuestEvents_Int.Contains(EventKey))
	{
		FQuestEventResult_Int Result = FQuestEventResult_Int(QuestEvents_Int[EventKey], true);

		return Result;
	}
	else
	{
		return FQuestEventResult_Int();
	}
}

FQuestEventResult_String UQuestEventSubsystem::GetEventValue_String(FString EventKey) const
{
	if (QuestEvents_String.Contains(EventKey))
	{
		FQuestEventResult_String Result = FQuestEventResult_String(QuestEvents_String[EventKey], true);

		return Result;
	}
	else
	{
		return FQuestEventResult_String();
	}
}

void UQuestEventSubsystem::SetEventValue_Bool(FString EventKey, bool bNewValue)
{
	FQuestEventResult_Bool OldValue = QuestEvents_Bool.Contains(EventKey) ? FQuestEventResult_Bool(QuestEvents_Bool[EventKey], true) : FQuestEventResult_Bool();

	QuestEvents_Bool.Add(EventKey, bNewValue);

	TArray<FQuestEventDelegate_Bool> EventObservers;

	EventObservers_Bool.MultiFind(EventKey, EventObservers);

	for (auto Observer : EventObservers)
	{
		if (Observer.IsBound())
		{
			Observer.Execute(EventKey, OldValue, bNewValue);
		}
	}
}

void UQuestEventSubsystem::SetEventValue_Int(FString EventKey, uint8 NewValue)
{
	FQuestEventResult_Int OldValue = QuestEvents_Int.Contains(EventKey) ? FQuestEventResult_Int(QuestEvents_Int[EventKey], true) : FQuestEventResult_Int();

	QuestEvents_Int.Add(EventKey, NewValue);

	TArray<FQuestEventDelegate_Int> EventObservers;

	EventObservers_Int.MultiFind(EventKey, EventObservers);

	for (auto Observer : EventObservers)
	{
		if (Observer.IsBound())
		{
			Observer.Execute(EventKey, OldValue, NewValue);
		}
	}
}

void UQuestEventSubsystem::SetEventValue_String(FString EventKey, FString NewValue)
{
	FQuestEventResult_String OldValue = QuestEvents_String.Contains(EventKey) ? FQuestEventResult_String(QuestEvents_String[EventKey], true) : FQuestEventResult_String();

	QuestEvents_String.Add(EventKey, NewValue);

	TArray<FQuestEventDelegate_String> EventObservers;

	EventObservers_String.MultiFind(EventKey, EventObservers);

	for (auto Observer : EventObservers)
	{
		if (Observer.IsBound())
		{
			Observer.Execute(EventKey, OldValue, NewValue);
		}
	}
}

void UQuestEventSubsystem::ClearEventValue(FQuestEventData EventData)
{
	switch (EventData.Type)
	{
	case EQuestEventType::BOOL:
	{
		ClearEventValue_Bool(EventData.Key);
		break;
	}
	case EQuestEventType::INT:
	{
		ClearEventValue_Int(EventData.Key);
			break;
	}
	case EQuestEventType::STRING:
	{
		ClearEventValue_String(EventData.Key);
			break;
	}
	}
}

void UQuestEventSubsystem::ClearEventValue_Bool(FString EventKey)
{
	if (QuestEvents_Bool.Contains(EventKey))
	{
		QuestEvents_Bool.Remove(EventKey);
	}
}

void UQuestEventSubsystem::ClearEventValue_Int(FString EventKey)
{
	if (QuestEvents_Int.Contains(EventKey))
	{
		QuestEvents_Int.Remove(EventKey);
	}
}

void UQuestEventSubsystem::ClearEventValue_String(FString EventKey)
{
	if (QuestEvents_String.Contains(EventKey))
	{
		QuestEvents_String.Remove(EventKey); 
	}
}

void UQuestEventSubsystem::RegisterToEvent_Bool(FString EventKey, FQuestEventDelegate_Bool EventDelegate)
{
	EventObservers_Bool.AddUnique(EventKey, EventDelegate);
}

void UQuestEventSubsystem::RegisterToEvent_Int(FString EventKey, FQuestEventDelegate_Int EventDelegate)
{
	EventObservers_Int.AddUnique(EventKey, EventDelegate);
}

void UQuestEventSubsystem::RegisterToEvent_String(FString EventKey, FQuestEventDelegate_String EventDelegate)
{
	EventObservers_String.AddUnique(EventKey, EventDelegate);
}

void UQuestEventSubsystem::UnregisterToEvent_Bool(FString EventKey, FQuestEventDelegate_Bool EventDelegate)
{
	EventObservers_Bool.Remove(EventKey, EventDelegate);
}

void UQuestEventSubsystem::UnregisterToEvent_Int(FString EventKey, FQuestEventDelegate_Int EventDelegate)
{
	EventObservers_Int.Remove(EventKey, EventDelegate);
}

void UQuestEventSubsystem::UnregisterToEvent_String(FString EventKey, FQuestEventDelegate_String EventDelegate)
{
	EventObservers_String.Remove(EventKey, EventDelegate);
}

const TMap<FString, bool>& UQuestEventSubsystem::GetQuestEvents_Bool() const
{
	return QuestEvents_Bool;
}

const TMap<FString, uint8>& UQuestEventSubsystem::GetQuestEvents_Int() const
{
	return QuestEvents_Int;
}

const TMap<FString, FString>& UQuestEventSubsystem::GetQuestEvents_String() const
{
	return QuestEvents_String;
}

void UQuestEventSubsystem::LoadEvents(const TMap<FString, bool>& pQuestEvents_Bool, const TMap<FString, uint8>& pQuestEvents_Int, const TMap<FString, FString>& pQuestEvents_String)
{
	if (pQuestEvents_Bool.Num() > 0)
		QuestEvents_Bool.Append(pQuestEvents_Bool);
	
	if (pQuestEvents_Int.Num() > 0)
		QuestEvents_Int.Append(pQuestEvents_Int);

	if (pQuestEvents_String.Num() > 0)
		QuestEvents_String.Append(pQuestEvents_String);
}

void UQuestEventSubsystem::SaveEvents(TMap<FString, bool>& OutQuestEvents_Bool, TMap<FString, uint8>& OutQuestEvents_Int, TMap<FString, FString>& OutQuestEvents_String)
{
	if (QuestEvents_Bool.Num() > 0)
		OutQuestEvents_Bool.Append(QuestEvents_Bool);

	if (QuestEvents_Int.Num() > 0)
		OutQuestEvents_Int.Append(QuestEvents_Int);

	if (QuestEvents_String.Num() > 0)
		OutQuestEvents_String.Append(QuestEvents_String);
}