# Quest System Plugin for Unreal Engine 4

Quest system plugin developped for an upcoming game

## How to get

1. Clone this project to ${Project}/Plugins/ of your UE4 project

```console
git clone https://github.com/WiseMooseGames/quest-system-plugin.git
```

## Features

### Narrative dialogue system

The dialogue system does not follow the common branching dialogue system pattern that we can find in RPG games for example.
It works as a sequence of Scenes, with Scenes being of two types:

- Static: A static image, usually used to describe a narrative scene
- Interactive: Multiple clickable images/icons, that player need to choose between

### Quest event system

The Quest event system is a global state management system.
It can be used to store Events using key-value pair, and act on Event changes.

## How to use

### Global

- Enable the plugin in UE4

[Enable Quest System Plugin in UE4](Docs/enable_quest_system_ue4.png)

### Narrative dialogue system

- Create a dialogue asset

[Create a dialogue asset](Docs/create_dialogue_asset.png)

- Create your dialogue tree

[Create the dialogue tree](Docs/create_dialogue_tree.png)

### Quest Event System

#### Getting an event value

```
	FQuestEventResult_Bool bEventCompleted = UQuestEventUtility::GetEventValue_Bool(this, EventKey);

	if (bEventCompleted.bIsValid)
	{
		if (bEventCompleted.Value)
		{
			// do something on event value completed
		}
    else
    {
      // do something on event value not completed
    }
	}
	else
	{
		// do something on event not set
	}
```

#### Setting an event value

```
UQuestEventUtility::SetEventValue_Bool(this, EventKey, false);
```

#### Registering to an event on value changed

Define a method handler

```
void ACustomActor::HandleOnEventStateChanged(FString EventKey, FQuestEventResult_Bool OldValue, bool NewValue)
{
  // do something
}
```

Define a Quest Event Delegate in the header file

```
FQuestEventDelegate_Bool OnEventStateChanged;
```

Bind the Handler to the delegate

```
OnEventStateChanged.BindDynamic(this, &ACustomActor::HandleOnEventStateChanged);
```

Register the delegate on event value changed

```
UQuestEventUtility::RegisterToEvent_Bool(this, GlobalEventKey, OnEventStateChanged);
```

The delegate will be triggered when the SetEventValue method will be called for with the same EventKey

## Miscellaneous

The custom dialogue editor is inspired from https://github.com/jinyuliao/GenericGraph
