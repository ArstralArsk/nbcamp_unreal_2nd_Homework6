// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingActor.h"
#include "TimerManager.h"

// Sets default values
AMovingActor::AMovingActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	MovingRange = 1000.0f;
	MovingSpeed = 100.0f;
	ToggleTime = 5.0f;
	GoFront = true;
	bIsVisible = true;
}

// Called when the game starts or when spawned
void AMovingActor::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	GetWorld()->GetTimerManager().SetTimer(ToggleTimerHandle, this, &AMovingActor::ToggleVisibility, ToggleTime, true);
}

// Called every frame
void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();

	float Direction = GoFront ? 1.0f : -1.0f;
	float DeltaMove = MovingSpeed * DeltaTime * Direction;

	FVector NewLocation = CurrentLocation + FVector(DeltaMove, 0, 0);

	if (FMath::Abs(NewLocation.X - StartLocation.X) >= MovingRange)
	{
		GoFront = !GoFront;
		NewLocation = CurrentLocation;
	}

	SetActorLocation(NewLocation);
}

void AMovingActor::ToggleVisibility()
{
	bIsVisible = !bIsVisible;
	StaticMeshComp->SetVisibility(bIsVisible, true);
}
