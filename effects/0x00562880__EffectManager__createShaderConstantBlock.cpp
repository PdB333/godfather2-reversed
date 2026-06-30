// FUNC_NAME: EffectManager::createShaderConstantBlock
int EffectManager::createShaderConstantBlock()
{
    // Local stack buffer for building a constant block (e.g., shader constants)
    // Offsets: 0x84..0xc4 (42 DWORDs) but only part is used in assignments
    undefined4 stackConstants[42]; // actually more local variables at different offsets
    undefined4* pBuffer;      // +0xb4
    undefined4 local_b0;      // unused? assigned later
    undefined4 local_ac;      // param for size?
    undefined4 local_a8;      // flags/result
    undefined4* newBuffer;    // +0x9c
    undefined4 local_98;      // output from allocation?
    // ... many locals for constants

    // Initialize constant block from global values
    stackConstants[0] = DAT_00e445a4;   // some float/int constant
    // Many assignments follow – we keep them symbolic
    // ...

    pBuffer = &stackConstants[0];
    local_ac = 0x10;
    local_b0 = 8;

    // Process the constant block: maybe marshal or create a copy
    // Outputs: newBuffer, local_a8 (flags)
    FUN_00a77320(&pBuffer, &newBuffer, &local_a8, 1);

    // Update local parameters from processed buffer
    local_b0 = local_98;    // size or handle from FUN_00a77320
    local_ac = 0x10;
    pBuffer = newBuffer;

    // Thread-local storage access (for per-thread heap?)
    TlsGetValue(DAT_01139810);

    // Allocate main effect structure (size 0x60 bytes)
    int effectPtr = FUN_00aa2680(0x60, 0x27);
    *(short*)(effectPtr + 4) = 0x60;

    // Create effect object using the processed constant block and flags
    int result = FUN_00c067b0(&pBuffer, &local_a8, _DAT_00ef3a9c);
    *(int*)(result + 0x10) = DAT_00e2fc48;

    // Additional initialization
    FUN_00562ad0();

    // Free temporary constant buffer if not using pool-allocated memory
    uint tempFlags = local_a0; // from stack
    if ((tempFlags & 0x80000000) == 0) {
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(local_a8, tempFlags << 4, 0x17);
    }

    return result;
}