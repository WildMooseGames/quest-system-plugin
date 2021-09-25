#include "DialogueRootNode.h"

UDialogueRootNode::UDialogueRootNode()
{

}

FString UDialogueRootNode::GetNodeName() const
{
	return "Root";
}

bool UDialogueRootNode::IsRootNode() const
{
	return true;
}