#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "QuestEventTypes.h"
#include "DialogueSystemTypes.h"
#include "DialogueEdge.generated.h"

class UDialogueNode_Base;
class UDialogueGraph;

UCLASS(Blueprintable)
class DIALOGUESYSTEM_API UDialogueEdge : public UObject
{

	GENERATED_BODY()

public:

	UPROPERTY(VisibleDefaultsOnly, Category = "DialogueGraph")
		UDialogueGraph* Graph;

	UDialogueNode_Base* OriginNode;

	UDialogueNode_Base* DestinationNode;

	UPROPERTY(EditDefaultsOnly, Category = "DialogueEdge")
		int Priority = 0;

	bool CanMakeTransition() const; 

	void DoTransition(); 

	UDialogueNode_Base* GetOriginNode() const;

	UDialogueNode_Base* GetDestinationNode() const;

	UPROPERTY(EditAnywhere, Category = "Event To Trigger")
		FString OnTransitionEvent;

	UPROPERTY(EditAnywhere, Category = "Transition Condition")
		TArray<FQuestEvent_Bool> QuestEventConditions_Bool; 

	UPROPERTY(EditAnywhere, Category = "Transition Condition")
		TArray<FQuestEvent_Int> QuestEventConditions_Int;

	UPROPERTY(EditAnywhere, Category = "Transition Condition")
		TArray<FQuestEvent_String> QuestEventConditions_String;

	UPROPERTY(EditAnywhere, Category = "Event To Set")
		TArray<FDialogueEvent_Bool> OnTransitionQuestEvent_Bool;

	UPROPERTY(EditAnywhere, Category = "Event To Set")
		TArray<FDialogueEvent_Int> OnTransitionQuestEvent_Int;

	UPROPERTY(EditAnywhere, Category = "Event To Set")
		TArray<FDialogueEvent_String> OnTransitionQuestEvent_String;

	FORCEINLINE bool operator < (const UDialogueEdge& Other)
	{
		return Priority < Other.Priority;
	}

};