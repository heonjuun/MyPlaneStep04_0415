// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <EnhancedInputLibrary.h>

#include"InputAction.h"

#include "MyPawn.generated.h"


class UBoxComponent;
class UStaticMeshComponent;
class UArrowComponent;
class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;
class UMyStaticMeshComponent;
class UInputAction;
class AMyActor;
UCLASS()
class MYPLANESTEP04_0415_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*void RotatePropeller(USceneComponent* Where, float RotationSpeed);*/

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Rotate(const FInputActionValue& Value);

	void Fire(const FInputActionValue& Value);

	void Boost(const FInputActionValue& Value);

	void Unboost(const FInputActionValue& Value);



	


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components) //visible은 C++변수를 블루프린트에서 보기 위해 사용
	TObjectPtr<UBoxComponent> Box;  // UBoxComponent *Box와 같지만 더효과적인 걸 사용하기위해 toObjectPtr함수를 사용

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UMyStaticMeshComponent> PropellarLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UMyStaticMeshComponent> PropellarRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UArrowComponent> Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UFloatingPawnMovement> Movement;




	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inputs)
	TObjectPtr<UInputAction> IA_Boost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inputs)
	TObjectPtr<UInputAction> IA_Rotate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inputs)
	TObjectPtr<UInputAction> IA_Fire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Data)
	TSubclassOf<AMyActor> RocketTemlate;

	float BoostValue = 0.5f;







};
