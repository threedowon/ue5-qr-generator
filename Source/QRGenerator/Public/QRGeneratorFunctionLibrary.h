// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "QRGeneratorFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class QRGENERATOR_API UQRGeneratorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	public:
        UFUNCTION(BlueprintCallable, Category="QR")
        static UTexture2D* GenerateQRCode(const FString& Url, int32 Size, FColor ForegroundColor, FColor BackgroundColor);
};
