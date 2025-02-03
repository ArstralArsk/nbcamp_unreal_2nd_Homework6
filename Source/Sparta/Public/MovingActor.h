// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingActor.generated.h"

UCLASS()
class SPARTA_API AMovingActor : public AActor
{
	GENERATED_BODY()

public:
	AMovingActor();

protected:
	virtual void BeginPlay() override;

	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MovingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MovingRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float ToggleTime;

	bool GoFront;
	bool bIsVisible;

	FTimerHandle ToggleTimerHandle;
	FVector StartLocation;

	void ToggleVisibility();

public:
	virtual void Tick(float DeltaTime) override;
};
