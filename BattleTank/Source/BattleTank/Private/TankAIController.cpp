// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledAITank = GetControlledTank();
	if (!ControlledAITank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AiController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AiController posessing: %s"), *ControlledAITank->GetName());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
