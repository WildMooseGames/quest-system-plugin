#pragma once

#include "QuestEventTypes.h"
#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "DialogueSystemTypes.generated.h"

class UTexture2D;
class UDialogueNode_Base; 

UENUM(BlueprintType)
enum class EDialogueSceneType :uint8
{
	NONE UMETA(DisplayName = "None"),
	SCENE UMETA(DisplayName = "Scene"),
	INTERACTIVE UMETA(DisplayName = "Interactive Scene")
};

USTRUCT(BlueprintType)
struct FDialogueNodeWrapper
{
	GENERATED_BODY()

public:

	FDialogueNodeWrapper()
		: NodeReference(nullptr), SceneType(EDialogueSceneType::NONE) {}

	FDialogueNodeWrapper(UDialogueNode_Base* pNodeReference, EDialogueSceneType pSceneType)
		: NodeReference(pNodeReference), SceneType(pSceneType)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node Wrapper")
		UDialogueNode_Base* NodeReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node Wrapper")
		EDialogueSceneType SceneType; 

	bool operator==(const FDialogueNodeWrapper& OtherNodeWrapper) const
	{
		if (NodeReference == OtherNodeWrapper.NodeReference && SceneType == OtherNodeWrapper.SceneType)
			return true;
		return false;
	}
};

USTRUCT(BlueprintType)
struct FDialogueEvent_Bool
{
	GENERATED_BODY()

public:

	FDialogueEvent_Bool()
		: Event(FQuestEvent_Bool()), bIsTemp(false) {}

	FDialogueEvent_Bool(FQuestEvent_Bool pEvent, bool pbIsTemp)
		: Event(pEvent), bIsTemp(pbIsTemp)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Condition")
		FQuestEvent_Bool Event;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Condition")
		bool bIsTemp = false;

	uint32 GetTypeHash() const
	{
		FString StringToHash = Event.Key;
		return FCrc::MemCrc32(*StringToHash, StringToHash.Len());
	}

	bool operator==(const FDialogueEvent_Bool& OtherCondition) const
	{
		if (Event == OtherCondition.Event && bIsTemp == OtherCondition.bIsTemp)
			return true;
		return false;
	}
};

FORCEINLINE uint32 GetTypeHash(const FDialogueEvent_Bool& other)
{
	return other.GetTypeHash();
}

USTRUCT(BlueprintType)
struct FDialogueEvent_Int
{
	GENERATED_BODY()

public:

	FDialogueEvent_Int()
		: Event(FQuestEvent_Int()), bIsTemp(false) {}

	FDialogueEvent_Int(FQuestEvent_Int pEvent, bool pbIsTemp)
		: Event(pEvent), bIsTemp(pbIsTemp)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Condition")
		FQuestEvent_Int Event;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Condition")
		bool bIsTemp = false;

	uint32 GetTypeHash() const
	{
		FString StringToHash = Event.Key;
		return FCrc::MemCrc32(*StringToHash, StringToHash.Len());
	}

	bool operator==(const FDialogueEvent_Int& OtherCondition) const
	{
		if (Event == OtherCondition.Event && bIsTemp == OtherCondition.bIsTemp)
			return true;
		return false;
	}
};

FORCEINLINE uint32 GetTypeHash(const FDialogueEvent_Int& other)
{
	return other.GetTypeHash();
}

USTRUCT(BlueprintType)
struct FDialogueEvent_String
{
	GENERATED_BODY()

public:

	FDialogueEvent_String()
		: Event(FQuestEvent_String()), bIsTemp(false) {}

	FDialogueEvent_String(FQuestEvent_String pEvent, bool pbIsTemp)
		: Event(pEvent), bIsTemp(pbIsTemp)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Condition")
		FQuestEvent_String Event;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Condition")
		bool bIsTemp = false;

	uint32 GetTypeHash() const
	{
		FString StringToHash = Event.Key;
		return FCrc::MemCrc32(*StringToHash, StringToHash.Len());
	}

	bool operator==(const FDialogueEvent_String& OtherCondition) const
	{
		if (Event == OtherCondition.Event && bIsTemp == OtherCondition.bIsTemp)
			return true;
		return false;
	}
};

FORCEINLINE uint32 GetTypeHash(const FDialogueEvent_String& other)
{
	return other.GetTypeHash();
}

USTRUCT(BlueprintType)
struct FDialogueSymbolData : public FTableRowBase
{
	GENERATED_BODY()

public: 
	FDialogueSymbolData() {}

	FDialogueSymbolData(const FDialogueSymbolData& S) : SymbolID(S.SymbolID), SymbolTexture(S.SymbolTexture), SymbolGlowTexture(S.SymbolGlowTexture) {}

	FDialogueSymbolData(FString pSymbolID, UTexture2D* pSymbolTexture, UTexture2D* pSymbolGlowTexture) : SymbolID(pSymbolID), SymbolTexture(pSymbolTexture), SymbolGlowTexture(pSymbolGlowTexture) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Symbol")
		FName SymbolID = "None";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Symbol")
		UTexture2D* SymbolTexture = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Symbol")
		UTexture2D* SymbolGlowTexture = nullptr;

	bool operator==(const FDialogueSymbolData& OtherSymbol) const
	{
		if (SymbolID == OtherSymbol.SymbolID)
			return true;
		return false;
	}
};
