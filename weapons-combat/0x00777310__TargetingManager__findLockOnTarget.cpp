// FUNC_NAME: TargetingManager::findLockOnTarget
int __fastcall TargetingManager::findLockOnTarget() {
    // this: TargetingManager instance
    int* targetList = *(int**)(this + 0x5c);               // m_pTargetList
    int* baseEntity = nullptr;
    if (*(int*)(this + 0x70) != 0) {                      // m_pStateObject?
        baseEntity = (int*)(*(int*)(this + 0x70) - 0x48); // adjust to base entity (offset -0x48)
    }
    // Check bit 11 at offset 0xc88 (lock‑on active flag)
    if (baseEntity && ((*(unsigned int*)(baseEntity + 0xc88/4) >> 11) & 1)) {
        unsigned int count = *(unsigned int*)(targetList + 0x744/4); // m_targetCount
        for (unsigned int i = 0; i < count; i++) {
            int* entity = getTargetEntityByIndex(i);               // FUN_00704110
            // Check bit 14 at offset 0x1d0 (valid/alive flag)
            if (entity && ((*(unsigned int*)(entity + 0x1d0/4) >> 14) & 1)) {
                return entity;                                     // first valid target found
            }
        }
        return 0;                                                  // no valid target
    }
    // Lock‑on not active: return default (local player)
    return getLocalPlayer();                                       // FUN_007175b0
}