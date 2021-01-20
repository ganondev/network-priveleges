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
	FString funcName(TEXT("Command_"));
	funcName += commandString;

	return FindFunction(FName(*funcName));
}

ECommandExecutionStatus UAuthorizationAgent::ParseArguments(const UFunction* const command, const FString& argString, FCommandArgs& OutArgs)
{

	check(command);
	check(!OutArgs.nArgs);

	void* argumentBuffer = FMemory::MallocZeroed(command->ParmsSize);

	if (!argumentBuffer) return ECommandExecutionStatus::NonUserError;

	FString remainingArgs = argString.TrimStartAndEnd();

	for (TFieldIterator<FProperty> PropertyIterator(command); PropertyIterator; ++PropertyIterator, OutArgs.nArgs++)
	{

		//TODO handle default parameters

		FString arg;
		if (remainingArgs.Split(FString(TEXT(" ")), &arg, &remainingArgs, ESearchCase::IgnoreCase, ESearchDir::FromEnd))
		{
			remainingArgs.TrimEndInline();
		}
		else if (remainingArgs.IsEmpty()) goto param_miscount;
		else arg = remainingArgs;

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

	FMemory::Free(argumentBuffer);
	UE_LOG(NetPriveleges, Error, TEXT("Command \"%s\" requires %d arguments but too few (%d) were provided"), TEXT("test"), command->NumParms, OutArgs.nArgs);
	return ECommandExecutionStatus::ParameterMiscount;

invalid_param:
	FMemory::Free(argumentBuffer);
	UE_LOG(NetPriveleges, Error, TEXT("Invalid argument type provided"));
	return ECommandExecutionStatus::InvalidParameter;
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

//bool UAuthorizationAgent::HasCommandAuthorization_Implementation(const FString& commandString)
//{
//	// TODO
//	return true;
//}
//
//void UAuthorizationAgent::GetAuthorizedCommands_Implementation(const FString& prefix)
//{
//	// TODO
//}
//
//ECommandExecutionStatus UAuthorizationAgent::ParseAndExecuteCommand_Implementation(const FString& commandString, const FString& argString)
//{
//	// TODO
//	return ECommandExecutionStatus::UnkownError;
//}