// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterGideon.h"

ACharacterGideon::ACharacterGideon()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(
		TEXT("SkeletalMesh'/Game/ParagonGideon/Characters/Heroes/Gideon/Meshes/Gideon.Gideon'"));
	if (skeletalMesh.Succeeded())
	{
		GetMesh()->SkeletalMesh = skeletalMesh.Object;
	}

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90.0f, 0));


	static ConstructorHelpers::FClassFinder<UAnimInstance> anim(
		TEXT("AnimBlueprint'/Game/Blueprints/Characters/Animations/ABP_Gideon.ABP_Gideon_C'"));
	if (anim.Succeeded())
	{
		GetMesh()->SetAnimClass(anim.Class);
	}
}
