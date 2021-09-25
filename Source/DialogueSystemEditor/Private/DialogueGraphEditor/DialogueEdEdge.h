#pragma once


#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "DialogueEdge.h"
#include "DialogueEdEdge.generated.h"

class UDialogueEdGraph;
class UDialogueEdNode;

UCLASS()
class UDialogueEdEdge : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UDialogueEdEdge();


	UPROPERTY(VisibleAnywhere, Instanced, Category = "DialogueGraph")
		UDialogueEdge* DialogueEdge;


	UDialogueEdGraph* GetDialogueEdGraph();

	UDialogueEdNode* GetStartNode();
	UDialogueEdNode* GetEndNode();

	void PinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual void PrepareForCopying() override;

	virtual UEdGraphPin* GetInputPin() const { return Pins[0]; }
	virtual UEdGraphPin* GetOutputPin() const { return Pins[1]; }

	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;

	void CreateConnections(UDialogueEdNode* Start, UDialogueEdNode* End);

	FLinearColor GetBackgroundColor() const;


//#if WITH_EDITOR
//	virtual void PostEditUndo() override;
//#endif

};