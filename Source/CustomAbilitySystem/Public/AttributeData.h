#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AttributeData.generated.h"

USTRUCT(BlueprintType)
struct FAttributeData : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AttributeName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InitialValue;
};
