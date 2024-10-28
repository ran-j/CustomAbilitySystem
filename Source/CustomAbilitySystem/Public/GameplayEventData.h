// Copyright (c) 2024 Ranieri Abreu (Ran-j)
//
// This source code is licensed under the MIT License found in the
// LICENSE file in the root directory of this source tree.
#pragma once

#include "CoreMinimal.h"
#include "GameplayEventData.generated.h"

USTRUCT(BlueprintType)
struct FGameplayEventData
{
    GENERATED_BODY()

public:
    /** The tag identifying the event */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
    FName EventTag;

    /** The instigator of the event */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
    AActor *Instigator;

    /** Optional target of the event */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
    AActor *Target;

    /** Optional event-specific data */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
    UObject *OptionalObject;

    /** Optional float data */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
    float OptionalFloat;

    /** Optional integer data */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
    int32 OptionalInt;
};
