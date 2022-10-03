// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.generated.h"

USTRUCT()
struct FGoKartMove
{
	GENERATED_BODY()

	UPROPERTY() float Throttle;
	UPROPERTY() float SteeringThrow;
	UPROPERTY() float DeltaTime;
	UPROPERTY() float Time;

	bool IsValid()
	{
		return FMath::Abs(Throttle) <= 1 && FMath::Abs(SteeringThrow) <= 1;
	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRAZYKARTS_API UGoKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoKartMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SimulateMove(const FGoKartMove& Move);

	void SetVelocity(const FVector& InVelocity);
	FVector GetVelocity();
	
	void SetThrottle(float Value);
	float GetThrottle();
	
	void SetSteeringThrow(float Value);
	float GetSteeringThrow();

	FGoKartMove GetLastMove() { return LastMove; };

private:
	// The mass of the car (kg).
	UPROPERTY(EditAnywhere)
	float Mass = 1000.f;

	// The max drive force when throttle is fully down (N).
	UPROPERTY(EditAnywhere)
	float MaxDriveForce = 10000.f;

	// Minimum radius of the car turning circle at full lock (m).
	UPROPERTY(EditAnywhere)
	float MinTurningRadius = 10.f;

	// Higher means more drag
	UPROPERTY(EditAnywhere)
	float DragCoefficient = 16.f;

	// Higher means more rolling resistance
	UPROPERTY(EditAnywhere)
	float RollingResistanceCoefficient = 0.015f;
	
	FVector Velocity;

	float Throttle;
	float SteeringThrow;

	FGoKartMove LastMove;

	void UpdateLocationFromVelocity(float DeltaTime);
	
	void ApplyRotation(float DeltaTime, float SteeringThrow);

	FVector GetAirResistance();

	FVector GetRollingResistance();

	FGoKartMove CreateMove(float DeltaTime);
};
