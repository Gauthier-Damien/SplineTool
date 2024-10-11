// Fill out your copyright notice in the Description page of Project Settings.


#include "Bezier.h"

Bezier::Bezier()
{
}

Bezier::~Bezier()
{
}

FVector Bezier::GetPoint(const FVector& _firstPoint, const FVector& _secondPoint, const FVector& _thirdPoint, const float& _time)
{
	int t = FMath::Clamp(_time, 0.f, 1.f);
	float oneMinusT = 1.f - t;
	return
		oneMinusT * oneMinusT * _firstPoint +
		2.f * oneMinusT * t * _secondPoint +
		t * t * _thirdPoint;
}


FVector Bezier::GetFirstDerivative(const FVector& _firstPoint, const FVector& _secondPoint, const FVector& _thirdPoint, const float& _time)
{
	return 2.f * (1.f - _time) * (_secondPoint - _firstPoint) + 2.f * _time * (_thirdPoint - _secondPoint);
}

FVector Bezier::GetVelocity(const FVector& _firstPoint, const FVector& _secondPoint, const FVector& _thirdPoint, const float& _time)
{
	return GetFirstDerivative(_firstPoint, _secondPoint, _thirdPoint, _time);
}

FVector Bezier::GetPoint(const FVector& _firstPoint, const FVector& _secondPoint, const FVector& _thirdPoint, const FVector& _fourthPoint, const float& _time)
{
	float t = FMath::Clamp(_time,0.f, 1.f);
	float oneMinusT = 1.f - t;

	return
		oneMinusT * oneMinusT * oneMinusT * _firstPoint +
		3.f * oneMinusT * oneMinusT * t * _secondPoint +
		3.f * oneMinusT * t * t * _thirdPoint +
		t * t * t * _fourthPoint;
}

FVector Bezier::GetFirstDerivative(const FVector& _firstPoint, const FVector& _secondPoint, const FVector& _thirdPoint, const FVector& _fourthPoint, const float& _time)
{

	float t = FMath::Clamp(_time, 0.f, 1.f);
	float oneMinusT = 1.f - t;
	return	3.f * oneMinusT * oneMinusT * (_secondPoint - _firstPoint) + 
			6.f * oneMinusT * _time * (_thirdPoint - _secondPoint) + 
			3.f * t* t *(_fourthPoint - _thirdPoint);
}

