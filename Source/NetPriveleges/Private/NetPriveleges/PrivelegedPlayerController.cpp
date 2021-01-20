// Fill out your copyright notice in the Description page of Project Settings.


#include "PrivelegedPlayerController.h"

UFunction* APrivelegedPlayerController::FindCommand(const FString& commandString) const
{
    return AuthorizationComponent->FindCommand(commandString);
}

ECommandExecutionStatus APrivelegedPlayerController::ParseArguments(const UFunction* const command, const FString& argString, FCommandArgs& OutArgs) const
{
    return AuthorizationComponent->ParseArguments(command, argString, OutArgs);
}

void APrivelegedPlayerController::ExecuteCommand(UFunction* const command, const FCommandArgs& commandArgs) const
{
    AuthorizationComponent->ExecuteCommand(command, commandArgs);
}

bool APrivelegedPlayerController::HasCommandAuthorization_Implementation(const FString& commandString)
{
    return AuthorizationComponent->HasCommandAuthorization(commandString);
}

ECommandExecutionStatus APrivelegedPlayerController::ParseAndExecuteCommand_Implementation(const FString& commandString, const FString& argString)
{
    return AuthorizationComponent->Execute_ParseAndExecuteCommand(AuthorizationComponent, commandString, argString);
}

void APrivelegedPlayerController::test()
{

}