// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"



ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<APlayerController>(GetController());
	
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TankPlayerController)//유효한지 확인
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		RotateTurret(HitResult.ImpactPoint);
		HitResult.ImpactPoint; //히트 이벤트가 발생한 스페이스 위치를 가져올 수 있다. 라인 트레이스에 대한 정보를 가져오기 위해 HitResult 사용함
	}

}

void ATank::Move(float Value) // 매 프레임마다 value값과 호출된다
{
	FVector DeltaLocation = FVector::ZeroVector;
	//X= Value * DeltaTime * Speed;
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this); //움직임은 x축으로 
	AddActorLocalOffset(DeltaLocation,true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation= FRotator::ZeroRotator; //x,y,z대신에 Pitch,Yaw,Roll이 존재, 기본값은 초기화 되지 않는다 , zeroRotator은 스태틱 멤버 변수
	// Yaw= Value * DeltaTime * TurnRate;
	DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}


