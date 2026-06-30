// FUNC_NAME: UnknownClass::checkAndTransition
// Function address: 0x00732f80
// Role: Checks a virtual condition, retrieves a time/distance value, and triggers a transition if below a global threshold.
// The function is likely part of an animation or state machine update within the EA EARS engine.

void __thiscall checkAndTransition(void* thisPtr, int param_2, int param_3)
{
    char isConditionMet;
    int someId;
    float timeValue;

    // Virtual call at vtable offset 0x28c (e.g., isActive, isDone, etc.)
    isConditionMet = (*(code**)*((int*)thisPtr + 0x28c))();

    if (isConditionMet == '\0' && param_2 != 0 && param_3 != 0)
    {
        // Acquire an ID or handle from the engine (e.g., current animation slot, entity index)
        someId = getSomeId();  // FUN_00471610

        // Retrieve a time or distance value from someId + 0x30 offset (likely a struct member)
        timeValue = getFloatValue(someId + 0x30);  // FUN_004702b0

        // Compare against a global threshold (e.g., fade time, transition trigger)
        if (timeValue < **globalThreshold