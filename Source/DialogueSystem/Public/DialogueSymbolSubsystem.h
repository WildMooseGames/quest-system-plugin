#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DialogueSystemTypes.h"
#include "DialogueSymbolSubsystem.generated.h"


/**
 *
 */
UCLASS()
class DIALOGUESYSTEM_API UDialogueSymbolSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UDialogueSymbolSubsystem();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FDialogueSymbolData GetDialogueSymbolData(FName DialogueSymbolID);

	/** Implement this for initialization of instances of the system */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override; 
	

private:

	UPROPERTY(EditDefaultsOnly)
		class UDataTable* DialogueSymbolDB;

};
