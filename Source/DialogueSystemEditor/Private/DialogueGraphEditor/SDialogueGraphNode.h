#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"

class UDialogueEdNode;

class SDialogueGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphNode) {}
	SLATE_END_ARGS()

		void Construct(const FArguments& InArgs, UDialogueEdNode* InNode);

	virtual void UpdateGraphNode() override;
	virtual void CreatePinWidgets() override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;

	//void OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo);

	virtual FSlateColor GetBorderBackgroundColor() const;
	virtual FSlateColor GetBackgroundColor() const;

	virtual EVisibility GetDragOverMarkerVisibility() const;

	virtual const FSlateBrush* GetNameIcon() const;

protected:
	TSharedPtr<SBorder> NodeBody;
	TSharedPtr<SHorizontalBox> OutputPinBox;
};
