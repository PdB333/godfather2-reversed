// FUNC_NAME: MissionManager::conditionallyOverrideResult
uint __thiscall MissionManager::conditionallyOverrideResult(void* this, int paramId)
{
    // +0x218: pointer to current active mission/objective object
    void* currentMission = *(void**)((uintptr_t)this + 0x218);

    // The incoming EAX register is masked to keep high bytes, low byte cleared.
    // This is an implicit parameter passed by the caller (likely a previous result).
    uint result = (uint)in_EAX & 0xffffff00;

    if (currentMission != nullptr &&
        // +0x18: identifier field of the mission (e.g., mission ID)
        *(int*)((uintptr_t)currentMission + 0x18) == paramId &&
        // +0x70: pointer to a sub-object (e.g., quest target, location data)
        *(void**)((uintptr_t)currentMission + 0x70) != nullptr &&
        // +0x30: some valid flag/pointer in the sub-object
        *(void**)(*(int*)((uintptr_t)currentMission + 0x70) + 0x30) != nullptr)
    {
        // If conditions are satisfied, call some function that produces a new result value
        result = FUN_00573440();
    }
    return result;
}