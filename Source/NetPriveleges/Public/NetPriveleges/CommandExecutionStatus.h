#pragma once

#include "CoreMinimal.h"
#include "CommandExecutionStatus.generated.h"

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