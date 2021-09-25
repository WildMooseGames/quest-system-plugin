#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestEventTypes.h"
#include "QuestEventSubsystem.generated.h"

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FQuestEventDelegate_Bool, FString, EventKey, FQuestEventResult_Bool, OldValue, bool, bValue);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FQuestEventDelegate_Int, FString, EventKey, FQuestEventResult_Int, OldValue, uint8, IntValue);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FQuestEventDelegate_String, FString, EventKey, FQuestEventResult_String, OldValue, FString, StringValue);

/**
 *
 */
UCLASS()
class QUESTEVENTSYSTEM_API UQuestEventSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

		friend class UGameInstance;

public:

	UFUNCTION(BlueprintCallable, Category = "Quest Event Manager")
		FQuestEventResult_Bool GetEventValue_Bool(FString EventKey) const;

	UFUNCTION(BlueprintCallable, Category = "Quest Event Manager")
		FQuestEventResult_Int GetEventValue_Int(FString EventKey) const;

	UFUNCTION(BlueprintCallable, Category = "Quest Event Manager")
		FQuestEventResult_String GetEventValue_String(FString EventKey) const;

	UFUNCTION(BlueprintCallable, Category = "Quest Event Manager")
		void SetEventValue_Bool(FString EventKey, bool bNewValue);

	UFUNCTION(BlueprintCallable, Category = "Quest Event Manager")
		void SetEventValue_Int(FString EventKey, uint8 NewValue);

	UFUNCTION(BlueprintCallable, Category = "Quest Event Manager")
		void SetEventValue_String(FString EventKey, FString NewValue);

	UFUNCTION(BlueprintCallable, Category = "Quest Event Manager")
		void ClearEventValue(FQuestEventData EventData);

	UFUNCTION(BlueprintCallable, Category = "Quest Event Manager")
		void ClearEventValue_String(FString EventKey);

	UFUNCTION(BlueprintCallable, Category = "Quest Event Manager")
		void ClearEventValue_Bool(FString EventKey);

	UFUNCTION(BlueprintCallable, Category = "Quest Event Manager")
		void ClearEventValue_Int(FString EventKey);

	void RegisterToEvent_Bool(FString EventKey, FQuestEventDelegate_Bool EventDelegate);

	void RegisterToEvent_Int(FString EventKey, FQuestEventDelegate_Int EventDelegate);

	void RegisterToEvent_String(FString EventKey, FQuestEventDelegate_String EventDelegate);

	void UnregisterToEvent_Bool(FString EventKey, FQuestEventDelegate_Bool EventDelegate);

	void UnregisterToEvent_Int(FString EventKey, FQuestEventDelegate_Int EventDelegate);

	void UnregisterToEvent_String(FString EventKey, FQuestEventDelegate_String EventDelegate);

	UFUNCTION(BlueprintCallable, Category = "Quest Event Manager")
		const TMap<FString, bool>& GetQuestEvents_Bool() const; 

	UFUNCTION(BlueprintCallable, Category = "Quest Event Manager")
		const TMap<FString, uint8>& GetQuestEvents_Int() const;

	UFUNCTION(BlueprintCallable, Category = "Quest Event Manager")
		const TMap<FString, FString>& GetQuestEvents_String() const;

	void LoadEvents(const TMap<FString, bool>& pQuestEvents_Bool, const TMap<FString, uint8>& pQuestEvents_Int, const TMap<FString, FString>& pQuestEvents_String);

	void SaveEvents(TMap<FString, bool>& OutQuestEvents_Bool, TMap<FString, uint8>& OutQuestEvents_Int, TMap<FString, FString>& OutQuestEvents_String);


private:

	UPROPERTY()
		TMap<FString, bool> QuestEvents_Bool;

	UPROPERTY()
		TMap<FString, uint8> QuestEvents_Int;

	UPROPERTY()
		TMap<FString, FString> QuestEvents_String;

	TMultiMap<FString, FQuestEventDelegate_Bool> EventObservers_Bool;

	TMultiMap<FString, FQuestEventDelegate_Int> EventObservers_Int;

	TMultiMap<FString, FQuestEventDelegate_String> EventObservers_String;

};
