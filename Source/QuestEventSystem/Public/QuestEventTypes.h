#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/Actor.h"
#include "Misc/Optional.h"
#include "Engine/DataTable.h"
#include "QuestEventTypes.generated.h"


UENUM(BlueprintType)
enum class EQuestEventType :uint8
{
	INT UMETA(DisplayName = "Int"),
	BOOL UMETA(DisplayName = "Bool"),
	STRING UMETA(DisplayName = "String"),
};

USTRUCT(BlueprintType)
struct FQuestEventData
{
	GENERATED_BODY()

public:

	FQuestEventData()
		: Key("none"), Type(EQuestEventType::INT)
	{}

	FQuestEventData(FString pKey, EQuestEventType pType)
		: Key(pKey), Type(pType)
	{}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest Event")
		FString Key;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest Event")
		EQuestEventType Type;

	bool operator==(const FQuestEventData& OtherEvent) const
	{
		if (Key == OtherEvent.Key && Type == OtherEvent.Type)
			return true;
		return false;
	}
};



USTRUCT(BlueprintType)
struct FQuestEvent_Bool : public FTableRowBase
{
	GENERATED_BODY()

public:

	FQuestEvent_Bool()
		: Key("none"), Value(false)
	{}

	FQuestEvent_Bool(FString pKey, bool pValue)
		: Key(pKey), Value(pValue)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Event")
		FString Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Event")
		bool Value;

	uint32 GetTypeHash() const
	{
		FString StringToHash = Key;
		return FCrc::MemCrc32(*StringToHash, StringToHash.Len());
	}

	bool operator==(const FQuestEvent_Bool& OtherEvent) const
	{
		if (Key == OtherEvent.Key && Value == OtherEvent.Value )
			return true;
		return false;
	}
};

FORCEINLINE uint32 GetTypeHash(const FQuestEvent_Bool& other)
{
	return other.GetTypeHash();
}

USTRUCT(BlueprintType)
struct FQuestEvent_Int : public FTableRowBase
{
	GENERATED_BODY()

public:

	FQuestEvent_Int()
		: Key("none"), Value(0)
	{}

	FQuestEvent_Int(FString pKey, int pValue)
		: Key(pKey), Value(pValue)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Event")
		FString Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Event")
		int Value;

	uint32 GetTypeHash() const
	{
		FString StringToHash = Key;
		return FCrc::MemCrc32(*StringToHash, StringToHash.Len());
	}

	bool operator==(const FQuestEvent_Int& OtherEvent) const
	{
		if (Key == OtherEvent.Key && Value == OtherEvent.Value)
			return true;
		return false;
	}
};

FORCEINLINE uint32 GetTypeHash(const FQuestEvent_Int& other)
{
	return other.GetTypeHash();
}

USTRUCT(BlueprintType)
struct FQuestEvent_String : public FTableRowBase
{
	GENERATED_BODY()

public:

	FQuestEvent_String()
		: Key("none"), Value("")
	{}

	FQuestEvent_String(FString pKey, FString pValue)
		: Key(pKey), Value(pValue)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Event")
		FString Key;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Event")
		FString Value;

	uint32 GetTypeHash() const
	{
		FString StringToHash = Key;
		return FCrc::MemCrc32(*StringToHash, StringToHash.Len());
	}

	bool operator==(const FQuestEvent_String& OtherEvent) const
	{
		if (Key == OtherEvent.Key && Value == OtherEvent.Value)
			return true;
		return false;
	}
};

FORCEINLINE uint32 GetTypeHash(const FQuestEvent_String& other)
{
	return other.GetTypeHash();
}


USTRUCT(BlueprintType)
struct FQuestEventResult_Bool
{
	GENERATED_BODY()

public:

	FQuestEventResult_Bool()
		: Value(false), bIsValid(false)
	{}

	FQuestEventResult_Bool(bool pValue, bool pbIsValid)
		: Value(pValue), bIsValid(pbIsValid)
	{}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest Event")
		bool Value;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest Event")
		bool bIsValid;

	bool operator==(const FQuestEventResult_Bool& OtherEventResult) const
	{
		if (Value == OtherEventResult.Value && bIsValid == OtherEventResult.bIsValid)
			return true;
		return false;
	}
};

USTRUCT(BlueprintType)
struct FQuestEventResult_Int
{
	GENERATED_BODY()

public:

	FQuestEventResult_Int()
		: Value(0), bIsValid(false)
	{}

	FQuestEventResult_Int(uint8 pValue, bool pbIsValid)
		: Value(pValue), bIsValid(pbIsValid)
	{}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest Event")
		uint8 Value;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest Event")
		bool bIsValid;

	bool operator==(const FQuestEventResult_Int& OtherEventResult) const
	{
		if (Value == OtherEventResult.Value && bIsValid == OtherEventResult.bIsValid)
			return true;
		return false;
	}
};

USTRUCT(BlueprintType)
struct FQuestEventResult_String
{
	GENERATED_BODY()

public:

	FQuestEventResult_String()
		: Value(""), bIsValid(false)
	{}

	FQuestEventResult_String(FString pValue, bool pbIsValid)
		: Value(pValue), bIsValid(pbIsValid)
	{}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest Event")
		FString Value;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest Event")
		bool bIsValid;

	bool operator==(const FQuestEventResult_String& OtherEventResult) const
	{
		if (Value == OtherEventResult.Value && bIsValid == OtherEventResult.bIsValid)
			return true;
		return false;
	}
};


