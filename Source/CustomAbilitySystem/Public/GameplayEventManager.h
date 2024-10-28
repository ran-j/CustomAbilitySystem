// Copyright (c) 2024 Ranieri Abreu (Ran-j)
//
// This source code is licensed under the MIT License found in the
// LICENSE file in the root directory of this source tree.
#pragma once

#include "CoreMinimal.h"
#include "GameplayEventData.h"
#include "GameplayEventManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameplayEventDelegate, const FGameplayEventData &, EventData);

UCLASS()
class CUSTOMABILITYSYSTEM_API UGameplayEventManager : public UObject
{
    GENERATED_BODY()

public:
    /** Gets the singleton instance of the event manager */
    static UGameplayEventManager *Get();

    /** Broadcasts an event */
    void BroadcastEvent(const FGameplayEventData &EventData);

    /** Adds a listener for a specific event tag */
    template<typename UserClass>
    void AddEventListener(FName EventTag, UserClass* Listener, void (UserClass::* Func)(const FGameplayEventData&));

    /** Removes a listener for a specific event tag */
    template<typename UserClass>
    void RemoveEventListener(FName EventTag, UserClass* Listener, void (UserClass::* Func)(const FGameplayEventData&));

private:
    /** Singleton instance */
    static UGameplayEventManager *Instance;

    /** Map of event tags to delegates */
    TMap<FName, FGameplayEventDelegate> EventListeners;
};
