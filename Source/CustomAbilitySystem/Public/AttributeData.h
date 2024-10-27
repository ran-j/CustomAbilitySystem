// Copyright (c) 2024 Ranieri Abreu (Ran-j)
// 
// This source code is licensed under the MIT License found in the
// LICENSE file in the root directory of this source tree.
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
