#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Misc/Optional.h"
#include "UObject/Object.h"
#include "QuestEventTypes.h"
#include "DialogueRootNode.h"
#include "DialogueSystemTypes.h"
#include "DialogueGraph.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogueGraphEvent, FString, EventKey);

class UDialogueNode_Base; 
class UDialogueEdge; 
class UDialogueRootNode; 


UCLASS(Blueprintable) 
class DIALOGUESYSTEM_API UDialogueGraph : public UObject
{

	GENERATED_BODY()

public:

	FDialogueGraphEvent OnDialogueEvent;

	UPROPERTY(EditDefaultsOnly, Category = "DialogueGraph")
		FString Name;

	UPROPERTY(VisibleDefaultsOnly, Category = "DialogueGraph")
		UDialogueRootNode* RootNode = nullptr;

	virtual UWorld* GetWorld() const override;

	void Initialize();

	UFUNCTION(BlueprintCallable, Category = "DialogueGraph")
		FDialogueNodeWrapper StartDialogue(UObject* pOwner);

	UFUNCTION(BlueprintCallable, Category = "DialogueGraph")
		void EndDialogue();

	UFUNCTION(BlueprintCallable, Category = "DialogueGraph")
		FDialogueNodeWrapper GetNextNode();

	UFUNCTION(BlueprintCallable, Category = "DialogueGraph")
		FDialogueNodeWrapper GetPreviousNode();

	UFUNCTION(BlueprintCallable, Category = "DialogueGraph")
		void RegisterTempEvent(FQuestEventData EventData);

	UFUNCTION(BlueprintCallable, Category = "DialogueGraph")
		void TriggerOnDialogueEvent(FString EventKey);

	UPROPERTY()
		TArray<UDialogueNode_Base*> Nodes ;

#if WITH_EDITORONLY_DATA

	/** Graph */
	UPROPERTY()
		class UEdGraph* DialogueEdGraph;

#endif

private:

	UPROPERTY()
		UObject* Owner = nullptr; 

	UPROPERTY()
		UDialogueNode_Base* CurrentNode = nullptr;

	int CurrentHistoryIndex = 0; 

	TArray<FQuestEventData> TempEvents;

	TArray<UDialogueNode_Base*> DialogueHistory;

};