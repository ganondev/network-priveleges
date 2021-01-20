// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AuthorizationAgent.generated.h"

//~ Execution data

UENUM(BlueprintType)
enum class ECommandExecutionStatus : uint8
{

	/* The desired command could not be found for this user. The command either does not exist or the user is not authorized to execute it. */
	NotAuthorized		UMETA(DisplayName = "Not Authorized"),

	ParameterMiscount	UMETA(DisplayName = "Parameter Miscount"),

	InvalidParameter	UMETA(DisplayName = "Invalid Parameter"),

	Parsed				UMETA(DisplayName = "Parsed"),

	UnkownError			UMETA(DisplayName = "Unknown Error"),

	/* An error occurred as a result of circumstances beyond this user's control, such as a lack of available memory. */
	NonUserError		UMETA(DisplayName = "Non User Error"),

	Successful			UMETA(DisplayName = "Successful")

};

USTRUCT()
struct NETPRIVELEGES_API FChatCommandArgs
{

	GENERATED_BODY();

	void* args;
	SIZE_T size;
	int nArgs;

	inline FChatCommandArgs() : args(nullptr), size(0), nArgs(0) {}

	~FChatCommandArgs();

};

//~

//~ Execution Handlers

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class NETPRIVELEGES_API UCommandHandler : public UInterface
{
	GENERATED_BODY()
};

class NETPRIVELEGES_API ICommandHandler
{
	GENERATED_BODY()

public:

	UFunction* FindCommand(const FString& commandString) const;

	ECommandExecutionStatus ParseArguments(const UFunction* const command, const FString& argString, FChatCommandArgs& OutArgs) const;

	void ExecuteCommand(const UFunction* const command, const FChatCommandArgs& commandArgs) const;

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//UPARAM(DisplayName = "Is Authorized") bool HasCommandAuthorization(const FString& commandString);

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//void GetAuthorizedCommands(const FString& prefix);

	/* TODO Submit PR to UHT that let's you declare these as inline virtual*/
	/* TODO also submit PR that allows you to put UPARAM on virtual returns*/
	UFUNCTION(BlueprintCallable)
		virtual inline ECommandExecutionStatus ParseAndExecuteCommand(const FString& commandString, const FString& argString)
	{
		checkNoEntry();
		return ECommandExecutionStatus::UnkownError;
	}

};

UINTERFACE(BlueprintType)
class NETPRIVELEGES_API UCommandValidator : public UInterface
{

	GENERATED_BODY()

};

class NETPRIVELEGES_API ICommandValidator
{

	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UPARAM(DisplayName = "Is Authorized") bool HasCommandAuthorization(const FString& commandString);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GetAuthorizedCommands(const FString& prefix);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	ECommandExecutionStatus ParseAndExecuteCommand(const FString& commandString, const FString& argString);

};

UCLASS( ClassGroup=(Authorization), meta=(BlueprintSpawnableComponent) )
class NETPRIVELEGES_API UAuthorizationAgent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAuthorizationAgent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

		
};

//~