// FUNC_NAME: SimNpc::SimNpc

SimNpc * __thiscall SimNpc::SimNpc(SimNpc *this, uint initializationFlags)
{
    // Base class initialization (e.g., Entity or ResourceManager)
    FUN_006c9760(initializationFlags, g_gameMemoryPool); // _DAT_00d5cf70

    // Set vtable pointers (dual inheritance or interface)
    this->vtable = (void *)&SimNpc_vtable;          // +0x00
    this->secondaryVtable = (void *)&SimNpc_other;  // +0x08

    // Zero out game-specific state fields (arranged in blocks)
    // State block 1 (offsets 0x3c-0x41: 6 ints)
    this->stateBlock1[0] = 0; // +0x3c
    this->stateBlock1[1] = 0; // +0x3d
    this->stateBlock1[2] = 0; // +0x3e
    this->stateBlock1[3] = 0; // +0x3f
    this->stateBlock1[4] = 0; // +0x40
    this->stateBlock1[5] = 0; // +0x41

    // Byte flags
    *((uint8 *)this + 0x42) = 0;
    *((uint8 *)this + 0x109) = 0;
    *((uint8 *)this + 0x10a) = 0;

    // Additional initialization (e.g., stats or sub-objects)
    FUN_006e01d0();

    // State block 2 (offsets 0x30-0x3b: 12 ints, consecutive)
    this->stateBlock2[0x0] = 0; // +0x30
    this->stateBlock2[0x1] = 0; // +0x31
    this->stateBlock2[0x2] = 0; // +0x32
    this->stateBlock2[0x3] = 0; // +0x33
    this->stateBlock2[0x4] = 0; // +0x34
    this->stateBlock2[0x5] = 0; // +0x35
    this->stateBlock2[0x6] = 0; // +0x36
    this->stateBlock2[0x7] = 0; // +0x37
    this->stateBlock2[0x8] = 0; // +0x38
    this->stateBlock2[0x9] = 0; // +0x39
    this->stateBlock2[0xa] = 0; // +0x3a
    this->stateBlock2[0xb] = 0; // +0x3b

    // State block 3 (offsets 0x45-0x43? Actually in reverse order)
    this->stateBlock3[0] = 0; // +0x43
    this->stateBlock3[1] = 0; // +0x44
    this->stateBlock3[2] = 0; // +0x45

    // State block 4 (offsets 0x46-0x48)
    this->stateBlock4[0] = 0; // +0x46
    this->stateBlock4[1] = 0; // +0x47
    this->stateBlock4[2] = 0; // +0x48

    // State block 5 (offsets 0x79-0x7c)
    this->stateBlock5[0] = 0; // +0x79
    this->stateBlock5[1] = 0; // +0x7a
    this->stateBlock5[2] = 0; // +0x7b
    this->stateBlock5[3] = 0; // +0x7c

    return this;
}