// Fill out your copyright notice in the Description page of Project Settings.


#include "AuthorizationAgent.h"

DEFINE_LOG_CATEGORY(NetPriveleges);

// Sets default values for this component's properties
UAuthorizationAgent::UAuthorizationAgent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UAuthorizationAgent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

UFunction* UAuthorizationAgent::FindCommand(const FString& commandString) const
{
	return FindFunction(FName(*commandString));
}

ECommandExecutionStatus UAuthorizationAgent::ParseArguments(const UFunction* const command, const TArray<FString>& args, FCommandArgs& OutArgs)
{

	check(command);
	check(!OutArgs.nArgs);
	
	if (command->NumParms != args.Num()) goto param_miscount;

	void* argumentBuffer = FMemory::MallocZeroed(command->ParmsSize);
	if (!argumentBuffer) goto non_user_error;

	for (TFieldIterator<FProperty> PropertyIterator(command); PropertyIterator; ++PropertyIterator, OutArgs.nArgs++)
	{

		//TODO handle default parameters

		FString arg = args[OutArgs.nArgs];
		arg.TrimStartAndEndInline();
		FProperty* Property = *PropertyIterator;
		FFieldClass* c = Property->GetClass();
		if (c->HasAnyCastFlags(FStrProperty::StaticClassCastFlagsPrivate()))
		{

			FString* argPtr = PropertyIterator->ContainerPtrToValuePtr<FString>(argumentBuffer);
			*argPtr = arg;

		}
		else if (c->HasAnyCastFlags(FIntProperty::StaticClassCastFlagsPrivate()))
		{
			if (arg.IsNumeric())
			{
				int intArg = FCString::Atoi(*arg);
				int* argPtr = PropertyIterator->ContainerPtrToValuePtr<int>(argumentBuffer);
				*argPtr = intArg;
			}
			else goto invalid_param;
		}

	}

	OutArgs.args = argumentBuffer;
	OutArgs.size = command->ParmsSize;

	return ECommandExecutionStatus::Parsed;

param_miscount:
	UE_LOG(NetPriveleges, Error, TEXT("The issued command requires %d arguments but too few (%d) were provided"), command->NumParms, OutArgs.nArgs);
	return ECommandExecutionStatus::ParameterMiscount;

invalid_param:
	FMemory::Free(argumentBuffer);
	UE_LOG(NetPriveleges, Error, TEXT("Invalid argument type provided"));
	return ECommandExecutionStatus::InvalidParameter;

non_user_error:
	UE_LOG(NetPriveleges, Error, TEXT("Failed to allocate the argument buffer."));
	return ECommandExecutionStatus::NonUserError;
}

void UAuthorizationAgent::ExecuteCommand(UFunction* const command, const FCommandArgs& commandArgs)
{

	checkf(command, TEXT("Valid UFunction * is required."));
	checkf(command->NumParms == commandArgs.nArgs, TEXT("The command expects %d arguments but the argument structure reported %d."), command->NumParms, commandArgs.size);
	checkf(command->NumParms == 0 || commandArgs.args, TEXT("The command expects arguments but was given a buffer at %d"), commandArgs.args);
	checkf(commandArgs.size == command->ParmsSize, TEXT("Command expected parameter buffer size of %d but got one of size %d"), command->ParmsSize, commandArgs.size);

	UE_LOG(LogTemp, Display, TEXT("Chat command invoking with %d arguments."), /**commandString,*/ commandArgs.nArgs)
	ProcessEvent(command, commandArgs.args);

}

bool UAuthorizationAgent::HasCommandAuthorization_Implementation(const FString& commandString)
{

	UFunction * targetFunction = FindCommand(commandString);

	return (bool)targetFunction;

}

//void UAuthorizationAgent::GetAuthorizedCommands_Implementation(const FString& prefix)
//{
//	// TODO
//}

/* TODO Maybe do a separate parse-only function for validating arguments?*/
ECommandExecutionStatus UAuthorizationAgent::ParseAndExecuteCommand_Implementation(const FString& commandString, const TArray<FString>& args)
{

	ECommandExecutionStatus result = ECommandExecutionStatus::NotAuthorized;

	if (UFunction * command = FindCommand(commandString))
	{

		FCommandArgs outArgs;
		if ((result = ParseArguments(command, args, outArgs)) == ECommandExecutionStatus::Parsed)
		{

			/* TODO Can we figure out if this failed/would fail? */
			ExecuteCommand(command, outArgs);
			result = ECommandExecutionStatus::Successful;

		}

	}
	
	return result;

}