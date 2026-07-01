// FUNC_NAME: checkBitmaskWithThreshold
// Address: 0x008968c0
// Role: Checks if a given bitmask (param_2) exists in a list of bitmasks, and if so, computes a sum based on associated data and compares it against a global threshold.
// Likely part of a bitmask-based state/attitude check (e.g., CrewLeaderComponent or AttitudeManager).

bool __thiscall checkBitmaskWithThreshold(uint param_2) {
    uint count = *(uint*)(this + 0x0C);
    if (count == 0) {
        return true;
    }

    uint* bitmaskArray = *(uint**)(this + 0x04);
    int* dataArrayBase = *(int**)(this + 0x08); // array of structures of size 0x2C
    int baseOffset = *(int*)(this + 0x14);      // additional offset added to the value read

    for (uint i = 0; i < count; i++) {
        if ((*bitmaskArray & param_2) != 0) {
            // Found a matching entry; retrieve value at offset 0x28 within the structure
            int structValue = *(int*)((int)dataArrayBase + i * 0x2C + 0x28);
            int total = structValue + baseOffset;
            return total < DAT_01205220; // global threshold
        }
        bitmaskArray++;
    }

    return true;
}