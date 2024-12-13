// Fill out your copyright notice in the Description page of Project Settings.
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Tank.h"
#include "Tower.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// ��ũ������ �Ÿ� ���� �� 

	if (InFireRange()) 
	{
		RotateTurret(Tank->GetActorLocation());
	}
	
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	//��ũ�� ��� �ҷ�����? ->GetPlayerPawn ���
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	//���� ���� �� Ÿ�̸Ӱ� ����ǵ��� 
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);  //GetWorldTimerManager�� FTimerManager�� ��ȯ�ϰ� �����͸� ��ȯ���� ���� 
}

void ATower::CheckFireCondition()
{
	//�Լ��� ����� ���� Ÿ�̸Ӹ� �����ؼ� Ÿ�̸Ӱ� ����ǰ� ���� �ð��� ������ �Լ��� ȣ��ǵ��� �Ѵ�.
	if (InFireRange())
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}
