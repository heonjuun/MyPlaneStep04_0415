// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"



// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	Body = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);
	Body->SetRelativeRotation(FRotator(- 90.0f, 0, 0));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/Rocket/Meshes/SM_Rocket.SM_Rocket'"));

	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->InitialSpeed = 2000.0f;
	Movement->MaxSpeed = 2000.0f;
	Movement->ProjectileGravityScale = 0.0f;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AMyActor::ProcessActorBeginOverlap);

	SetLifeSpan(3.0f);
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::ProcessActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{

	UE_LOG(LogTemp,Warning,TEXT("ProcessBeginActorOverlap"));
}

