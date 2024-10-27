#include "../Public/AttributeComponent.h"

UAttributeComponent::UAttributeComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

float UAttributeComponent::GetAttributeValue(FName AttributeName) const
{
    const float *ValuePtr = Attributes.Find(AttributeName);
    return ValuePtr ? *ValuePtr : 0.f;
}

void UAttributeComponent::SetAttributeValue(FName AttributeName, float NewValue)
{
    if (Attributes.Contains(AttributeName))
    {
        Attributes[AttributeName] = NewValue;
    }
    else
    {
        AddAttribute(AttributeName, NewValue);
    }
}

void UAttributeComponent::ModifyAttributeValue(FName AttributeName, float Delta)
{
    if (Attributes.Contains(AttributeName))
    {
        Attributes[AttributeName] += Delta;
    }
    else
    {
        AddAttribute(AttributeName, Delta);
    }
}

bool UAttributeComponent::HasAttribute(FName AttributeName) const
{
    return Attributes.Contains(AttributeName);
}

void UAttributeComponent::AddAttribute(FName AttributeName, float InitialValue)
{
    if (!Attributes.Contains(AttributeName))
    {
        Attributes.Add(AttributeName, InitialValue);
    }
}

void UAttributeComponent::RemoveAttribute(FName AttributeName)
{
    Attributes.Remove(AttributeName);
}
