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
	inline virtual bool HasCommandAuthorization_Implementation(const FString& commandString)
	{
		// TODO log unimplemented
		return false;
	}
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Network Priveleges - Commands")
	void GetAuthorizedCommands(const FString& prefix);
	inline virtual void GetAuthorizedCommands_Implementation(const FString& prefix)
	{
		// TODO log unimplemented
	}
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Network Priveleges - Commands")
	ECommandExecutionStatus ParseAndExecuteCommand(const FString& commandString, const TArray<FString>& args);
	inline virtual ECommandExecutionStatus ParseAndExecuteCommand_Implementation(const FString& commandString, const TArray<FString>& args)
	{
		// TODO log unimplemented
		return ECommandExecutionStatus::UnknownError;
	}

};