#include "InteractiveDialogueNode.h"

FLinearColor UInteractiveDialogueNode::GetBackgroundColor() const
{
	/*return FLinearColor(128, 173, 203);*/
	return FLinearColor::Blue;
}

EDialogueSceneType UInteractiveDialogueNode::GetSceneType() const
{
	return EDialogueSceneType::INTERACTIVE;
}