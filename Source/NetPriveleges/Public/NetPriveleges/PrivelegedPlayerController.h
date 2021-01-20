// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuthorizationAgent.h"
#include "CommandHandler.h"
#include "CommandValidator.h"
#include "CommandExecutionStatus.h"
#include "PrivelegedPlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NETPRIVELEGES_API APrivelegedPlayerController : public APlayerController, public ICommandHandler, public ICommandValidator
{

	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAuthorizationAgent * AuthorizationComponent;

public:

	UFunction* FindCommand(const FString& commandString) const;

	ECommandExecutionStatus ParseArguments(const UFunction* const command, const FString& argString, FCommandArgs& OutArgs) const;

	void ExecuteCommand(UFunction* const command, const FCommandArgs& commandArgs) const;

	//~ICommandValidator Implementations
	virtual bool HasCommandAuthorization_Implementation(const FString& commandString) override;

	//virtual void GetAuthorizedCommands_Implementation(const FString& prefix) override;

	virtual ECommandExecutionStatus ParseAndExecuteCommand_Implementation(const FString& commandString, const FString& argString) override;
	//~

	virtual void test();
	
};
