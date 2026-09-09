#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PoseSearch/PoseSearchTrajectoryTypes.h" 
#include "MyAnimInstance.generated.h"

UENUM(BlueprintType)
enum class ETurnState : uint8
{
	NotTurning      UMETA(DisplayName = "Not Turning"),
	TurnLeft45      UMETA(DisplayName = "Turn Left 45"),
	TurnRight45     UMETA(DisplayName = "Turn Right 45"),
	TurnLeft90      UMETA(DisplayName = "Turn Left 90"),
	TurnRight90     UMETA(DisplayName = "Turn Right 90")
};

class ACharacter;
class UCharacterMovementComponent;

UCLASS()
class CPLUSPLUS_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Turn In Place")
	float RootYawOffset;

	UPROPERTY(BlueprintReadOnly, Category = "Turn In Place")
	ETurnState CurrentTurnState = ETurnState::NotTurning;


	UPROPERTY(BlueprintReadOnly, Category = "Character")
	ACharacter* CharacterRef;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	UCharacterMovementComponent* MovementComponentRef;


	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsFalling;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon Sway")
	float SwayYaw;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon Sway")
	float SwayPitch;

	FRotator LastControlRotation;
};