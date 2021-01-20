// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CommandArgs.h"
#include "CommandExecutionStatus.h"
#include "CommandHandler.h"
#include "CommandValidator.h"
#include "AuthorizationAgent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(NetPriveleges, Verbose, All);

//~ Execution Handlers

UCLASS( ClassGroup=(Authorization), meta=(BlueprintSpawnableComponent) )
class NETPRIVELEGES_API UAuthorizationAgent : public UActorComponent, public ICommandHandler, public ICommandValidator
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAuthorizationAgent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	//~ ICommandHandler Implementations
	UFunction* FindCommand(const FString& commandString) const;

	ECommandExecutionStatus ParseArguments(const UFunction* const command, const TArray<FString>& args, FCommandArgs& OutArgs);

	void ExecuteCommand(UFunction* const command, const FCommandArgs& commandArgs);
	//~

	//~ICommandValidator Implementations
	virtual bool HasCommandAuthorization_Implementation(const FString& commandString) override;

	//virtual void GetAuthorizedCommands_Implementation(const FString& prefix) override;

	virtual ECommandExecutionStatus ParseAndExecuteCommand_Implementation(const FString& commandString, const TArray<FString>& args) override;
	//~
		
};