// FUNC_NAME: ShaderManager::allocateConstantTableSlot
uint __fastcall ShaderManager::allocateConstantTableSlot(ShaderManager* this, void* shaderBytecode) {
    uint slotId;
    int* flagPtr;
    undefined4 tempVar;
    ID3DXConstantTable* constantTable; // from D3DXGetShaderConstantTable

    // Retrieve shader bytecode from this? Actually param_1 is this, and we read a field.
    // Offset DAT_00f15a14 * 4 is probably the shader bytecode pointer field.
    void* bytecode = *(void**)((uint)this + DAT_00f15a14 * 4);

    // Verify bytecode via some global manager (maybe HashManager?)
    int result = (*(int(__stdcall**)(Manager*, void*))(*(int*)DAT_01205750 + 0x16c))(DAT_01205750, bytecode);
    if (result == -0x7789fe84) {
        // Hash or validation failure - report error
        ((void(__stdcall*)(int))PTR_FUN_00f15a3c)(2);
    }

    // Check if this pointer is valid and verify bytecode again via another method
    if (this != nullptr) {
        result = (*(int(__stdcall**)(Manager*))(*(int*)DAT_01205750 + 0x158))(DAT_01205750);
        if (result == -0x7789fe84) {
            ((void(__stdcall*)(int))PTR_FUN_00f15a3c)(2);
        }
    }

    // Create constant table from shader bytecode
    D3DXGetShaderConstantTable(bytecode, &constantTable);

    // Search for an empty slot in the global pool
    slotId = 1;
    flagPtr = &s_shaderSlotFlags[0]; // DAT_011eb900
    do {
        if (*flagPtr == 0) {
            // Slot found - fill in the slot data
            uint slotOffset = (slotId - 1) * 16; // 0x10 byte structs
            s_shaderSlots[slotOffset / 4] = constantTable; // store constant table pointer
            s_shaderSlots[slotOffset / 4 + 1] = 0;          // some meta (e.g. reference count)
            s_shaderSlots[slotOffset / 4 + 2] = 0;          // maybe shader handle
            s_shaderSlots[slotOffset / 4 + 3] = 1;          // usage flag
            return slotId; // return 1-based slot index
        }
        slotId++;
        flagPtr++;
    } while (slotId < 0x800);

    return 0; // no free slot
}
/* Note: The decompiler output was ambiguous due to register state. The presumed structure is:
   - s_shaderSlots[]: 0x800 structs of 16 bytes each, starting at DAT_011eb8f0
   - s_shaderSlotFlags[]: 0x800 ints, starting at DAT_011eb900 (adjacent)
   The offsets and initial values are best guesses based on the pattern.
*/