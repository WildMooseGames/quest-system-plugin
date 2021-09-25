// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSymbolWidget.h"
#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"
#include "Kismet/KismetInputLibrary.h"
#include "Kismet/GameplayStatics.h"


void UDialogueSymbolWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetAllNavigationRules(EUINavigationRule::Escape, FName("None"));

	SetVisibility(ESlateVisibility::HitTestInvisible);

	bIsFocusable = true;

	SymbolImage->SetBrushFromTexture(DialogueSymbolData.SymbolTexture);

	FrameImage->SetRenderOpacity(0.f);

	PlayAnimation(GlowLoopingAnim, 0, 0);

}

FReply UDialogueSymbolWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

	StartOnFocusAnim();

	UGameplayStatics::PlaySound2D(this, OnFocusSound); 

	return FReply::Handled();
}

void UDialogueSymbolWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);

	EndOnFocusAnim();

}

FReply UDialogueSymbolWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	FKey Key = InKeyEvent.GetKey();

	if ((UKismetInputLibrary::EqualEqual_KeyKey(Key, FKey("Enter")) || UKismetInputLibrary::EqualEqual_KeyKey(Key, FKey("Gamepad FaceButton Bottom"))))
	{
		OnSelectedEvent.Execute(DialogueSymbolData.SymbolID.ToString());

		UGameplayStatics::PlaySound2D(this, OnClickSound);

		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FReply UDialogueSymbolWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent); 


	if (InMouseEvent.IsMouseButtonDown(FKey("RightMouseButton")) || InMouseEvent.IsMouseButtonDown(FKey("LeftMouseButton")))
	{
		OnSelectedEvent.Execute(DialogueSymbolData.SymbolID.ToString());

		UGameplayStatics::PlaySound2D(this, OnClickSound);

		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FReply UDialogueSymbolWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);

	if (InMouseEvent.GetScreenSpacePosition().Size() - InMouseEvent.GetLastScreenSpacePosition().Size() != 0.f && bIsFocusable)
	{
		SetKeyboardFocus();

		return FReply::Handled();
	}

	return FReply::Unhandled();
}

void UDialogueSymbolWidget::SetDialogueSymbolData(FDialogueSymbolData NewData)
{
	DialogueSymbolData = NewData;

	if (SymbolImage)
		SymbolImage->SetBrushFromTexture(NewData.SymbolTexture);

	if (GlowImage)
		GlowImage->SetBrushFromTexture(NewData.SymbolGlowTexture);
}

FDialogueSymbolData UDialogueSymbolWidget::GetSymbolData() const
{
	return DialogueSymbolData;
}

void UDialogueSymbolWidget::StartOnFocusAnim()
{
	PauseAnimation(GlowLoopingAnim); 
	PlayAnimation(FrameVisibilityAnim);
	PlayAnimation(GlowSymbolAnim);
}

void UDialogueSymbolWidget::EndOnFocusAnim()
{
	PlayAnimationReverse(FrameVisibilityAnim);
	PlayAnimation(GlowLoopingAnim,0,0);
}