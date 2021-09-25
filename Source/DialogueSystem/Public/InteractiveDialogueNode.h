#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "DialogueNode.h"
#include "InteractiveDialogueNode.generated.h"

class UDialogueArc;
class UDialogueGraph;
class UUserWidget;

UCLASS(Blueprintable) 
class DIALOGUESYSTEM_API UInteractiveDialogueNode : public UDialogueNode
{

	GENERATED_BODY()

public:

	FLinearColor GetBackgroundColor() const override;

	EDialogueSceneType GetSceneType() const override;

	/*Need to have between 2 and 4 elements*/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Data")
		TArray<FString> Symbols; 

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Data")
		FString QuestEventKey; 
};