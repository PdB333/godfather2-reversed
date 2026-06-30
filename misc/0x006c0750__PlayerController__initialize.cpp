// FUNC_NAME: PlayerController::initialize
void __fastcall PlayerController::initialize(void* thisPtr)
{
    // Call base initialization
    FUN_006daa50();

    // Set global flag indicating initialization complete
    g_playerControllerInitialized = 1;

    // Initialize various fields in the object
    // +0x30: byte flag (possibly active or enabled)
    *(uint8_t*)(thisPtr + 0x30) = 1;
    // +0x38: byte flag (possibly mode or state)
    *(uint8_t*)(thisPtr + 0x38) = 1;
    // +0x34: int (maybe an index or timer)
    *(int32_t*)(thisPtr + 0x34) = 0;
    // +0x39 to +0x3c: bytes (flags or padding)
    *(uint8_t*)(thisPtr + 0x39) = 0;
    *(uint8_t*)(thisPtr + 0x3a) = 0;
    *(uint8_t*)(thisPtr + 0x3b) = 0;
    *(uint8_t*)(thisPtr + 0x3c) = 0;
    // +0x40, +0x44, +0x48: float3 (position or direction) set to zero
    *(float*)(thisPtr + 0x40) = 0.0f;
    *(float*)(thisPtr + 0x44) = 0.0f;
    *(float*)(thisPtr + 0x48) = 0.0f;
    // +0x4c to +0x60: six ints/floats set to zero (maybe rotation, velocity, etc.)
    *(int32_t*)(thisPtr + 0x4c) = 0;
    *(int32_t*)(thisPtr + 0x50) = 0;
    *(int32_t*)(thisPtr + 0x54) = 0;
    *(int32_t*)(thisPtr + 0x58) = 0;
    *(int32_t*)(thisPtr + 0x5c) = 0;
    *(int32_t*)(thisPtr + 0x60) = 0;
    // +0x64 (decimal 100): set to a global value (possibly a pointer or ID)
    *(int32_t*)(thisPtr + 0x64) = g_globalValueAt0x00d5eea0;
    // +0x68 to +0x70: three ints/floats set to zero (maybe additional stats)
    *(int32_t*)(thisPtr + 0x68) = 0;
    *(int32_t*)(thisPtr + 0x6c) = 0;
    *(int32_t*)(thisPtr + 0x70) = 0;
}