#include "QuestEventUtility.h"

FQuestEventResult_Bool UQuestEventUtility::GetEventValue_Bool(UObject* WorldContextObject, FString EventKey)
{
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();

	if (GameInstance)
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (QuestEventSS)
		{
			return QuestEventSS->GetEventValue_Bool(EventKey); 
		}
	}

	return FQuestEventResult_Bool(); 
}

FQuestEventResult_Int UQuestEventUtility::GetEventValue_Int(UObject* WorldContextObject, FString EventKey)
{
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();

	if (GameInstance)
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (QuestEventSS)
		{
			return QuestEventSS->GetEventValue_Int(EventKey);
		}
	}

	return FQuestEventResult_Int();
}

FQuestEventResult_String UQuestEventUtility::GetEventValue_String(UObject* WorldContextObject, FString EventKey)
{
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();

	if (GameInstance)
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (QuestEventSS)
		{
			return QuestEventSS->GetEventValue_String(EventKey);
		}
	}

	return FQuestEventResult_String();
}

void UQuestEventUtility::SetEventValue_Bool(UObject* WorldContextObject, FString EventKey, bool bNewValue)
{
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();

	if (GameInstance)
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (QuestEventSS)
		{
			QuestEventSS->SetEventValue_Bool(EventKey,bNewValue);
		}
	}
}

void UQuestEventUtility::SetEventValue_Int(UObject* WorldContextObject, FString EventKey, uint8 NewValue)
{
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();

	if (GameInstance)
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (QuestEventSS)
		{
			QuestEventSS->SetEventValue_Int(EventKey, NewValue);
		}
	}
}

void UQuestEventUtility::SetEventValue_String(UObject* WorldContextObject, FString EventKey, FString NewValue)
{
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();

	if (GameInstance)
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (QuestEventSS)
		{
			QuestEventSS->SetEventValue_String(EventKey, NewValue);
		}
	}
}

void UQuestEventUtility::ClearEventValue(UObject* WorldContextObject, FQuestEventData EventData)
{
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();

	if (GameInstance)
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (QuestEventSS)
		{
			QuestEventSS->ClearEventValue(EventData);
		}
	}
}

void UQuestEventUtility::ClearEventValue_String(UObject* WorldContextObject, FString EventKey)
{
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();

	if (GameInstance)
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (QuestEventSS)
		{
			QuestEventSS->ClearEventValue_String(EventKey);
		}
	}
}

void UQuestEventUtility::ClearEventValue_Bool(UObject* WorldContextObject, FString EventKey)
{
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();

	if (GameInstance)
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (QuestEventSS)
		{
			QuestEventSS->ClearEventValue_Bool(EventKey);
		}
	}
}

void UQuestEventUtility::ClearEventValue_Int(UObject* WorldContextObject, FString EventKey)
{
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();

	if (GameInstance)
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (QuestEventSS)
		{
			QuestEventSS->ClearEventValue_Int(EventKey);
		}
	}
}

void UQuestEventUtility::RegisterToEvent_Bool(UObject* WorldContextObject, FString EventKey, FQuestEventDelegate_Bool EventDelegate)
{
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();

	if (GameInstance)
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (QuestEventSS)
		{
			QuestEventSS->RegisterToEvent_Bool(EventKey, EventDelegate);
		}
	}
}

void UQuestEventUtility::RegisterToEvent_Int(UObject* WorldContextObject, FString EventKey, FQuestEventDelegate_Int EventDelegate)
{
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();

	if (GameInstance)
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (QuestEventSS)
		{
			QuestEventSS->RegisterToEvent_Int(EventKey, EventDelegate);
		}
	}
}

void UQuestEventUtility::RegisterToEvent_String(UObject* WorldContextObject, FString EventKey, FQuestEventDelegate_String EventDelegate)
{
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();

	if (GameInstance)
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (QuestEventSS)
		{
			QuestEventSS->RegisterToEvent_String(EventKey, EventDelegate);
		}
	}
}

void UQuestEventUtility::UnregisterToEvent_Bool(UObject* WorldContextObject, FString EventKey, FQuestEventDelegate_Bool EventDelegate)
{
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();

	if (GameInstance)
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (QuestEventSS)
		{
			QuestEventSS->UnregisterToEvent_Bool(EventKey, EventDelegate);
		}
	}
}

void UQuestEventUtility::UnregisterToEvent_Int(UObject* WorldContextObject, FString EventKey, FQuestEventDelegate_Int EventDelegate)
{
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();

	if (GameInstance)
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (QuestEventSS)
		{
			QuestEventSS->UnregisterToEvent_Int(EventKey, EventDelegate);
		}
	}
}

void UQuestEventUtility::UnregisterToEvent_String(UObject* WorldContextObject, FString EventKey, FQuestEventDelegate_String EventDelegate)
{
	UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();

	if (GameInstance)
	{
		UQuestEventSubsystem* QuestEventSS = GameInstance->GetSubsystem<UQuestEventSubsystem>();

		if (QuestEventSS)
		{
			QuestEventSS->UnregisterToEvent_String(EventKey, EventDelegate);
		}
	}
}