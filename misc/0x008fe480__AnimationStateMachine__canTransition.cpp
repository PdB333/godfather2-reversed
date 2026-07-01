// FUNC_NAME: AnimationStateMachine::canTransition
// Address: 0x008fe480
// Role: Checks if the animation state machine can transition to a new state.
// Returns: 0 = cannot transition, 1 = can transition, 2 = forced transition (flag set)

int __thiscall AnimationStateMachine::canTransition() {
    // +0xC8: pointer to animation controller (derived object)
    int* pController = *(int**)(this + 0xC8);
    int basePtr;
    if (pController == nullptr) {
        basePtr = 0;
    } else {
        // Subtract offset to get base class pointer (likely parent object)
        basePtr = (int)pController - 0x48;
    }

    // Get type info from the base pointer
    int* pTypeInfo = getAnimationTypeInfo(basePtr); // FUN_008c6d50
    if (pTypeInfo == nullptr || pTypeInfo[1] != 7) { // type ID at +4, 7 = specific animation type
        // Check if forced transition flag is set (bit 5 of byte at +0xD0)
        if ((*(unsigned char*)(this + 0xD0) >> 5) & 1) {
            return 2; // forced transition
        }

        // Check three animation slots (each 8 bytes: pointer + char[4])
        // Slots start at +0x78 (pointer) and +0x7C (name char)
        for (int i = 0; i < 3; i++) {
            int* slotPtr = *(int**)(this + 0x78 + i * 8); // pointer at slot start
            char* slotName = (char*)(this + 0x7C + i * 8); // name at offset 4
            if (slotPtr != nullptr && *slotName == '\0') {
                return 0; // slot is active but name empty -> invalid
            }
        }

        // Compare current state ID with global state
        int currentState = *(int*)(this + 0x58); // +0x58: current state ID
        int globalState = getGlobalAnimationState(); // FUN_008fe1e0
        if (globalState == currentState) {
            return 1; // can transition
        }
    }
    return 0; // default: cannot transition
}