// Dark Field


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate=FRotator(0,400,0);
	GetCharacterMovement()->bConstrainToPlane=true;
	//开始的时候就设置到平面
	GetCharacterMovement()->bSnapToPlaneAtStart=true;
	
	bUseControllerRotationPitch=false;
	bUseControllerRotationRoll=false;
	bUseControllerRotationYaw=false;
}
