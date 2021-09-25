#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "DialogueNode_Base.h"
#include "DialogueRootNode.generated.h"


UCLASS(Blueprintable)
class DIALOGUESYSTEM_API UDialogueRootNode : public UDialogueNode_Base
{

	GENERATED_BODY()

public:

	UDialogueRootNode(); 

	FString GetNodeName() const override;

	bool IsRootNode() const override;

};