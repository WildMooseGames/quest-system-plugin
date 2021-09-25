#include "SceneDialogueNode.h"

FLinearColor USceneDialogueNode::GetBackgroundColor() const
{
	return FLinearColor::Red;
}

EDialogueSceneType USceneDialogueNode::GetSceneType() const
{
	return EDialogueSceneType::SCENE;
}