#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "DialogueNode_Base.h"
#include "DialogueGraph.h"
#include "DialogueNode.generated.h"

class UDialogueEdge; 

UCLASS(Blueprintable) 
class DIALOGUESYSTEM_API UDialogueNode : public UDialogueNode_Base
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "DialogueNode")
		FString NodeName = "New Node";

	UPROPERTY(BlueprintReadOnly, Category = "DialogueNode")
		TArray<UDialogueEdge*> InEdges;

	UPROPERTY(EditAnywhere, Category = "Event To Trigger")
		FString OnEnterNodeEvent; 

	UPROPERTY(EditAnywhere, Category = "Event To Set")
		TArray<FDialogueEvent_Bool> OnEnterNodeQuestEvent_Bool;

	UPROPERTY(EditAnywhere, Category = "Event To Set")
		TArray<FDialogueEvent_Int> OnEnterNodeQuestEvent_Int;

	UPROPERTY(EditAnywhere, Category = "Event To Set")
		TArray<FDialogueEvent_String> OnEnterNodeQuestEvent_String;

	virtual FLinearColor GetBackgroundColor() const override; 

	virtual FString GetNodeName() const override;

	void OnEnterNode();

};