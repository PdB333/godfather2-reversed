// FUNC_NAME: ScriptContext::getMappedRegisterValues
void ScriptContext::getMappedRegisterValues(int param1, int param2, int sentinel, int* outRegs) {
    // vtable at this+4? Actually, this+4 holds a pointer to vtable? The code: piVar1 = *(int **)(this + 4);
    // So the first 4 bytes might be something else, then at offset4 is a pointer to a structure that has a vtable.
    // We'll assume this->m_pVTableHolder points to a structure with virtual functions.
    int* vtableHolder = *(int**)(this + 4);
    // The virtual function at offset 0x20 (32 bytes) from the vtable is GetRegisterIndex(int slotIndex)
    // It returns an index that maps to a saved register.
    int (*GetRegisterIndex)(int) = (int (*)(int))(*(int*)(*(int*)vtableHolder + 0x20));

    // These are the saved register values from the caller (passed in registers in the original asm)
    int savedRetAddr = ???; // unaff_retaddr
    int savedEBX = ???;    // unaff_EBX
    int savedEBP = ???;    // unaff_EBP
    int savedESI = ???;    // unaff_ESI

    // The sentinel used for comparison (likely -1)
    const int sentinel1 = -1; // unaff_EDI

    // Process each of the 4 register slots
    for (int i = 0; i < 4; i++) {
        int mapping = GetRegisterIndex(i);
        // If the mapping matches either sentinel, store the corresponding saved register.
        // The stored value depends on the branch taken (first or second sentinel match)
        if (mapping == sentinel1) {
            // First sentinel match: store the base register for this slot
            outRegs[i] = getSlotBaseValue(i, savedRetAddr, savedEBX, savedEBP, savedESI);
        } else if (mapping == sentinel) {
            // Second sentinel match: store param1, retaddr, EBX, or EBP depending on slot
            outRegs[i] = getSlotAltValue(i, param1, savedRetAddr, savedEBX, savedEBP);
        } else {
            // No match: leave outRegs[i] unchanged (or default?)
        }
    }
}

// Helper to determine the base saved register for a given slot index
int getSlotBaseValue(int slot, int savedRetAddr, int savedEBX, int savedEBP, int savedESI) {
    switch (slot) {
        case 0: return savedRetAddr;  // unaff_retaddr
        case 1: return savedEBX;      // unaff_EBX
        case 2: return savedEBP;      // unaff_EBP
        case 3: return savedESI;      // unaff_ESI
        default: return 0;
    }
}

// Helper to determine the alternative value when sentinel matches
int getSlotAltValue(int slot, int param1, int savedRetAddr, int savedEBX, int savedEBP) {
    switch (slot) {
        case 0: return param1;         // param_1
        case 1: return savedRetAddr;   // unaff_retaddr (note: swapped from original logic)
        case 2: return savedEBX;       // unaff_EBX
        case 3: return savedEBP;       // unaff_EBP (note: original uses unaff_EBP for both? Actually slot3 in sentinel2 uses savedEBP)
        default: return 0;
    }
}