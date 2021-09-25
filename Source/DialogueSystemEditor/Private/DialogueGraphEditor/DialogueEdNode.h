#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "DialogueEdNode.generated.h"

class UDialogueEdGraph; 
class UDialogueNode_Base; 

UCLASS()
class UDialogueEdNode : public UEdGraphNode
{
	GENERATED_BODY()

public: 
	UDialogueEdNode();

	TSubclassOf<UDialogueNode_Base> NodeClass = nullptr; 

	UPROPERTY(VisibleAnywhere, Instanced, Category = "DialogueGraph")
		UDialogueNode_Base* DialogueNode;

	UDialogueEdGraph* GetDialogueEdGraph();

	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PrepareForCopying() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
	virtual void PostPlacedNewNode() override;
	virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;
	virtual bool CanUserDeleteNode() const override; 

	virtual UEdGraphPin* GetInputPin() const { return Pins[0]; }
	virtual UEdGraphPin* GetOutputPin() const { return Pins[1]; }

	void GetTransitionList(TArray<class UDialogueEdEdge*>& OutTransitions);

	bool IsConnectedTo(UDialogueEdNode* NodeToCheck); 

	FLinearColor GetBackgroundColor() const;

//#if WITH_EDITOR
//	virtual void PostEditUndo() override;
//#endif
};