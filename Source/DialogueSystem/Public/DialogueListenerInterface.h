#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DialogueListenerInterface.generated.h"

class UTexture2D; 
class UInteractiveDialogueSceneWidget; 
class UDialogueTalkerComponent; 

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDialogueListenerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class DIALOGUESYSTEM_API IDialogueListenerInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DialogueListener Interface")
		void StartDialogue(UDialogueTalkerComponent* DialogueTalkerComponent);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DialogueListener Interface")
		void OnNewScene(UTexture2D* SceneTexture, bool bEndNode);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DialogueListener Interface")
		void OnNewInteractiveScene(UInteractiveDialogueSceneWidget* InteractiveWidget, bool bEndNode);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DialogueListener Interface")
		void NotifyEndDialogue();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "DialogueListener Interface")
		void OnEndDialogue();

};

