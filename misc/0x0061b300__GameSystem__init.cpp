// FUNC_NAME: GameSystem::init
void GameSystem::init(void)
{
    int allocParams[4] = {2, 0x10, 0, 0}; // Allocation flags: alignment, size, unknown
    MemoryAllocator* allocator = (MemoryAllocator*)0x01205868; // Global allocator object pointer

    // Allocate buffer1 (0xC80 = 3200 bytes)
    g_someBuffer1 = (void*)allocator->Allocate(0xC80, allocParams);

    // Reinitialize alloc params for second allocation
    allocParams[0] = 2;
    allocParams[1] = 0x10;
    allocParams[2] = 0;
    allocParams[3] = 0;
    g_someBuffer2 = (void*)allocator->Allocate(500, allocParams);

    // Initialize global struct members (offsets relative to base at 0x01205970)
    // +0x34: g_defaultValue1 (from DAT_00e2b1a4)
    g_globalStruct.memberA = g_defaultValue1;
    // +0x38
    g_globalStruct.memberB = g_defaultValue1;
    // +0x3C
    g_globalStruct.memberC = g_defaultValue1;
    // +0x04: set to 0
    g_globalStruct.someCount = 0;
    // +0x0C: pointer to buffer1
    g_globalStruct.buffer1Ptr = g_someBuffer1;
    // +0x54: set to 0
    g_globalStruct.anotherCount = 0;
    // +0x44: max value = 0xB (11)
    g_globalStruct.maxElements = 0xB;
    // +0x40: set to 0
    g_globalStruct.unknownFlag = 0;
    // +0x1C, +0x20: set to 0
    g_globalStruct.flag1 = 0;
    g_globalStruct.flag2 = 0;
    // +0x24, +0x28: set to 1
    g_globalStruct.flag3 = 1;
    g_globalStruct.flag4 = 1;
    // +0x48, +0x4C: from g_defaultValue2 (DAT_00e2cd54)
    g_globalStruct.floatA = g_defaultValue2;
    g_globalStruct.floatB = g_defaultValue2;
    // +0x00: result of this function (set twice)
    g_globalStruct.initResult = 0;
    // +0x5C: alias to buffer2
    g_globalStruct.buffer2Alias = g_someBuffer2;
    // +0x00: overwritten with return from secondary init
    g_globalStruct.initResult = FUN_0061bdf0();
}