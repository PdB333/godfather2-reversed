// FUNC_NAME: MultiTrackStream::constructor (0x00724290)
// This function is a constructor for a derived class (likely MultiTrackStream or similar).
// It calls a base class initializer with a size parameter 0x4000 (16KB buffer?),
// then sets up the vtable and multiple function pointer tables at specific offsets.
// Offsets: +0x00 vtable, +0x3C, +0x48, +0x50, +0x54, +0x58.

void* __thiscall MultiTrackStream_constructor(void* this, uint32_t param_2) {
    // Base class constructor (likely StreamManager or similar)
    // param_2 is probably a pointer to configuration or owner
    // 0x4000 is likely a buffer size or flag
    BaseClass_constructor(param_2, 0x4000);

    // Set vtable pointer (offset +0x00)
    *(void**)this = &MultiTrackStream_vtable; // PTR_FUN_00d621d8

    // Set function pointer tables at various offsets
    // Offset +0x3C: first table (e.g., packet handlers or stream callbacks)
    *(void**)((uint8_t*)this + 0x3C) = &MultiTrackStream_table1; // PTR_LAB_00d621c8
    // Offset +0x48: second table
    *(void**)((uint8_t*)this + 0x48) = &MultiTrackStream_table2; // PTR_LAB_00d621c4
    // Offset +0x50: third table
    *(void**)((uint8_t*)this + 0x50) = &MultiTrackStream_table3; // PTR_LAB_00d621c0
    // Offset +0x54: fourth table
    *(void**)((uint8_t*)this + 0x54) = &MultiTrackStream_table4; // PTR_LAB_00d62160
    // Offset +0x58: fifth table
    *(void**)((uint8_t*)this + 0x58) = &MultiTrackStream_table5; // PTR_LAB_00d620f8

    return this;
}