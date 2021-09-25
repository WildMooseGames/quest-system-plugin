#include "DialogueGraphFactory.h"

#include "DialogueGraph.h"

UDialogueGraphFactory::UDialogueGraphFactory() 
{
  SupportedClass = UDialogueGraph::StaticClass();
  bCreateNew = true;
  bEditAfterNew = true;
}

UObject *UDialogueGraphFactory::FactoryCreateNew(UClass *InClass, UObject *InParent, FName InName, EObjectFlags Flags, UObject *Context, FFeedbackContext *Warn)
{
  check(InClass->IsChildOf(UDialogueGraph::StaticClass()));
  return NewObject<UDialogueGraph>(InParent, InClass, InName, Flags);
}

bool UDialogueGraphFactory::ShouldShowInNewMenu() const
{
  return true;
}

bool UDialogueGraphFactory::CanCreateNew() const
{
  return true;
}