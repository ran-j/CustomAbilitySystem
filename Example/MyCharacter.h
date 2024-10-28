#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilityComponent.h"
#include "AttributeComponent.h"
#include "MyCharacter.generated.h"

namespace GameplayTags
{
    // Ability Tags
    static const FName Ability_Fireball_Weapon = FName("Ability.FireballStaff");
    static const FName Ability_Heal = FName("Ability.Heal");

    // Effect Tags
    static const FName Effect_FireDamage = FName("Effect.FireDamage");
    static const FName Effect_Healing = FName("Effect.Healing");

    // Character State Tags
    static const FName State_Stunned = FName("State.Stunned");
    static const FName State_ImmuneToFire = FName("State.ImmuneToFire");
}

UCLASS()
class AMyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMyCharacter();

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
    UAbilityComponent *AbilityComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
    UAttributeComponent *AttributeComponent;

protected:
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

protected:
    void ActivateAbility1();
    void ActivateAbility2();
    void ActivateAbility3();
    void ActivateAbility4();

    void HealActivate(AActor *OwnerActor);

    void FireballActivate(AActor *OwnerActor);

    void DashActivate(AActor *OwnerActor);
    void DashDeactivate(AActor *OwnerActor);

    void JumpBoostActivate(AActor *OwnerActor);
    void JumpBoostDeactivate(AActor *OwnerActor);

    void ShieldActivate(AActor *OwnerActor);
    void ShieldDeactivate(AActor *OwnerActor);

    UFUNCTION()
    void OnFireballCast(const FGameplayEventData &EventData);
};
