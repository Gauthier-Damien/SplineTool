// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define LOG(text) UE_LOG(LogTemp, Warning, TEXT(text));
#define LOG(text, ...) UE_LOG(LogTemp, Warning, TEXT(text), __VA_ARGS__);

class GHOSTPROTO_API Bezier
{
public:
	Bezier();
	~Bezier();

	static FVector GetPoint(const FVector& _firstPoint, const FVector& _secondPoint, const FVector& _thirdPoint, const float& _time);
	static FVector GetFirstDerivative(const FVector& _firstPoint, const FVector& _secondPoint, const FVector& _thirdPoint, const float& _time);
	static FVector GetVelocity(const FVector& _firstPoint, const FVector& _secondPoint, const FVector& _thirdPoint, const float& _time);


	static FVector GetPoint(const FVector& _firstPoint, const FVector& _secondPoint, const FVector& _thirdPoint, const FVector& _fourthPoint, const float& _time);
	static FVector GetFirstDerivative(const FVector& _firstPoint, const FVector& _secondPoint, const FVector& _thirdPoint, const FVector& _fourthPoint, const float& _time);

};
