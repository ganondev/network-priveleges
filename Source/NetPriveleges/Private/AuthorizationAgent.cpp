// Fill out your copyright notice in the Description page of Project Settings.


#include "AuthorizationAgent.h"

// Sets default values for this component's properties
UAuthorizationAgent::UAuthorizationAgent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAuthorizationAgent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAuthorizationAgent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

