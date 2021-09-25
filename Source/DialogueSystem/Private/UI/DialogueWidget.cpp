// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Components/WrapBox.h"
#include "InteractiveDialogueSceneWidget.h"
#include "Kismet/KismetInputLibrary.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Switcher->SetActiveWidgetIndex(0);

	InteractiveSceneBox->ClearChildren();

	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetOwningPlayer());
	GetOwningPlayer()->bShowMouseCursor = true;
	bIsFocusable = true;

	if (!ContinueButton->OnClicked.Contains(this, FName("HandleOnContinueButtonClicked")))
	{
		ContinueButton->OnClicked.AddDynamic(this, &UDialogueWidget::HandleOnContinueButtonClicked); 
	}

	ButtonImage->SetBrushFromSoftTexture(ContinueIcon);
}

void UDialogueWidget::NativeDestruct()
{
	OnClose.ExecuteIfBound(); 

	if (GetOwningPlayer())
	{
		GetOwningPlayer()->bShowMouseCursor = false;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(GetOwningPlayer());
	}

	Super::NativeDestruct();
}

FReply UDialogueWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	FKey Key = InKeyEvent.GetKey();

	if (GetOwningPlayer()->bShowMouseCursor)
	{
		GetOwningPlayer()->bShowMouseCursor = false;
	}

	if (UKismetInputLibrary::EqualEqual_KeyKey(Key, FKey("Escape")) || UKismetInputLibrary::EqualEqual_KeyKey(Key, FKey("Gamepad_Special_Left")) || UKismetInputLibrary::EqualEqual_KeyKey(Key, FKey("Backspace")) || UKismetInputLibrary::EqualEqual_KeyKey(Key, FKey("Gamepad FaceButton Right")))
	{
		RemoveFromParent();
	}

	if (!HasFocusedDescendants())
	{
		switch (Switcher->GetActiveWidgetIndex())
		{
		case 0:
		{
			ContinueButton->SetKeyboardFocus(); 
			break; 
		}
		case 1:
		{
			if (InteractiveSceneBox->HasAnyChildren())
			{
				if (UInteractiveDialogueSceneWidget* InteractiveSceneWidget = Cast<UInteractiveDialogueSceneWidget>(InteractiveSceneBox->GetChildAt(0)))
				{
					return InteractiveSceneWidget->DelegateKeyDown();
				}
				
			}
			
			break;
		}
		}
		
		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FReply UDialogueWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

	Super::NativeOnMouseMove(InGeometry, InMouseEvent); 

	if (InMouseEvent.GetScreenSpacePosition().Size() - InMouseEvent.GetLastScreenSpacePosition().Size() != 0.f && bIsFocusable)
	{
		if (InteractiveSceneBox->HasAnyChildren())
		{
			InteractiveSceneBox->GetChildAt(0)->SetKeyboardFocus();

			return FReply::Handled();
		}

	}

	return FReply::Unhandled();
}

void UDialogueWidget::DisplayScene(UTexture2D* SceneTexture, bool bLastScene)
{
	Switcher->SetActiveWidgetIndex(0); 

	InteractiveSceneBox->ClearChildren();
	CurrentInteractiveSceneWidget = nullptr; 

	SceneImage->SetBrushFromTexture(SceneTexture);

	ContinueButton->SetKeyboardFocus();
	if(bLastScene)
		ButtonImage->SetBrushFromSoftTexture(CrossIcon);
	else
		ButtonImage->SetBrushFromSoftTexture(ContinueIcon);
}

void UDialogueWidget::DisplayInteractiveScene(UInteractiveDialogueSceneWidget* InteractiveSceneWidget, bool bLastScene)
{
	Switcher->SetActiveWidgetIndex(1);

	InteractiveSceneBox->ClearChildren();
	CurrentInteractiveSceneWidget = InteractiveSceneWidget; 

	InteractiveSceneBox->AddChildToWrapBox(InteractiveSceneWidget);

	InteractiveSceneBox->GetChildAt(0)->SetKeyboardFocus();
	if (bLastScene)
		ButtonImage->SetBrushFromSoftTexture(CrossIcon);
	else
		ButtonImage->SetBrushFromSoftTexture(ContinueIcon);
}

void UDialogueWidget::HandleOnContinueButtonClicked()
{
	OnContinue.ExecuteIfBound();
}