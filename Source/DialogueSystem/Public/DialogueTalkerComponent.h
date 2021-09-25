#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueTalkerComponent.generated.h"

class UDialogueGraph;
class UInteractiveDialogueSceneWidget;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DIALOGUESYSTEM_API UDialogueTalkerComponent : public UActorComponent
{
	GENERATED_BODY()

public :

	UFUNCTION(BlueprintCallable, Category = "Dialogue Component")
		void StartDialogue(AActor* ListenerActor);

	UFUNCTION(BlueprintCallable, Category = "Dialogue Component")
		void GetNextScene();

	UFUNCTION(BlueprintCallable, Category = "Dialogue Component")
		void EndDialogue();

	UFUNCTION(BlueprintCallable, Category = "Dialogue Component")
		bool IsDialogueOngoing() const; 

protected:

	virtual void BeginPlay() override;

	AActor* CurrentListenerActor = nullptr;

	UPROPERTY(EditAnywhere, Category = "Dialogue Component")
		UDialogueGraph* DialogueGraph;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue Component")
		TSubclassOf<UInteractiveDialogueSceneWidget> InteractiveSceneWidgetClass = nullptr;

};