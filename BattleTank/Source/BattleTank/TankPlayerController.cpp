// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController posessing: %s"), *ControlledTank->GetName());
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is goign to line trace
	{
		// UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
		// TODO Tell controlled tank to aim at this point 
	}
}

// Get world location if linetrace through crosshair, true if hits landscape 
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the corsshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY; // initiating the variables 
	GetViewportSize(ViewportSizeX, ViewportSizeY); // filling the variables with the data about a game screen 
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation); // calculating location on a screen by multiplying screen size on crosshairlocation
	// UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString())

		// "De-project" the screen position of the crosshair to a world direction
		FVector LookDirection;
		if (GetLookDirection(ScreenLocation, LookDirection))
		{
			UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
		}

	// Line-trace along that LookDirection, and see what we hit (upto max range)
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{

	FVector CameraWorldLocation; // To be discarded 
	return DeprojectScreenPositionToWorld
	(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}
