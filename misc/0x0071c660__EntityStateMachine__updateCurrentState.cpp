// FUNC_NAME: EntityStateMachine::updateCurrentState
void __thiscall EntityStateMachine::updateCurrentState(EntityStateMachine* this) {
    uint newState = 0;
    // Get sub-object pointer (offset +0x08) and re-derive parent offset (0x48 header)
    int* subObj = *(int**)((uint)this + 0x08);
    int* parentObj = subObj ? (int*)((uint)subObj - 0x48) : nullptr;

    // Bit 9 of this->m_flags (+0x3c) indicates state machine active
    if (((*(ushort*)((uint)this + 0x3C) >> 9) & 1) != 0 && parentObj != nullptr) {
        // Bit 10 of parentObj[0x238] (+0x8E0) indicates some override
        if ((((uint)parentObj[0x238] >> 10) & 1) == 0) {
            // Not overridden: check external condition
            if (FUN_007ff880() != 0) {
                newState = 5; // e.g., "autoCombat"
            }
        } else {
            // Overridden: call virtual function via vtable offset 0x270
            // (likely returns a priority byte)
            newState = ((*(code**)(*parentObj + 0x270))() & 0xFF);
        }

        // Re-fetch parent object (safety check)
        parentObj = (int*)((uint)*(int**)((uint)this + 0x08) - 0x48);
        // Bit 7 of low byte of m_flags indicates dead/downed
        if (*(char*)((uint)this + 0x3C) < 0 && parentObj != nullptr) {
            // Check if special death override OR specific animation state
            if ((((*(uint*)((uint)parentObj + 0x8E0) >> 10) & 1) != 0 && FUN_00800b10() != 0) ||
                (*(int*)((uint)parentObj + 0x30C0) != 0 && *(int*)((uint)parentObj + 0x30C0) != 0x48)) {
                newState = 1; // death/transition state
            }
        }
    }

    // Update if state changed, record timestamp
    if (newState != *(uint*)((uint)this + 0x38)) {
        *(uint*)((uint)this + 0x38) = newState;
        *(float*)((uint)this + 0x34) = *(float*)DAT_01205228; // global frame time
    }
}