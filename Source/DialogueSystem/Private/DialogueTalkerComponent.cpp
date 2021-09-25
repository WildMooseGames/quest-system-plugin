#include "DialogueTalkerComponent.h"
#include "DialogueGraph.h"
#include "InteractiveDialogueSceneWidget.h"
#include "Kismet/GameplayStatics.h"
#include "DialogueListenerInterface.h"
#include "SceneDialogueNode.h"
#include "InteractiveDialogueNode.h"

void UDialogueTalkerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(DialogueGraph))
	{
		DialogueGraph->Initialize(); 
	}

}

void UDialogueTalkerComponent::StartDialogue(AActor* ListenerActor)
{
	if (ensure(DialogueGraph))
	{
		CurrentListenerActor = ListenerActor;

		IDialogueListenerInterface* CurrentListenerInterface = Cast<IDialogueListenerInterface>(CurrentListenerActor);

		if (!CurrentListenerInterface)
			return;

		CurrentListenerInterface->StartDialogue_Implementation(this);

		FDialogueNodeWrapper DialogueNodeWrapper = DialogueGraph->StartDialogue(this);

		switch (DialogueNodeWrapper.SceneType)
		{
		case EDialogueSceneType::SCENE:
		{
			USceneDialogueNode* SceneNode = Cast<USceneDialogueNode>(DialogueNodeWrapper.NodeReference);

			if (SceneNode)
			{
				CurrentListenerInterface->OnNewScene_Implementation(SceneNode->SceneTexture, SceneNode->IsEndNode());
			}

			break;
		}
		case EDialogueSceneType::INTERACTIVE:
		{
			UInteractiveDialogueNode* InteractiveNode = Cast<UInteractiveDialogueNode>(DialogueNodeWrapper.NodeReference);

			if (InteractiveNode)
			{
				UInteractiveDialogueSceneWidget* InteractiveSceneWidget = CreateWidget<UInteractiveDialogueSceneWidget, APlayerController>(UGameplayStatics::GetPlayerController(this, 0), InteractiveSceneWidgetClass, FName(InteractiveNode->QuestEventKey));
				InteractiveSceneWidget->InitializeInteractiveScene(DialogueGraph, InteractiveNode->Symbols, InteractiveNode->QuestEventKey); 

				CurrentListenerInterface->OnNewInteractiveScene_Implementation(InteractiveSceneWidget, InteractiveNode->IsEndNode());
			}

			break;
		}
		}

	}
}

void UDialogueTalkerComponent::GetNextScene()
{
	if (ensure(DialogueGraph) && CurrentListenerActor)
	{

		IDialogueListenerInterface* CurrentListenerInterface = Cast<IDialogueListenerInterface>(CurrentListenerActor);

		if (!CurrentListenerInterface)
			return;

		FDialogueNodeWrapper DialogueNodeWrapper = DialogueGraph->GetNextNode();

		switch (DialogueNodeWrapper.SceneType)
		{
		case EDialogueSceneType::SCENE:
		{
			USceneDialogueNode* SceneNode = Cast<USceneDialogueNode>(DialogueNodeWrapper.NodeReference);

			if (SceneNode)
			{
				CurrentListenerInterface->OnNewScene_Implementation(SceneNode->SceneTexture, SceneNode->IsEndNode());
			}

			break;
		}
		case EDialogueSceneType::INTERACTIVE:
		{
			UInteractiveDialogueNode* InteractiveNode = Cast<UInteractiveDialogueNode>(DialogueNodeWrapper.NodeReference);

			if (InteractiveNode)
			{
				UInteractiveDialogueSceneWidget* InteractiveSceneWidget = CreateWidget<UInteractiveDialogueSceneWidget, APlayerController>(UGameplayStatics::GetPlayerController(this, 0), InteractiveSceneWidgetClass, FName(InteractiveNode->QuestEventKey));
				InteractiveSceneWidget->InitializeInteractiveScene(DialogueGraph, InteractiveNode->Symbols, InteractiveNode->QuestEventKey);

				CurrentListenerInterface->OnNewInteractiveScene_Implementation(InteractiveSceneWidget, InteractiveNode->IsEndNode());
			}
			break;
		}
		case EDialogueSceneType::NONE:
		{
			EndDialogue();

			CurrentListenerInterface->OnEndDialogue_Implementation();
			break;
		}
		}

	}
}

void UDialogueTalkerComponent::EndDialogue()
{
	if (ensure(DialogueGraph) && CurrentListenerActor)
	{
		DialogueGraph->EndDialogue();
		CurrentListenerActor = nullptr; 
	}
}

bool UDialogueTalkerComponent::IsDialogueOngoing() const
{
	return CurrentListenerActor != nullptr; 
}