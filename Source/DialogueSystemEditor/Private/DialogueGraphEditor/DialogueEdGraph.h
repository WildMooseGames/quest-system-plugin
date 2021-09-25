#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "BlueprintUtilities.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "DialogueEdGraph.generated.h"

class UDialogueGraph; 
class UDialogueEdNode; 
struct FEdGraphEditAction; 

UCLASS()
class UDialogueEdGraph : public UEdGraph
{
	GENERATED_BODY()

public:

	UDialogueEdGraph(); 

	TDelegate<void(const FEdGraphEditAction&)> UpdateAssetOnGraphChangedHandler;

	void SetRootNode(UDialogueEdNode* pRootNode); 

	virtual void UpdateAsset();

	virtual bool Modify(bool bAlwaysMarkDirty = true) override;
	virtual void PostEditUndo() override;

	UDialogueEdNode* RootNode = nullptr; 

	UDialogueGraph* GetDialogueGraph() const;

protected:

	void Clear();
};






