#pragma once

#include "CoreMinimal.h"
#include "CommandExecutionStatus.generated.h"

UENUM(BlueprintType)
enum class ECommandExecutionStatus : uint8
{

	/* The desired command could not be found for this user. The command either does not exist or the user is not authorized to execute it. */
	NotAuthorized		UMETA(DisplayName = "Not Authorized"),

	/* The number of arguments given did not match the number of parameters taken by the command */
	ParameterMiscount	UMETA(DisplayName = "Parameter Miscount"),

	/* One or more arguments were not parsable into a parameter, e.g. an alphanumeric string for an integer parameter */
	InvalidParameter	UMETA(DisplayName = "Invalid Parameter"),

	/* The given command was found and its arguments were successfully parsed. This is only used in C++ and would never come back to a blueprint graph. */
	Parsed				UMETA(DisplayName = "Parsed"),

	/* An error occurred due to unclear circumstances. Currently only results from calling unimplemented interface methods. */
	UnknownError		UMETA(DisplayName = "Unknown Error"),

	/* An error occurred as a result of circumstances beyond this user's control, such as a lack of available memory. */
	NonUserError		UMETA(DisplayName = "Non User Error"),

	/* The issued command and arguments were successfully parsed and executed. */
	Successful			UMETA(DisplayName = "Successful")

};