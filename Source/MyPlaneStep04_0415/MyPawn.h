// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UArrowComponent;
class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;
class UMyStaticMeshComponent;

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

	void RotatePropeller(USceneComponent* Where, float RotationSpeed);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components) //visible은 C++변수를 블루프린트에서 보기 위해 사용
	TObjectPtr<UBoxComponent> Box;

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

	void Pitch(float Value);

	void Roll(float Value);

	void Fire();

	void Boost();

	void Unboost();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float MoveSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float RotationSpeed = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float BoostValue = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float PropellerRotationSpeed = 7200.0f;






};
