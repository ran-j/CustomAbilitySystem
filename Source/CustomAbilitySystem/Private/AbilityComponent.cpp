#include "../Public/AbilityComponent.h"

#include "../Public/Ability.h"
#include "../Public/GameplayEventData.h"
#include "../Public/GameplayEventManager.h"

#include "GameFramework/Actor.h"

UAbilityComponent::UAbilityComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetComponentTickEnabled(false); // we start as tick disabled until we have abilities to track
    NextAbilityID = 1;
}

void UAbilityComponent::AddAbility(const FAbility &NewAbility)
{
    int32 AssignedID = NewAbility.AbilityID > 0 ? NewAbility.AbilityID : NextAbilityID++;
    FAbility AbilityToAdd = NewAbility;
    AbilityToAdd.AbilityID = AssignedID;

    Abilities.Add(AssignedID, AbilityToAdd);
    InputToAbilityMap.Add(AbilityToAdd.AbilityName, AssignedID);
}

void UAbilityComponent::RemoveAbility(int32 AbilityID)
{
    if (!Abilities.Contains(AbilityID))
    {
        return;
    }
    Abilities.Remove(AbilityID);
    InputToAbilityMap.Remove(Abilities[AbilityID].AbilityName);
    AbilitiesOnCooldown.Remove(AbilityID);
    ActiveAbilities.Remove(AbilityID);
    CooldownTimers.Remove(AbilityID);
    DurationTimers.Remove(AbilityID);
}

bool UAbilityComponent::ActivateAbility(int32 AbilityID)
{
    if (!IsAbilityAvailable(AbilityID))
    {
        return false;
    }

    const FAbility *Ability = Abilities.Find(AbilityID);
    if (!Ability)
    {
        return false;
    }

    for (const FName &BlockedTag : Ability->ActivationBlockedTags)
    {
        if (HasTag(BlockedTag))
        {
            UE_LOG(LogTemp, Warning, TEXT("Cannot activate ability %s due to blocked tag: %s"), *Ability->AbilityName, *BlockedTag.ToString());
            return false;
        }
    }

    for (const FName &RequiredTag : Ability->ActivationRequiredTags)
    {
        if (!HasTag(RequiredTag))
        {
            UE_LOG(LogTemp, Warning, TEXT("Cannot activate ability %s because required tag is missing: %s"), *Ability->AbilityName, *RequiredTag.ToString());
            return false;
        }
    }

    for (const FName &GrantedTag : Ability->GrantedTags)
    {
        AddTag(GrantedTag);
    }

    if (!Ability->ActivationEventTag.IsNone())
    {
        FGameplayEventData EventData;
        EventData.EventTag = Ability->ActivationEventTag;
        EventData.Instigator = GetOwner();
        //EventData.OptionalObject = Ability; //TODO ??
        EventData.OptionalInt = AbilityID;
        UGameplayEventManager::Get()->BroadcastEvent(EventData);
    }

    // { // old code
    //     ActiveAbilities.Add(AbilityID);

    //     Ability->OnActivate.ExecuteIfBound(GetOwner());

    //     if (Ability->Duration > 0.f)
    //     {
    //         DurationTimers.Add(AbilityID, Ability->Duration);
    //     }
    // }
    Ability->OnActivate.ExecuteIfBound(GetOwner());
    if (Ability->Duration > 0.f)
    {
        ActiveAbilities.Add(AbilityID);
        DurationTimers.Add(AbilityID, Ability->Duration);
    }

    AbilitiesOnCooldown.Add(AbilityID);
    CooldownTimers.Add(AbilityID, Ability->Cooldown);

    if (!IsComponentTickEnabled())
    {
        SetComponentTickEnabled(true);
    }

    return true;
}

bool UAbilityComponent::IsAbilityAvailable(int32 AbilityID) const
{
    bool bOnCooldown = AbilitiesOnCooldown.Contains(AbilityID);
    bool bHasAbility = Abilities.Contains(AbilityID);
    return bHasAbility && !bOnCooldown;
}

int32 UAbilityComponent::GetAbilityID(const FString &AbilityName) const
{
    return InputToAbilityMap.FindRef(*AbilityName);
}

void UAbilityComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    if (CooldownTimers.Num() == 0 && DurationTimers.Num() == 0)
    {
        SetComponentTickEnabled(false);
        return;
    }

    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Update cooldown timers
    for (auto It = CooldownTimers.CreateIterator(); It; ++It)
    {
        It.Value() -= DeltaTime;
        if (It.Value() <= 0.f)
        {
            // Remove from cooldown
            AbilitiesOnCooldown.Remove(It.Key());
            It.RemoveCurrent();
        }
    }

    // Update duration timers
    for (auto It = DurationTimers.CreateIterator(); It; ++It)
    {
        It.Value() -= DeltaTime;
        if (It.Value() <= 0.f)
        {
            int32 AbilityID = It.Key();

            // Deactivate ability
            ActiveAbilities.Remove(AbilityID);

            // Call the deactivation delegate
            const FAbility *Ability = Abilities.Find(AbilityID);
            if (Ability)
            {
                Ability->OnDeactivate.ExecuteIfBound(GetOwner());

                // Remove granted tags
                for (const FName &GrantedTag : Ability->GrantedTags)
                {
                    RemoveTag(GrantedTag);
                }
            }

            It.RemoveCurrent();
        }
    }
}

void UAbilityComponent::AddTag(FName Tag)
{
    OwnedTags.Add(Tag);
}

void UAbilityComponent::RemoveTag(FName Tag)
{
    OwnedTags.Remove(Tag);
}

bool UAbilityComponent::HasTag(FName Tag) const
{
    return OwnedTags.Contains(Tag);
}