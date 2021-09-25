// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractiveDialogueSceneWidget.generated.h"

class UWidgetSwitcher; 
class UWrapBox; 
class UDialogueGraph; 
class UDialogueSymbolWidget; 

DECLARE_DYNAMIC_DELEGATE(FInteractiveDialogueSceneEvent);

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEM_API UInteractiveDialogueSceneWidget : public UUserWidget
{
	GENERATED_BODY()

public : 

	FInteractiveDialogueSceneEvent OnSymbolSelectedEvent; 

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWidgetSwitcher* Switcher = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWrapBox* TwoSymbolBox1 = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWrapBox* TwoSymbolBox2 = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWrapBox* ThreeSymbolBox1 = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWrapBox* ThreeSymbolBox2 = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWrapBox* ThreeSymbolBox3 = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWrapBox* FourSymbolBox1 = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWrapBox* FourSymbolBox2 = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWrapBox* FourSymbolBox3 = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWrapBox* FourSymbolBox4 = nullptr;

	void InitializeInteractiveScene(UDialogueGraph* pDialogueGraph, TArray<FString> pSymbolsToDisplay, FString pQuestEventKey);

	FReply DelegateKeyDown();

protected :

	void NativeConstruct() override;

	//FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;

	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UPROPERTY(EditDefaultsOnly, Category = "InteractiveDialogueSceneWidget")
		TSubclassOf<UDialogueSymbolWidget> DialogueSymbolWidgetClass; 

	UFUNCTION()
		void HandleOnDialogueSymbolSelected(FString DialogueSymbolID); 

	void AddDialogueSymbolToWrapBox(UWrapBox* BoxToAddTo, FString SymbolID);

	FString QuestEventKey = "InteractiveSceneEvent"; 

	UDialogueGraph* DialogueGraph = nullptr; 

	TArray<FString> SymbolsToDisplay; 
	
};
