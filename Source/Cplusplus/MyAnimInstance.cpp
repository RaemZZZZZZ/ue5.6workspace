#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterTrajectoryComponent.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// Lấy chủ sở hữu của bộ xương này ngay khi bắt đầu
	CharacterRef = Cast<ACharacter>(TryGetPawnOwner());

	if (CharacterRef)
	{
		MovementComponentRef = CharacterRef->GetCharacterMovement();
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CharacterRef)
	{
		// --- LOGIC TURN IN PLACE ---
		FRotator ControlRot = CharacterRef->GetControlRotation();
		FRotator ActorRot = CharacterRef->GetActorRotation();
		RootYawOffset = FMath::ClampAngle(ControlRot.Yaw - ActorRot.Yaw, -180.0f, 180.0f);

		if (CurrentTurnState == ETurnState::NotTurning)
		{
			if (RootYawOffset > 45.0f && RootYawOffset <= 90.0f)
			{
				CurrentTurnState = ETurnState::TurnRight45;
			}
			else if (RootYawOffset > 90.0f)
			{
				CurrentTurnState = ETurnState::TurnRight90;
			}
			else if (RootYawOffset < -45.0f && RootYawOffset >= -90.0f)
			{
				CurrentTurnState = ETurnState::TurnLeft45;
			}
			else if (RootYawOffset < -90.0f)
			{
				CurrentTurnState = ETurnState::TurnLeft90;
			}
		}

		if (CurrentTurnState != ETurnState::NotTurning)
		{
			float TurnSpeed = (CurrentTurnState == ETurnState::TurnRight90 || CurrentTurnState == ETurnState::TurnLeft90) ? 8.0f : 5.0f;

			FRotator NewActorRot = ActorRot;
			NewActorRot.Yaw = FMath::FInterpTo(ActorRot.Yaw, ControlRot.Yaw, DeltaSeconds, TurnSpeed);
			CharacterRef->SetActorRotation(NewActorRot);

			if (FMath::Abs(RootYawOffset) < 5.0f)
			{
				CurrentTurnState = ETurnState::NotTurning;
				RootYawOffset = 0.0f;
			}
		}

		if (MovementComponentRef)
		{
			FVector Velocity = CharacterRef->GetVelocity();
			Velocity.Z = 0.0f;
			GroundSpeed = Velocity.Size();

			bIsFalling = MovementComponentRef->IsFalling();
		}
	}
}