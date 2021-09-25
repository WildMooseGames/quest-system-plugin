#include "DialogueSymbolSubsystem.h"

UDialogueSymbolSubsystem::UDialogueSymbolSubsystem()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> BP_DialogueSymbolDB(TEXT("DataTable'/Game/Data/DialogueSymbolDB.DialogueSymbolDB'"));
	DialogueSymbolDB = BP_DialogueSymbolDB.Object;
}

void UDialogueSymbolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

FDialogueSymbolData UDialogueSymbolSubsystem::GetDialogueSymbolData(FName DialogueSymbolID)
{
	UGameInstance* GameInstance = GetGameInstance();

	if (GameInstance)
	{

		FDialogueSymbolData* Temp = DialogueSymbolDB->FindRow<FDialogueSymbolData>(DialogueSymbolID, "");

		if (Temp)
			return *Temp;
	}

	return FDialogueSymbolData();
}