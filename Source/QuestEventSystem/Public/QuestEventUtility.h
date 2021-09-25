#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuestEventTypes.h"
#include "QuestEventSubsystem.h"
#include "QuestEventUtility.generated.h"

UCLASS()
class QUESTEVENTSYSTEM_API UQuestEventUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:


	UFUNCTION(BlueprintCallable, Category = "Quest Event Utility")
		static FQuestEventResult_Bool GetEventValue_Bool(UObject* WorldContextObject, FString EventKey);

	UFUNCTION(BlueprintCallable, Category = "Quest Event Utility")
		static FQuestEventResult_Int GetEventValue_Int(UObject* WorldContextObject, FString EventKey);

	UFUNCTION(BlueprintCallable, Category = "Quest Event Utility")
		static FQuestEventResult_String GetEventValue_String(UObject* WorldContextObject, FString EventKey);

	UFUNCTION(BlueprintCallable, Category = "Quest Event Utility")
		static void SetEventValue_Bool(UObject* WorldContextObject, FString EventKey, bool bNewValue);

	UFUNCTION(BlueprintCallable, Category = "Quest Event Utility")
		static void SetEventValue_Int(UObject* WorldContextObject, FString EventKey, uint8 NewValue);

	UFUNCTION(BlueprintCallable, Category = "Quest Event Utility")
		static void SetEventValue_String(UObject* WorldContextObject, FString EventKey, FString NewValue);

	UFUNCTION(BlueprintCallable, Category = "Quest Event Utility")
		static void ClearEventValue(UObject* WorldContextObject, FQuestEventData EventData);

	UFUNCTION(BlueprintCallable, Category = "Quest Event Utility")
		static void ClearEventValue_String(UObject* WorldContextObject, FString EventKey);

	UFUNCTION(BlueprintCallable, Category = "Quest Event Utility")
		static void ClearEventValue_Bool(UObject* WorldContextObject, FString EventKey);

	UFUNCTION(BlueprintCallable, Category = "Quest Event Utility")
		static void ClearEventValue_Int(UObject* WorldContextObject, FString EventKey);

	static void RegisterToEvent_Bool(UObject* WorldContextObject, FString EventKey, FQuestEventDelegate_Bool EventDelegate);

	static void RegisterToEvent_Int(UObject* WorldContextObject, FString EventKey, FQuestEventDelegate_Int EventDelegate);

	static void RegisterToEvent_String(UObject* WorldContextObject, FString EventKey, FQuestEventDelegate_String EventDelegate);

	static void UnregisterToEvent_Bool(UObject* WorldContextObject, FString EventKey, FQuestEventDelegate_Bool EventDelegate);

	static void UnregisterToEvent_Int(UObject* WorldContextObject, FString EventKey, FQuestEventDelegate_Int EventDelegate);

	static void UnregisterToEvent_String(UObject* WorldContextObject, FString EventKey, FQuestEventDelegate_String EventDelegate);

};
