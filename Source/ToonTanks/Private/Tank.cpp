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
	if (TankPlayerController)//��ȿ���� Ȯ��
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		RotateTurret(HitResult.ImpactPoint);
		HitResult.ImpactPoint; //��Ʈ �̺�Ʈ�� �߻��� �����̽� ��ġ�� ������ �� �ִ�. ���� Ʈ���̽��� ���� ������ �������� ���� HitResult �����
	}

}

void ATank::Move(float Value) // �� �����Ӹ��� value���� ȣ��ȴ�
{
	FVector DeltaLocation = FVector::ZeroVector;
	//X= Value * DeltaTime * Speed;
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this); //�������� x������ 
	AddActorLocalOffset(DeltaLocation,true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation= FRotator::ZeroRotator; //x,y,z��ſ� Pitch,Yaw,Roll�� ����, �⺻���� �ʱ�ȭ ���� �ʴ´� , zeroRotator�� ����ƽ ��� ����
	// Yaw= Value * DeltaTime * TurnRate;
	DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}

