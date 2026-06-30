// FUNC_NAME: ActionComponent::checkActionCooldown
// Address: 0x004700a0
// This function checks if an action's cooldown (param3) is less than a threshold obtained from
// a game object state (offset +0xF0). It uses a global default if 'this' is null.

void __thiscall ActionComponent::checkActionCooldown(void* this, int param2, float param3)
{
    undefined4* thresholdProvider; // in_EAX - holds the object used to evaluate the threshold
    float10 result;                // Return value from FUN_004a10f0 (likely double/float)

    // If this is null, fall back to a global singleton (likely EARS engine root)
    if (this == nullptr) {
        thresholdProvider = &DAT_00e2e358; // Global default object
    } else {
        thresholdProvider = reinterpret_cast<undefined4*>(this);
    }

    // Call function that evaluates a condition based on state at +0xF0, param2, and thresholdProvider
    // FUN_004a10f0 likely returns a float threshold value (e.g., cooldown time or distance)
    result = FUN_004a10f0(reinterpret_cast<int>(this) + 0xF0, param2, thresholdProvider);

    // Check if param3 is below the threshold, but only if the threshold mask passes
    // DAT_00e44680 is a mask applied to the bit pattern of the float result (e.g., to clamp/manipulate)
    if ((param3 < static_cast<float>(static_cast<uint32_t>(static_cast<float>(result)) & DAT_00e44680)) &&
        (0.0f < static_cast<float>(result))) {
        return; // Condition met, exit early (action is available?)
    }
    // Otherwise continue (action not available or cooldown not expired)
    return;
}