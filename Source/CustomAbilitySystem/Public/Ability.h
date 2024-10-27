#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Ability.generated.h"

DECLARE_DELEGATE_OneParam(FAbilityEffectDelegate, AActor *);

USTRUCT(BlueprintType)
struct FAbility
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    int32 AbilityID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    FString AbilityName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    float Cooldown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    float Cost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    float Duration;

    /** Tags associated with this ability */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    TSet<FName> AbilityTags;

    /** Tags that this ability grants to the owner when activated */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    TSet<FName> GrantedTags;

    /** Tags that this ability requires on the target to activate */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    TSet<FName> ActivationRequiredTags;

    /** Tags that prevent this ability from activating if present on the target */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    TSet<FName> ActivationBlockedTags;

    /** Delegate called when the ability is activated */
    FAbilityEffectDelegate OnActivate;

    /** Delegate called when the ability is deactivated */
    FAbilityEffectDelegate OnDeactivate;

    FAbility()
        : AbilityID(0), AbilityName(TEXT("")), Cooldown(0.f), Cost(0.f), Duration(0.f), AbilityTags(TSet<FName>()), GrantedTags(TSet<FName>()), ActivationRequiredTags(TSet<FName>()), ActivationBlockedTags(TSet<FName>())
    {
    }
};