// FUNC_NAME: ActionComponent::testActionCondition
uint __thiscall ActionComponent::testActionCondition(uint param_2, uint param_3, int actionType, void* param_5)
{
    // Offsets:
    // +0x48: pointer to embedded component within an Entity (at offset 0x48 in Entity)
    // After subtracting 0x48, we get the Entity base.
    // Entity +0x218: pointer to target data (TargetData)
    // TargetData +0x10: flags
    // TargetData +0x24: health/distance float
    // this +0x30: some float (e.g., range threshold)
    // Global floats: fHealthThreshold (<= E2B1A4), fRangeThreshold (<= E2B05C)

    extern float fHealthThreshold;   // DAT_00e2b1a4
    extern float fRangeThreshold;    // DAT_00e2b05c

    uint componentPtr = *(uint*)((char*)this + 0x48);
    Entity* entity = nullptr;
    if (componentPtr != 0) {
        entity = (Entity*)(componentPtr - 0x48);
    }

    // Helper: get target handle and data from entity
    uint targetHandle = 0;
    TargetData* targetData = nullptr;
    if (entity != nullptr) {
        targetHandle = *(uint*)((char*)entity + 0x218);  // Could be pointer or handle
        targetData = (TargetData*)targetHandle;
    }

    if (actionType == 7) {
        uint result = componentPtr & 0xffffff00;  // Preserve high bytes, low byte = 0
        if (targetData == nullptr) {
            return result;
        }
        // Check health threshold
        if (*(float*)((char*)targetData + 0x24) <= fHealthThreshold) {
            result = (componentPtr & 0xffffff00) | 1;
        }
        // If no specific flags set, return current result
        if ((*(uint*)((char*)targetData + 0x10) & 0x2000003) == 0) {
            return result;
        }
        // Otherwise force low bit
        return (componentPtr & 0xffffff00) | 1;
    }
    else if (actionType == 8) {
        // Evaluate conditions for ignoring low bit
        bool condition = (targetData == nullptr) ||
                         ( ((*(uint*)((char*)targetData + 0x10) & 0x2000003) == 0) &&
                           (fHealthThreshold < *(float*)((char*)targetData + 0x24)) ) ||
                         (*(float*)((char*)this + 0x30) <= fRangeThreshold);
        if (condition) {
            return targetHandle & 0xffffff00;  // low byte 0
        }
        return (targetHandle & 0xffffff00) | 1;  // low byte 1
    }
    else if (actionType == 9) {
        // Delegate to another function
        return FUN_004ac2c0(*(uint*)((char*)param_5 + 4));
    }
    else {
        // Default fallback
        return FUN_004abb20(param_2, param_3, actionType, param_5);
    }
}