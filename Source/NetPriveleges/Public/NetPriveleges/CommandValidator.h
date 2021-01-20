#pragma once

#include "CoreMinimal.h"
#include "CommandExecutionStatus.h"
#include "CommandValidator.generated.h"

UINTERFACE(Blueprintable)
class NETPRIVELEGES_API UCommandValidator : public UInterface
{
    GENERATED_BODY()
};

class ICommandValidator
{

    GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Network Priveleges - Commands")
	UPARAM(DisplayName = "Is Authorized") bool HasCommandAuthorization(const FString& commandString);
	virtual bool HasCommandAuthorization_Implementation(const FString& commandString);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Network Priveleges - Commands")
	void GetAuthorizedCommands(const FString& prefix);
	virtual void GetAuthorizedCommands_Implementation(const FString& prefix);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Network Priveleges - Commands")
	ECommandExecutionStatus ParseAndExecuteCommand(const FString& commandString, const FString& argString);
	virtual ECommandExecutionStatus ParseAndExecuteCommand_Implementation(const FString& commandString, const FString& argString);

};