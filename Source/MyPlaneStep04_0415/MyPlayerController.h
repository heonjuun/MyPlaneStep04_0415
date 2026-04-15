// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class MYPLANESTEP04_0415_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();


	virtual void OnPossess(APawn* aPawn) override;

	UPROPERTY(EditAnywhere, Category = Inputs)
	TObjectPtr<UInputMappingContext> InputMapping;

	
};
