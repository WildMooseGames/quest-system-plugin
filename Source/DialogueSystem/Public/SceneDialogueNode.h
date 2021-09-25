#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "DialogueNode.h"
#include "SceneDialogueNode.generated.h"

class UTexture2D;

UCLASS(Blueprintable)
class DIALOGUESYSTEM_API USceneDialogueNode : public UDialogueNode
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category = "Data")
		UTexture2D* SceneTexture;

	FLinearColor GetBackgroundColor() const override;

	EDialogueSceneType GetSceneType() const override;

};
