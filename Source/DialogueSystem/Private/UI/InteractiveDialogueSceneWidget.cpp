// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveDialogueSceneWidget.h"
#include "DialogueSymbolSubsystem.h"
#include "QuestEventUtility.h"
#include "DialogueGraph.h"
#include "Components/WidgetSwitcher.h"
#include "DialogueSymbolWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "Components/WrapBox.h"

void UInteractiveDialogueSceneWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsFocusable = true;

	//ensure(SymbolsToDisplay.Num() <= 4 && SymbolsToDisplay.Num() >= 2); 
	ensure(DialogueSymbolWidgetClass);

	TwoSymbolBox1->ClearChildren();
	TwoSymbolBox2->ClearChildren();
	ThreeSymbolBox1->ClearChildren();
	ThreeSymbolBox2->ClearChildren();
	ThreeSymbolBox3->ClearChildren();
	FourSymbolBox1->ClearChildren();
	FourSymbolBox2->ClearChildren();
	FourSymbolBox3->ClearChildren();
	FourSymbolBox4->ClearChildren();

	switch(SymbolsToDisplay.Num())
	{
	case 2:
	{
		AddDialogueSymbolToWrapBox(TwoSymbolBox1, SymbolsToDisplay[0]); 
		AddDialogueSymbolToWrapBox(TwoSymbolBox2, SymbolsToDisplay[1]);

		TwoSymbolBox1->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Previous, EUINavigationRule::Stop); 
		TwoSymbolBox1->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Next, TwoSymbolBox2->GetChildAt(0));
		TwoSymbolBox1->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Left, TwoSymbolBox2->GetChildAt(0));
		TwoSymbolBox1->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Right, TwoSymbolBox2->GetChildAt(0));
		TwoSymbolBox1->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Up, EUINavigationRule::Stop);
		TwoSymbolBox1->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Down, EUINavigationRule::Stop);

		TwoSymbolBox2->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Next, EUINavigationRule::Stop);
		TwoSymbolBox2->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Previous, TwoSymbolBox1->GetChildAt(0));
		TwoSymbolBox2->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Left, TwoSymbolBox1->GetChildAt(0));
		TwoSymbolBox2->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Right, TwoSymbolBox1->GetChildAt(0));
		TwoSymbolBox2->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Up, EUINavigationRule::Stop);
		TwoSymbolBox2->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Down, EUINavigationRule::Stop);

		Switcher->SetActiveWidgetIndex(0); 
		break;
	}
	case 3: 
	{
		AddDialogueSymbolToWrapBox(ThreeSymbolBox1, SymbolsToDisplay[0]);
		AddDialogueSymbolToWrapBox(ThreeSymbolBox2, SymbolsToDisplay[1]);
		AddDialogueSymbolToWrapBox(ThreeSymbolBox3, SymbolsToDisplay[2]);

		ThreeSymbolBox1->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Previous, EUINavigationRule::Stop);
		ThreeSymbolBox1->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Next, ThreeSymbolBox2->GetChildAt(0));
		ThreeSymbolBox1->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Left, ThreeSymbolBox3->GetChildAt(0));
		ThreeSymbolBox1->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Right, ThreeSymbolBox2->GetChildAt(0));
		ThreeSymbolBox1->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Up, EUINavigationRule::Stop);
		ThreeSymbolBox1->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Down, EUINavigationRule::Stop);

		ThreeSymbolBox2->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Next, ThreeSymbolBox3->GetChildAt(0));
		ThreeSymbolBox2->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Previous, ThreeSymbolBox1->GetChildAt(0));
		ThreeSymbolBox2->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Left, ThreeSymbolBox1->GetChildAt(0));
		ThreeSymbolBox2->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Right, ThreeSymbolBox3->GetChildAt(0));
		ThreeSymbolBox2->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Up, EUINavigationRule::Stop);
		ThreeSymbolBox2->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Down, EUINavigationRule::Stop);

		ThreeSymbolBox3->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Next, EUINavigationRule::Stop);
		ThreeSymbolBox3->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Previous, ThreeSymbolBox2->GetChildAt(0));
		ThreeSymbolBox3->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Left, ThreeSymbolBox3->GetChildAt(0));
		ThreeSymbolBox3->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Right, ThreeSymbolBox1->GetChildAt(0));
		ThreeSymbolBox3->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Up, EUINavigationRule::Stop);
		ThreeSymbolBox3->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Down, EUINavigationRule::Stop);

		Switcher->SetActiveWidgetIndex(1);
		break;
	}
	case 4:
	{
		AddDialogueSymbolToWrapBox(FourSymbolBox1, SymbolsToDisplay[0]);
		AddDialogueSymbolToWrapBox(FourSymbolBox2, SymbolsToDisplay[1]);
		AddDialogueSymbolToWrapBox(FourSymbolBox3, SymbolsToDisplay[2]);
		AddDialogueSymbolToWrapBox(FourSymbolBox4, SymbolsToDisplay[3]);

		FourSymbolBox1->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Previous, EUINavigationRule::Stop);
		FourSymbolBox1->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Next, FourSymbolBox2->GetChildAt(0));
		FourSymbolBox1->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Left, FourSymbolBox4->GetChildAt(0));
		FourSymbolBox1->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Right, FourSymbolBox2->GetChildAt(0));
		FourSymbolBox1->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Up, EUINavigationRule::Stop);
		FourSymbolBox1->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Down, EUINavigationRule::Stop);

		FourSymbolBox2->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Previous, FourSymbolBox1->GetChildAt(0));
		FourSymbolBox2->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Next, FourSymbolBox3->GetChildAt(0));
		FourSymbolBox2->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Left, FourSymbolBox1->GetChildAt(0));
		FourSymbolBox2->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Right, FourSymbolBox3->GetChildAt(0));
		FourSymbolBox2->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Up, EUINavigationRule::Stop);
		FourSymbolBox2->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Down, EUINavigationRule::Stop);

		FourSymbolBox3->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Previous, FourSymbolBox2->GetChildAt(0));
		FourSymbolBox3->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Next, FourSymbolBox4->GetChildAt(0));
		FourSymbolBox3->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Left, FourSymbolBox2->GetChildAt(0));
		FourSymbolBox3->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Right, FourSymbolBox4->GetChildAt(0));
		FourSymbolBox3->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Up, EUINavigationRule::Stop);
		FourSymbolBox3->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Down, EUINavigationRule::Stop);

		FourSymbolBox4->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Next, EUINavigationRule::Stop);
		FourSymbolBox4->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Previous, FourSymbolBox3->GetChildAt(0));
		FourSymbolBox4->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Left, FourSymbolBox3->GetChildAt(0));
		FourSymbolBox4->GetChildAt(0)->SetNavigationRuleExplicit(EUINavigation::Right, FourSymbolBox1->GetChildAt(0));
		FourSymbolBox4->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Up, EUINavigationRule::Stop);
		FourSymbolBox4->GetChildAt(0)->SetNavigationRuleBase(EUINavigation::Down, EUINavigationRule::Stop);

		Switcher->SetActiveWidgetIndex(2);
		break; 
	}
	}
}


//FReply UInteractiveDialogueSceneWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) 
//{
//	if (!HasFocusedDescendants())
//	{
//		switch (Switcher->GetActiveWidgetIndex())
//		{
//		case 0:
//		{
//			if (TwoSymbolBox1->HasAnyChildren())
//			{
//				TwoSymbolBox1->GetChildAt(0)->SetKeyboardFocus();
//				return FReply::Handled();
//			}
//			
//			break;
//		}
//		case 1:
//		{
//			if (ThreeSymbolBox1->HasAnyChildren())
//			{
//				ThreeSymbolBox1->GetChildAt(0)->SetKeyboardFocus();
//				return FReply::Handled();
//			}
//
//			break;
//		}
//		case 2:
//		{
//			if (FourSymbolBox1->HasAnyChildren())
//			{
//				FourSymbolBox1->GetChildAt(0)->SetKeyboardFocus();
//				return FReply::Handled();
//			}
//
//			break;
//		}
//		}
//	}
//
//	return FReply::Unhandled();
//}

FReply UInteractiveDialogueSceneWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

	Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	if (InMouseEvent.GetScreenSpacePosition().Size() - InMouseEvent.GetLastScreenSpacePosition().Size() != 0.f && bIsFocusable && !HasFocusedDescendants())
	{
		SetKeyboardFocus();

		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FReply UInteractiveDialogueSceneWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	FKey Key = InKeyEvent.GetKey();

	return DelegateKeyDown(); 
}

FReply UInteractiveDialogueSceneWidget::DelegateKeyDown()
{
	if (GetOwningPlayer()->bShowMouseCursor)
	{
		GetOwningPlayer()->bShowMouseCursor = false;
	}

	if (!HasFocusedDescendants())
	{
		switch (Switcher->GetActiveWidgetIndex())
		{
		case 0:
		{
			TwoSymbolBox1->GetChildAt(0)->SetKeyboardFocus();
			return FReply::Handled();

			break;
		}
		case 1:
		{
			ThreeSymbolBox1->GetChildAt(0)->SetKeyboardFocus();
			return FReply::Handled();

			break;
		}
		case 2:
		{
			FourSymbolBox1->GetChildAt(0)->SetKeyboardFocus();
			return FReply::Handled();

			break;
		}
		}
	}

	return FReply::Unhandled();
}

void UInteractiveDialogueSceneWidget::AddDialogueSymbolToWrapBox(UWrapBox* BoxToAddTo, FString SymbolID)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(DialogueGraph);

	if (!GameInstance)
		return;

	UDialogueSymbolSubsystem* DialogueSymbolSS = GameInstance->GetSubsystem<UDialogueSymbolSubsystem>();

	if (!DialogueSymbolSS)
		return;

	FDialogueSymbolData SymbolData = DialogueSymbolSS->GetDialogueSymbolData(UKismetStringLibrary::Conv_StringToName(SymbolID));

	UDialogueSymbolWidget* SymbolWidget = CreateWidget<UDialogueSymbolWidget, APlayerController>(UGameplayStatics::GetPlayerController(DialogueGraph, 0), DialogueSymbolWidgetClass, FName(SymbolID));
	SymbolWidget->SetDialogueSymbolData(SymbolData);
	SymbolWidget->SetVisibility(ESlateVisibility::Visible); 
	SymbolWidget->OnSelectedEvent.BindUFunction(this, FName("HandleOnDialogueSymbolSelected")); 
	BoxToAddTo->AddChildToWrapBox(SymbolWidget);
}


void UInteractiveDialogueSceneWidget::HandleOnDialogueSymbolSelected(FString DialogueSymbolID)
{
	UQuestEventUtility::SetEventValue_String(Cast<UObject>(DialogueGraph), QuestEventKey, DialogueSymbolID);
	DialogueGraph->RegisterTempEvent(FQuestEventData(QuestEventKey, EQuestEventType::STRING)); 


	OnSymbolSelectedEvent.ExecuteIfBound(); 
}

void UInteractiveDialogueSceneWidget::InitializeInteractiveScene(UDialogueGraph* pDialogueGraph, TArray<FString> pSymbolsToDisplay, FString pQuestEventKey)
{
	DialogueGraph = pDialogueGraph;
	SymbolsToDisplay = pSymbolsToDisplay; 
	QuestEventKey = pQuestEventKey; 
}