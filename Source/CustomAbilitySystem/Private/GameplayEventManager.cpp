#include "../Public/GameplayEventManager.h"

UGameplayEventManager *UGameplayEventManager::Instance = nullptr;

UGameplayEventManager *UGameplayEventManager::Get()
{
    if (!Instance)
    {
        Instance = NewObject<UGameplayEventManager>();
        Instance->AddToRoot(); // Prevent garbage collection
    }
    return Instance;
}

void UGameplayEventManager::BroadcastEvent(const FGameplayEventData &EventData)
{
    FGameplayEventDelegate *Delegate = EventListeners.Find(EventData.EventTag);
    if (Delegate)
    {
        Delegate->Broadcast(EventData);
    }
}

template<typename UserClass>
void UGameplayEventManager::AddEventListener(FName EventTag, UserClass* Listener, void (UserClass::* Func)(const FGameplayEventData&))
{
    FGameplayEventDelegate& ExistingDelegate = EventListeners.FindOrAdd(EventTag);
    ExistingDelegate.AddDynamic(Listener, Func);
}

template<typename UserClass>
void UGameplayEventManager::RemoveEventListener(FName EventTag, UserClass* Listener, void (UserClass::* Func)(const FGameplayEventData&))
{
    FGameplayEventDelegate* ExistingDelegate = EventListeners.Find(EventTag);
    if (ExistingDelegate)
    {
        ExistingDelegate->RemoveDynamic(Listener, Func);
    }
}