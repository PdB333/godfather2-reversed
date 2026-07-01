// FUNC_NAME: FUN_00787260 (unidentified class)::canPerformAction
// Address: 0x00787260
// Role: Checks if an action is allowed based on a maximum threshold.
// Returns false (0) if the action is blocked, true (1) if allowed.
// Uses a member pointer at this+0x2c88 and a lookup via FUN_007867b0.

bool __thiscall canPerformAction(void* this, uint32_t actionId)
{
    // Look up some data associated with actionId (second param 0 is a flag)
    void* actionData = _lookupActionData(actionId, 0); // FUN_007867b0

    // If lookup succeeded and the threshold condition is met, block action
    if (actionData != nullptr)
    {
        // Member pointer at this+0x2c88 points to a settings block; offset +0x6c is the max allowed float
        float maxAllowed = *(float*)(*(int*)((char*)this + 0x2c88) + 0x6c);

        // actionData has a current value at offset +0x20
        float currentValue = *(float*)((char*)actionData + 0x20);

        // Block action if current value exceeds or equals the maximum allowed
        if (currentValue >= maxAllowed)
            return false;
    }

    // Otherwise allow action
    return true;
}