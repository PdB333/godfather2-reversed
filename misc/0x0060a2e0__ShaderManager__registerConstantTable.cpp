// FUNC_NAME: ShaderManager::registerConstantTable
uint ShaderManager::registerConstantTable(void* pShaderData) // param_1 is likely a pointer to shader data (e.g., bytecode wrapper)
{
    // +0x00f15a14 * 4: offset in pShaderData where the shader bytecode pointer is stored (constant)
    uint shaderBytecode = *(uint*)((char*)pShaderData + g_shaderBytecodeOffset * 4); // DAT_00f15a14

    // Local variables for D3DXGetShaderConstantTable call
    uint constantTableHandle = shaderBytecode; // uStack_10 initially set to shaderBytecode
    uint* pConstantTableOutput = &constantTableHandle; // puStack_c points to constantTableHandle

    // Check global engine version/feature via vtable call (offset 0x1a8)
    // DAT_01205750 is the global engine singleton pointer
    int engineCheck = ((int(__thiscall*)(void*))(*((int*)g_engineSingleton + 0x1a8)))(g_engineSingleton);
    if (engineCheck == -0x7789fe84) // some feature flag/version check
    {
        // Call a global function pointer with argument 2 (maybe enable something)
        ((void(__cdecl*)(int))g_featureEnableFunc)(2); // PTR_FUN_00f15a3c
    }

    // Create constant table from shader bytecode
    D3DXGetShaderConstantTable(shaderBytecode, &constantTableHandle);

    // Look for empty slot in global registration arrays
    // DAT_011eb900: array of 0x800 entries, each 4 bytes (flags or pointers)
    // DAT_011eb8f0: array of 0x800 entries, each 0x10 bytes (constant table data)
    uint slotIndex = 1;
    int* flagArray = (int*)g_constantTableSlotFlags; // &DAT_011eb900
    do
    {
        if (*flagArray == 0)
        {
            // Found empty slot, store constant table handle and associated data
            int entryOffset = slotIndex * 0x10;
            uint* entryBase = (uint*)((char*)g_constantTableEntries + entryOffset); // &DAT_011eb8f0 + entryOffset

            // unaff_ESI is likely the 'this' pointer (passed in ESI), but decompiled doesn't capture it
            // We'll assume the constant table entries store: ESI value, handle, and two zeros
            entryBase[0] = g_currentThis; // unaff_ESI (the object being registered?)
            entryBase[1] = constantTableHandle; // uStack_10 (the ID3DXConstantTable*)
            entryBase[2] = 0;
            entryBase[3] = 0; // last 4 bytes

            return slotIndex; // return the slot index (non-zero)
        }
        slotIndex++;
        flagArray++; // advance 4 bytes
    } while (slotIndex < 0x800); // max 2048 slots

    return 0; // no empty slot found
}

// Static global data definitions (would be in corresponding .cpp)
// uint g_shaderBytecodeOffset = DAT_00f15a14; // e.g., 0x94 or similar
// void* g_engineSingleton = DAT_01205750;
// void (__cdecl* g_featureEnableFunc)(int) = PTR_FUN_00f15a3c;
// int g_constantTableSlotFlags[0x800] = {}; // DAT_011eb900
// char g_constantTableEntries[0x800 * 0x10] = {}; // DAT_011eb8f0
// uint g_currentThis; // global placeholder for ESI, actual implementation would be 'this'