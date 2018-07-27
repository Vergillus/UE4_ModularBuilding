// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "MyProject420GameMode.h"
#include "MyProject420Character.h"
#include "UObject/ConstructorHelpers.h"

AMyProject420GameMode::AMyProject420GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
