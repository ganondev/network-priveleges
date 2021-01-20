#pragma once

#include "CoreMinimal.h"
#include "CommandExecutionStatus.h"
#include "CommandArgs.generated.h"

USTRUCT()
struct FCommandArgs
{

    GENERATED_BODY()

	void* args;
	SIZE_T size;
	int nArgs;

	inline FCommandArgs() : args(nullptr), size(0), nArgs(0) {}

	inline ~FCommandArgs()
	{
		// TODO for some reason I had this in an impl file
		// for posterity, ensure this is actually getting hit once the plugin is in a working state
		if (args) FMemory::Free(args);
	}

};