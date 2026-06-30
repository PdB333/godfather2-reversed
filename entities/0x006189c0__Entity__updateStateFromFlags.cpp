// FUNC_NAME: Entity::updateStateFromFlags
// Function at 0x006189c0: Sets internal state bytes based on flags at offset +0xC.
// This is a common __thiscall utility called by many character/AI update functions.
void Entity::updateStateFromFlags() {
    uint32 flags = *(uint32 *)(this + 0x0C); // +0x0C: flags field (bitmask of various states)

    // Process bits 16-17 (0x30000) to set movement/action bytes at +0x20, +0x21, +0x22, +0x23
    if ((flags & 0x30000) == 0x10000) {
        // State: e.g., "running" or "aggressive"
        *(char *)(this + 0x21) = 1; // +0x21: substate A
        *(char *)(this + 0x22) = 1; // +0x22: substate B
        *(char *)(this + 0x20) = 1; // +0x20: main state
    } else {
        *(char *)(this + 0x22) = 2;
        *(char *)(this + 0x20) = 2;

        if ((flags & 0x30000) == 0x20000) {
            *(char *)(this + 0x21) = 3;
            *(char *)(this + 0x23) = 4; // +0x23: additional substate
            goto after_0x23;
        }
        *(char *)(this + 0x21) = 2;
    }
    *(char *)(this + 0x23) = 1;

after_0x23:
    // Check bit 0 (0x1) – if not set, override main state to 0
    if ((flags & 1) == 0) {
        *(char *)(this + 0x20) = 0;
    }

    // Process bits 19-22 (0x700000) to set byte at +0x24 and dword at +0x28
    uint32 highFlags = flags & 0x700000;
    if (highFlags == 0x200000) {
        *(char *)(this + 0x24) = 3; // +0x24: secondary state
    } else if (highFlags == 0x100000) {
        *(char *)(this + 0x24) = 2;
        *(int32 *)(this + 0x28) = 0; // +0x28: associated integer (e.g., timer)
        return;
    } else if (highFlags == 0x300000 || highFlags == 0x400000) {
        *(char *)(this + 0x24) = 4;
    } else {
        *(char *)(this + 0x24) = 1;
    }

    if (highFlags == 0x400000) {
        *(int32 *)(this + 0x28) = -1; // Special sentinel
        return;
    }

    *(int32 *)(this + 0x28) = 0;
}