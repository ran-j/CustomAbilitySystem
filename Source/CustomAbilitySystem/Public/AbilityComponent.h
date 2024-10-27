#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ability.h"
#include "AbilityComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CUSTOMABILITYSYSTEM_API UAbilityComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAbilityComponent();

    void AddAbility(const FAbility &NewAbility);
    void RemoveAbility(int32 AbilityID);

    bool ActivateAbility(int32 AbilityID);
    bool IsAbilityAvailable(int32 AbilityID) const;

    int32 GetAbilityID(const FString &AbilityName) const;

public:
    void AddTag(FName Tag);
    void RemoveTag(FName Tag);
    bool HasTag(FName Tag) const;

public:
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tags")
    TSet<FName> OwnedTags;

protected:
    TSet<int32> AbilitiesOnCooldown;
    TSet<int32> ActiveAbilities;

    UPROPERTY()
    TMap<int32, FAbility> Abilities;
    TMap<int32, float> CooldownTimers;
    TMap<int32, float> DurationTimers;

    int32 NextAbilityID;

    TMap<FString, int32> InputToAbilityMap;
};
