// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

class UWidgetSwitcher; 
class UImage; 
class UInteractiveDialogueSceneWidget; 
class UWrapBox; 
class UButton; 

DECLARE_DYNAMIC_DELEGATE(FDialoguetWidgetEvent);

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEM_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	FDialoguetWidgetEvent OnClose; 
	FDialoguetWidgetEvent OnContinue;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* SceneImage = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWrapBox* InteractiveSceneBox = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* ContinueButton = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* ButtonImage = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWidgetSwitcher* Switcher = nullptr;

	void DisplayScene(UTexture2D* SceneTexture, bool bLastScene = false);

	void DisplayInteractiveScene(UInteractiveDialogueSceneWidget* InteractiveSceneWidget, bool bLastScene = false);

protected:

	UPROPERTY(EditDefaultsOnly, Category="Dialogue Widget")
		TSoftObjectPtr<UTexture2D> CrossIcon;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue Widget")
		TSoftObjectPtr<UTexture2D> ContinueIcon;

	UFUNCTION()
		void HandleOnContinueButtonClicked(); 

	void NativeConstruct() override;

	FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void NativeDestruct() override;

	UInteractiveDialogueSceneWidget* CurrentInteractiveSceneWidget = nullptr;

};
