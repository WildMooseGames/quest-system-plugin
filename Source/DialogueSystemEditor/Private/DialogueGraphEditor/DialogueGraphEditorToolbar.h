#pragma once

#include "CoreMinimal.h"

class FDialogueGraphEditor;
class FExtender;
class FToolBarBuilder;

class FDialogueGraphEditorToolbar : public TSharedFromThis<FDialogueGraphEditorToolbar>
{
public:
	FDialogueGraphEditorToolbar(TSharedPtr<FDialogueGraphEditor> InDialogueGraphEditor)
		: DialogueGraphEditor(InDialogueGraphEditor) {}

	void AddDialogueGraphToolbar(TSharedPtr<FExtender> Extender);

private:

	void FillDialogueGraphToolbar(FToolBarBuilder& ToolbarBuilder);

protected:
	/** Pointer back to the blueprint editor tool that owns us */
	TWeakPtr<FDialogueGraphEditor> DialogueGraphEditor;
};