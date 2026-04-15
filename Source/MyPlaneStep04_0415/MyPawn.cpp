// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include"Components/BoxComponent.h"
#include"Components/ArrowComponent.h"
#include"Components/StaticMeshComponent.h"
#include"Camera/CameraComponent.h"
#include"GameFramework/SpringArmComponent.h"
#include"GameFrameWork/FloatingPawnMovement.h"
#include"Kismet/GameplayStatics.h"
#include"MyStaticMeshComponent.h"
#include"EnhancedInputComponent.h"

#include"MyActor.h"



// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//엔진님에게 요청을 한다. 다 NewObject다
	//CreateDefaultSubobject에서 해당작업 수행해줌
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(40.0f,44.2f,12.4f));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));

	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	PropellarLeft = CreateDefaultSubobject<UMyStaticMeshComponent>(TEXT("PropellarLeft"));
	PropellarLeft->SetupAttachment(Body);

	PropellarRight = CreateDefaultSubobject<UMyStaticMeshComponent>(TEXT("PropellarRight"));
	PropellarRight->SetupAttachment(Body);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));

	if (SM_Propeller.Succeeded())
	{
		PropellarLeft->SetStaticMesh(SM_Propeller.Object);
		PropellarRight->SetStaticMesh(SM_Propeller.Object);
	}
	PropellarLeft->SetRelativeLocation(FVector(37.1f, -21.4f, 0.5f));
	PropellarRight->SetRelativeLocation(FVector(37.1f, 21.4f, 0.5f));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);
	Arrow->SetRelativeLocation(FVector(200.f, 0, 0));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);
	SpringArm->SocketOffset = FVector(0, 0, 33.33f);
	SpringArm->TargetArmLength = 150.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	Movement->MaxSpeed = 2000;



	//블푸 클래스에 로켓 기본값 주입
	static ConstructorHelpers::FClassFinder<AMyActor> BP_AMyActor(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_MyActor.BP_MyActor_C'"));
	if (BP_AMyActor.Succeeded())
	{
		RocketTemlate = BP_AMyActor.Class;
	}
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(),BoostValue);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* UIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (UIC)
	{
		UIC->BindAction(IA_Rotate, ETriggerEvent::Triggered, this, &AMyPawn::Rotate);
		UIC->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AMyPawn::Fire);
		UIC->BindAction(IA_Boost, ETriggerEvent::Triggered, this, &AMyPawn::Boost);
		UIC->BindAction(IA_Boost, ETriggerEvent::Completed, this, &AMyPawn::Unboost);
	}
}


void AMyPawn::Rotate(const FInputActionValue& Value)
{
	FVector2D Rot = Value.Get<FVector2D>();
	Rot = Rot * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f;

	AddActorLocalRotation(FRotator(Rot.Y,0,Rot.X));
}


void AMyPawn::Fire(const FInputActionValue& Value)
{
	GetWorld()->SpawnActor<AMyActor>(RocketTemlate,Arrow->K2_GetComponentToWorld());
}


void AMyPawn::Boost(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Boost %d"), Value.Get<bool>());
	BoostValue = 1.0f;
}

void AMyPawn::Unboost(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Unboost"));
	BoostValue = 0.5f;
}



