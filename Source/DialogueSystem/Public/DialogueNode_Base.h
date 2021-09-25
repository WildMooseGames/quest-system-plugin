#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "QuestEventTypes.h"
#include "DialogueSystemTypes.h"
#include "DialogueNode_Base.generated.h"

class UDialogueEdge;
class UDialogueGraph; 

UCLASS(Blueprintable)
class DIALOGUESYSTEM_API UDialogueNode_Base : public UObject
{

	GENERATED_BODY()

public:

	virtual UWorld* GetWorld() const override;

	UPROPERTY(VisibleDefaultsOnly, Category = "DialogueNode")
		UDialogueGraph* Graph;

	UPROPERTY(BlueprintReadOnly, Category = "DialogueNode")
		TArray<UDialogueEdge*> OutEdges;

	UPROPERTY(EditAnywhere, Category = "Event To Trigger")
		FString OnLeaveNodeEvent;

	UPROPERTY(EditAnywhere, Category = "Event To Set")
		TArray<FDialogueEvent_Bool> OnLeaveNodeQuestEvent_Bool;

	UPROPERTY(EditAnywhere, Category = "Event To Set")
		TArray<FDialogueEvent_Int> OnLeaveNodeQuestEvent_Int;

	UPROPERTY(EditAnywhere, Category = "Event To Set")
		TArray<FDialogueEvent_String> OnLeaveNodeQuestEvent_String;

	virtual FLinearColor GetBackgroundColor() const;

	UFUNCTION(BlueprintCallable, Category = "DialogueNode")
		virtual FString GetNodeName() const ;

	UFUNCTION(BlueprintCallable, Category = "DialogueNode")
		virtual EDialogueSceneType GetSceneType() const;

	virtual bool IsRootNode() const;

	bool IsConnectedTo(UDialogueNode_Base* NodeToCheck); 

	virtual bool IsEndNode() const;

	void OnLeaveNode(); 

	UFUNCTION(BlueprintCallable, Category = "DialogueNode")
	UDialogueNode_Base* GetNextNode(); 

	void SortOutEdges();
};
