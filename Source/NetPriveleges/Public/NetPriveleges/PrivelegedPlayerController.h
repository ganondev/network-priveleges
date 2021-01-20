// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuthorizationAgent.h"
#include "PrivelegedPlayerController.generated.h"

//~ Execution Handlers

UCLASS()
class NETPRIVELEGES_API APrivlegedPlayerController : public APlayerController
{
	
	GENERATED_BODY()
	
protected:

	UPROPERTY()
	class UAuthorizationAgent * authorizationAgent;

};

//~