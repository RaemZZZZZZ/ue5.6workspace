#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterTrajectoryComponent.h" // Nhúng thư viện Trajectory

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

	if (CharacterRef && MovementComponentRef)
	{
		FVector Velocity = CharacterRef->GetVelocity();
		Velocity.Z = 0.0f;
		GroundSpeed = Velocity.Size();

		bIsFalling = MovementComponentRef->IsFalling();

		if (UCharacterTrajectoryComponent* TrajComp = CharacterRef->FindComponentByClass<UCharacterTrajectoryComponent>())
		{
			CharacterTrajectory = TrajComp->GetTrajectory();
		}
	}
}