// FUNC_NAME: CombatPerception::isTargetInRange
uint __thiscall CombatPerception::isTargetInRange(int thisPtr, int param2)
{
    uint flags = *(uint *)(thisPtr + 0xac);
    if ((flags >> 5 & 1) == 0) {
        // Not in combat state, return a default value based on another flag
        return (flags >> 0xd) << 8;
    }

    // Get the local player or main entity
    void* player = FUN_00800a90(); // likely getLocalPlayer()
    uint result = (uint)player;
    if (player != nullptr) {
        result = FUN_00701ed0(); // likely isPlayerAlive() or similar
        if ((char)result != 0) {
            int* playerData = *(int **)((int)player + 0x328); // +0x328: some state pointer
            if (playerData != nullptr) {
                float fParam2 = (float)param2;
                if (param2 < 0) {
                    fParam2 += DAT_00e44578; // constant for negative handling
                }
                // Compare with a range stored at +0x94
                if (*(float *)(thisPtr + 0x94) < fParam2 * DAT_00d5efb8) {
                    // Get two positions (likely player and target)
                    int* pos1 = FUN_00471610(); // getPosition1()
                    int* pos2 = FUN_00471610(); // getPosition2()
                    float dx = *(float *)(pos2 + 0x34) - *(float *)(pos1 + 0x34);
                    float dy = *(float *)(pos2 + 0x30) - *(float *)(pos1 + 0x30);
                    float dz = *(float *)(pos2 + 0x38) - *(float *)(pos1 + 0x38);
                    float distSq = dx*dx + dy*dy + dz*dz;
                    float radiusSq = *(float *)((int)player + 0x34c) * *(float *)((int)player + 0x34c);
                    if (distSq < radiusSq) {
                        // Target is within range, return pointer with low byte set to 1
                        return ((uint)pos2 & 0xFFFFFF00) | 1;
                    }
                }
            }
        }
    }
    // Return the result with low byte cleared
    return result & 0xFFFFFF00;
}