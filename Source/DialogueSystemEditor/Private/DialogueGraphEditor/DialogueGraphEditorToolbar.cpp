#include "DialogueGraphEditorToolbar.h"
#include "DialogueGraphEditor.h"

#define LOCTEXT_NAMESPACE "DialogueGraphEditorToolbar"

void FDialogueGraphEditorToolbar::AddDialogueGraphToolbar(TSharedPtr<FExtender> Extender)
{
	check(DialogueGraphEditor.IsValid());
	TSharedPtr<FDialogueGraphEditor> DialogueGraphEditorPtr = DialogueGraphEditor.Pin();

	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
	ToolbarExtender->AddToolBarExtension("Asset", EExtensionHook::After, DialogueGraphEditorPtr->GetToolkitCommands(), FToolBarExtensionDelegate::CreateSP(this, &FDialogueGraphEditorToolbar::FillDialogueGraphToolbar));
	DialogueGraphEditorPtr->AddToolbarExtender(ToolbarExtender);
}

void FDialogueGraphEditorToolbar::FillDialogueGraphToolbar(FToolBarBuilder& ToolbarBuilder)
{
	check(DialogueGraphEditor.IsValid());
	TSharedPtr<FDialogueGraphEditor> DialogueGraphEditorPtr = DialogueGraphEditor.Pin();

	ToolbarBuilder.BeginSection("Dialogue Graph");
	{

	}
	ToolbarBuilder.EndSection();

}

#undef LOCTEXT_NAMESPACE