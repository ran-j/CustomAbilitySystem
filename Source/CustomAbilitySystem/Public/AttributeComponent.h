// Copyright (c) 2024 Ranieri Abreu (Ran-j)
// 
// This source code is licensed under the MIT License found in the
// LICENSE file in the root directory of this source tree.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CUSTOMABILITYSYSTEM_API UAttributeComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAttributeComponent();

    /** Get the value of an attribute */
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetAttributeValue(FName AttributeName) const;

    /** Set the value of an attribute */
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    void SetAttributeValue(FName AttributeName, float NewValue);

    /** Modify the value of an attribute (additive) */
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    void ModifyAttributeValue(FName AttributeName, float Delta);

    /** Check if an attribute exists */
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    bool HasAttribute(FName AttributeName) const;

    /** Add a new attribute */
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    void AddAttribute(FName AttributeName, float InitialValue = 0.f);

    /** Remove an attribute */
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    void RemoveAttribute(FName AttributeName);

protected:
    UPROPERTY()
    TMap<FName, float> Attributes;
};
