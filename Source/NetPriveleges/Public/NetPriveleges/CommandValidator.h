#pragma once

#include "CommandExecutionStatus.h"
#include "CommandValidator.generated.h"

UINTERFACE(Blueprintable)
class NETPRIVELEGES_API UCommandValidator : public UInterface
{
    GENERATED_BODY()
};

class ICommandValidator
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface Functions")
    void FooNative();
    virtual void FooNative_Implementation();

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interface Functions")
    void FooImplmentable_Implementation();
};

//UINTERFACE(Blueprintable)
//class NETPRIVELEGES_API UCommandValidator : public UInterface
//{
//
//	GENERATED_BODY()
//
//};
//
//class NETPRIVELEGES_API ICommandValidator
//{
//
//	GENERATED_BODY()
//
//public:
//	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface Functions")
//	UPARAM(DisplayName = "Is Authorized") bool HasCommandAuthorization(const FString& commandString);
//	virtual bool HasCommandAuthorization_Implementation(const FString& commandString);
//
//	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface Functions")
//	void GetAuthorizedCommands(const FString& prefix);
//	virtual void GetAuthorizedCommands_Implementation(const FString& prefix);
//
//	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interface Functions")
//	ECommandExecutionStatus ParseAndExecuteCommand(const FString& commandString, const FString& argString);
//	virtual ECommandExecutionStatus ParseAndExecuteCommand_Implementation(const FString& commandString, const FString& argString);
//
//};