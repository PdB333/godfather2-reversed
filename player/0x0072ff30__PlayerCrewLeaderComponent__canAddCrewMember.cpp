// FUNC_NAME: PlayerCrewLeaderComponent::canAddCrewMember
bool __thiscall PlayerCrewLeaderComponent::canAddCrewMember(void *this, void *pPlayerData) {
    bool result = false;
    if (pPlayerData != nullptr) {
        uint currentCount = *(uint *)((char *)this + 0x7b4);  // +0x7b4: current crew member count
        uint maxCount = *(uint *)((char *)pPlayerData + 0x1ed0); // +0x1ed0: max crew capacity from player data
        if (maxCount == 0) {
            // Fallback: use a hash lookup to determine capacity
            float temp = 0.0f;
            FUN_008934e0(0x7589ba59, &temp);
            if (temp != _DAT_00d577a0) {
                maxCount = 1;
            }
        }
        result = currentCount <= maxCount;
        if (currentCount == 5) {
            // Special case: if current count is 5, check virtual method at vtable+0x1bc
            bool (__thiscall *checkFunc)(void *) = *(bool (__thiscall **)(void *))((char *)this + *(int *)this + 0x1bc);
            if (checkFunc(this)) {
                return true;
            }
        }
    }
    return result;
}