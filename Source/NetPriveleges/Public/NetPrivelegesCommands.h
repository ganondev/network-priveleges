// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "NetPrivelegesStyle.h"

class FNetPrivelegesCommands : public TCommands<FNetPrivelegesCommands>
{
public:

	FNetPrivelegesCommands()
		: TCommands<FNetPrivelegesCommands>(TEXT("NetPriveleges"), NSLOCTEXT("Contexts", "NetPriveleges", "Network Priveleges Plugin"), NAME_None, FNetPrivelegesStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};