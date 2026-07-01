// FUNC_NAME: AIController::evaluateOverrideCondition
// Address: 0x0086ebc0
// Role: Evaluates an override condition based on a component's virtual method results and a global threshold.

#include <cstdint>

// Forward declarations (placeholder for known EA EARS types)
class BehaviorComponent; // vtable at +0x00, size unknown

class AIController {
public:
    // +0x50: pointer to a behavior container (e.g., GenericBehavior or ActiveBehavior)
    class BehaviorContainer* m_pBehaviorContainer; // offset +0x50

    // Accessor for the container's internal flag and component pointer
    // container->+0x70: pointer to a BehaviorComponent-derived object
    // container->+0xC9: bit0 flag indicating "override enabled?"
};

class BehaviorContainer {
public:
    // +0x70: pointer to a derived BehaviorComponent (base at offset -0x48 from this pointer)
    BehaviorComponent* m_pComponent; // offset +0x70
    // +0xC9: flags byte; bit0 = bOverrideEnabled
    uint8_t m_flags; // offset +0xC9
};

// Global threshold (likely a float constant used for timing/distance checks)
extern float DAT_00d75860;

// Forward declaration of a helper function (likely returns a default result)
uint __fastcall FUN_0086e440(int a, int b);

uint __fastcall AIController::evaluateOverrideCondition(void* thisPtr) {
    // Fetch container and component
    BehaviorContainer* container = *(BehaviorContainer**)((uint8_t*)thisPtr + 0x50);
    if (container == nullptr) {
        return FUN_0086e440(0, 0);
    }

    BehaviorComponent* rawComponent = *(BehaviorComponent**)((uint8_t*)container + 0x70);
    if (rawComponent == nullptr) {
        return FUN_0086e440(0, 0);
    }

    // The component's actual vtable is at address `rawComponent` but the object is embedded
    // with a header of 0x48 bytes? Actually the code computes: piVar1 = rawComponent - 0x48.
    // So the "real" BehaviorComponent object starts at (rawComponent - 0x48).
    BehaviorComponent* component = (BehaviorComponent*)((uint8_t*)rawComponent - 0x48);
    if (component == nullptr) {
        return FUN_0086e440(0, 0);
    }

    // Check the container's override enabled flag
    if ((container->m_flags & 1) == 0) {
        return FUN_0086e440(0, 0);
    }

    // Call virtual function at vtable index 0x1e4 (method #121)
    // Returns non-zero if the override is possible
    typedef bool (__thiscall* OverridePossibleFn)(BehaviorComponent*);
    OverridePossibleFn isOverridePossible = *(OverridePossibleFn*)(*(void***)component + 0x1e4 / sizeof(void*));
    if (!isOverridePossible(component)) {
        return FUN_0086e440(0, 0);
    }

    // Call virtual function at vtable index 0x1b0 (method #108) returning a float
    typedef float (__thiscall* GetOverrideFloatFn)(BehaviorComponent*);
    GetOverrideFloatFn getOverrideFloat = *(GetOverrideFloatFn*)(*(void***)component + 0x1b0 / sizeof(void*));
    float overrideValue = getOverrideFloat(component);

    // Compare the returned float against the global threshold
    if (overrideValue <= DAT_00d75860) {
        // Override condition met; return result from helper with lower byte cleared
        uint result = FUN_0086e440(0, 0);
        return result & 0xFFFFFF00;
    }

    // Default fallback
    return FUN_0086e440(0, 0);
}