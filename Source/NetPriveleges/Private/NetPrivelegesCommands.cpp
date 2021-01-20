// Copyright Epic Games, Inc. All Rights Reserved.

#include "NetPrivelegesCommands.h"

#define LOCTEXT_NAMESPACE "FNetPrivelegesModule"

void FNetPrivelegesCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Priveleges", "Bring up Network Priveleges window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
