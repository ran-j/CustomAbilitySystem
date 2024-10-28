#include "MyCharacter.h"
#include "Ability.h"

AMyCharacter::AMyCharacter()
{
    AbilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComponent"));
    AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Add attributes
    AttributeComponent->AddAttribute("Health", 100.f);
    AttributeComponent->AddAttribute("MaxHealth", 100.f);
    AttributeComponent->AddAttribute("Mana", 50.f);
    AttributeComponent->AddAttribute("MaxMana", 50.f);
    AttributeComponent->AddAttribute("Strength", 10.f);
    AttributeComponent->AddAttribute("Armor", 5.f);

    // Add Dash Ability
    FAbility DashAbility;
    DashAbility.AbilityName = TEXT("Dash");
    DashAbility.Cooldown = 5.f;
    DashAbility.Duration = 0.5f; // Dash lasts 0.5 seconds
    DashAbility.OnActivate = FAbilityEffectDelegate::CreateUObject(this, &AMyCharacter::DashActivate);
    DashAbility.OnDeactivate = FAbilityEffectDelegate::CreateUObject(this, &AMyCharacter::DashDeactivate);
    AbilityComponent->AddAbility(DashAbility);

    // Add Jump Boost Ability
    FAbility JumpBoostAbility;
    JumpBoostAbility.AbilityName = TEXT("JumpBoost");
    JumpBoostAbility.Cooldown = 10.f;
    JumpBoostAbility.Duration = 5.f; // Lasts 5 seconds
    JumpBoostAbility.OnActivate = FAbilityEffectDelegate::CreateUObject(this, &AMyCharacter::JumpBoostActivate);
    JumpBoostAbility.OnDeactivate = FAbilityEffectDelegate::CreateUObject(this, &AMyCharacter::JumpBoostDeactivate);
    AbilityComponent->AddAbility(JumpBoostAbility);

    // Add Shield Ability
    FAbility ShieldAbility;
    ShieldAbility.AbilityName = TEXT("Shield");
    ShieldAbility.Cooldown = 15.f;
    ShieldAbility.Duration = 10.f; // Lasts 10 seconds
    ShieldAbility.OnActivate = FAbilityEffectDelegate::CreateUObject(this, &AMyCharacter::ShieldActivate);
    ShieldAbility.OnDeactivate = FAbilityEffectDelegate::CreateUObject(this, &AMyCharacter::ShieldDeactivate);
    AbilityComponent->AddAbility(ShieldAbility);

    // Add Heal Ability
    FAbility HealAbility;
    HealAbility.AbilityName = TEXT("Heal");
    HealAbility.Cooldown = 10.f;
    HealAbility.Duration = 0.f; // Instant effect
    HealAbility.OnActivate = FAbilityEffectDelegate::CreateUObject(this, &AMyCharacter::HealActivate);
    AbilityComponent->AddAbility(HealAbility);

    // Add Fireball Ability
    FAbility FireballAbility;
    FireballAbility.AbilityName = TEXT("Fireball");
    FireballAbility.Cooldown = 5.f;
    FireballAbility.Duration = 0.f; // Instant effect
    FireballAbility.OnActivate = FAbilityEffectDelegate::CreateUObject(this, &AMyCharacter::FireballActivate);
    FireballAbility.ActivationRequiredTags.Add(GameplayTags::Ability_Fireball_Weapon);
    FireballAbility.GrantedTags.Add(GameplayTags::State_ImmuneToFire);
    AbilityComponent->AddAbility(FireballAbility);

    // event example
    UGameplayEventManager::Get()->AddEventListener("Event.FireballCast", FGameplayEventDelegate::CreateUObject(this, &AMyCharacter::OnFireballCast));
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("Ability1", IE_Pressed, this, &AMyCharacter::ActivateAbility1);
    PlayerInputComponent->BindAction("Ability2", IE_Pressed, this, &AMyCharacter::ActivateAbility2);
    PlayerInputComponent->BindAction("Ability3", IE_Pressed, this, &AMyCharacter::ActivateAbility3);
    PlayerInputComponent->BindAction("Ability4", IE_Pressed, this, &AMyCharacter::ActivateAbility4);
}

void AMyCharacter::ActivateAbility1()
{
    int32 AbilityID = AbilityComponent->GetAbilityID("Dash");
    AbilityComponent->ActivateAbility(AbilityID);
}

void AMyCharacter::ActivateAbility2()
{
    int32 AbilityID = AbilityComponent->GetAbilityID("JumpBoost");
    AbilityComponent->ActivateAbility(AbilityID);
}

void AMyCharacter::ActivateAbility3()
{
    int32 AbilityID = AbilityComponent->GetAbilityID("Shield");
    AbilityComponent->ActivateAbility(AbilityID);
}

void AMyCharacter::ActivateAbility4()
{
    int32 AbilityID = AbilityComponent->GetAbilityID("Fireball");
    AbilityComponent->ActivateAbility(AbilityID);
}

void AMyCharacter::DashActivate(AActor *OwnerActor)
{
    ACharacter *Character = Cast<ACharacter>(OwnerActor);
    if (Character)
    {
        Character->GetCharacterMovement()->MaxWalkSpeed *= 2.0f;
    }
}

void AMyCharacter::DashDeactivate(AActor *OwnerActor)
{
    ACharacter *Character = Cast<ACharacter>(OwnerActor);
    if (Character)
    {
        Character->GetCharacterMovement()->MaxWalkSpeed /= 2.0f;
    }
}

void AMyCharacter::JumpBoostActivate(AActor *OwnerActor)
{
    ACharacter *Character = Cast<ACharacter>(OwnerActor);
    if (Character)
    {
        Character->GetCharacterMovement()->JumpZVelocity *= 1.5f;
    }
}

void AMyCharacter::JumpBoostDeactivate(AActor *OwnerActor)
{
    ACharacter *Character = Cast<ACharacter>(OwnerActor);
    if (Character)
    {
        Character->GetCharacterMovement()->JumpZVelocity /= 1.5f;
    }
}

void AMyCharacter::ShieldActivate(AActor *OwnerActor)
{
    UE_LOG(LogTemp, Warning, TEXT("Shield activated!"));
}

void AMyCharacter::ShieldDeactivate(AActor *OwnerActor)
{
    UE_LOG(LogTemp, Warning, TEXT("Shield deactivated!"));
}

void AMyCharacter::OnFireballCast(const FGameplayEventData &EventData)
{
    float Damage = EventData.OptionalFloat;
    UE_LOG(LogTemp, Log, TEXT("Fireball cast! Damage: %f"), Damage);
}

void AMyCharacter::HealActivate(AActor *OwnerActor)
{
    AMyCharacter *Character = Cast<AMyCharacter>(OwnerActor);
    if (Character && Character->AttributeComponent)
    {
        float HealAmount = 25.f;

        float Health = Character->AttributeComponent->GetAttributeValue("Health");
        float MaxHealth = Character->AttributeComponent->GetAttributeValue("MaxHealth");

        // Increase health
        float NewHealth = FMath::Min(Health + HealAmount, MaxHealth);
        Character->AttributeComponent->SetAttributeValue("Health", NewHealth);

        UE_LOG(LogTemp, Log, TEXT("Health after healing: %f"), NewHealth);
    }
}

void AMyCharacter::FireballActivate(AActor *OwnerActor)
{
    AMyCharacter *Character = Cast<AMyCharacter>(OwnerActor);
    if (Character && Character->AttributeComponent)
    {
        float ManaCost = 20.f;
        float BaseDamage = 50.f;

        float Mana = Character->AttributeComponent->GetAttributeValue("Mana");
        float Strength = Character->AttributeComponent->GetAttributeValue("Strength");

        if (Mana >= ManaCost)
        {
            Character->AttributeComponent->ModifyAttributeValue("Mana", -ManaCost);

            float DamageMultiplier = 1.f;
            if (Character->AttributeComponent.HasTag("Vulnerability.Fire"))
            {
                DamageMultiplier = 1.5f;
            }

            float Damage = BaseDamage + (Strength * 2.f) * DamageMultiplier;

            // Fire logic here
            //

            FGameplayEventData EventData;
            EventData.EventTag = "Event.FireballCast";
            EventData.Instigator = this;
            EventData.OptionalFloat = Damage;
            UGameplayEventManager::Get()->BroadcastEvent(EventData);

            float RemainingMana = Character->AttributeComponent->GetAttributeValue("Mana");
            UE_LOG(LogTemp, Log, TEXT("Fireball cast! Damage: %f, Remaining Mana: %f"), Damage, RemainingMana);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Not enough mana to cast Fireball!"));
        }
    }
}
