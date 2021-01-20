#pragma once

#include "CoreMinimal.h"
#include "CommandExecutionStatus.h"
#include "CommandHandler.generated.h"

UINTERFACE()
class NETPRIVELEGES_API UCommandHandler : public UInterface
{
	GENERATED_BODY()
};

class NETPRIVELEGES_API ICommandHandler
{
	GENERATED_BODY()

public:

	UFunction* FindCommand(const FString& commandString) const;

	ECommandExecutionStatus ParseArguments(const UFunction* const command, const FString& argString, FCommandArgs& OutArgs) const;

	void ExecuteCommand(const UFunction* const command, const FCommandArgs& commandArgs) const;

};