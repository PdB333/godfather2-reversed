// FUNC_NAME: Building::Building
undefined4 * __thiscall Building::Building(Building *this, int param2) {
    // Base initialization (possibly memory pool or allocator)
    FUN_0046e6b0(param2, 0x4000);

    // Set vtable pointers for multiple inheritance / interfaces
    this->vtable0 = &PTR_FUN_00d80c78;                          // +0x00: primary vtable
    *(void**)((int)this + 0x3C) = &PTR_LAB_00d80c68;            // +0x3C: secondary vtable (message handler base)
    *(void**)((int)this + 0x48) = &PTR_LAB_00d80c64;            // +0x48
    *(void**)((int)this + 0x50) = &PTR_LAB_00d80c60;            // +0x50
    *(void**)((int)this + 0x54) = &PTR_LAB_00d80c00;            // +0x54
    *(void**)((int)this + 0x58) = &PTR_LAB_00d80b98;            // +0x58

    // Zero out some fields
    *(int*)((int)this + 0x60) = 0;  // +0x60
    *(int*)((int)this + 0x64) = 0;  // +0x64? Wait, param_1[0x61] is offset 0x61*4=0x184? Actually careful: param_1 is int*, so param_1[0x61] = byte offset 0x184. But code says param_1[0x60]=0, param_1[0x61]=0, param_1[0x62]=0. So they are ints at offsets 0x60*4=0x180, 0x61*4=0x184, 0x62*4=0x188.
    // Correct offsets:
    this->field_0x180 = 0;   // +0x180
    this->field_0x184 = 0;   // +0x184
    this->field_0x188 = 0;   // +0x188

    // Write two shorts at adjacent byte offsets (likely part of a bitfield or padding)
    *(short*)((int)this + 0x18C) = 0;   // +0x18C
    *(short*)((int)this + 0x18E) = 0;   // +0x18E

    // Initialize magic sentinel values (debug markers)
    this->field_0x190 = 0xBADBADBA;  // +0x190
    this->field_0x194 = 0xBEEFBEEF;  // +0x194
    this->field_0x198 = 0xEAC15A55;  // +0x198
    this->field_0x19C = 0x91100911;  // +0x19C
    this->field_0x1A0 = 0;           // +0x1A0
    this->field_0x1A4 = 0;           // +0x1A4

    // Look up message ID for "iMsgBuildingExploded"
    FUN_00408240(&DAT_0112a5e0, "iMsgBuildingExploded");
    if (DAT_0112a5e0 != 0) {
        // Subscribe the message handler subobject (at offset +0x3C) to this event with priority 0x8000
        FUN_00408900((int)this + 0x3C, &DAT_0112a5e0, 0x8000);
    }

    return this;
}