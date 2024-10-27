#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AbilityData.generated.h"

USTRUCT(BlueprintType)
struct FAbilityData : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString AbilityName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Cooldown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Cost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration;
};
