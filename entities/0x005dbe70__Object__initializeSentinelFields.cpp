// FUNC_NAME: Object::initializeSentinelFields
void __thiscall Object::initializeSentinelFields(void* thisPtr) {
    uint32_t* obj = (uint32_t*)thisPtr;
    // Global vtable pointers (likely different classes)
    uint32_t vtable1 = *(uint32_t*)0x00e2eff4;  // +0x00: first vtable
    uint32_t vtable2 = *(uint32_t*)0x00e2b1a4;  // +0x0C: second vtable

    // Set up virtual function pointers (multiple inheritance or interfaces)
    obj[0] = vtable1;      // +0x00
    obj[1] = vtable1;     // +0x04
    obj[2] = vtable1;     // +0x08
    obj[3] = vtable2;     // +0x0C
    obj[4] = vtable2;     // +0x10

    // Clear miscellaneous fields
    obj[5] = 0;           // +0x14
    obj[6] = 0;           // +0x18

    // Set debug sentinel markers (common EA practice)
    obj[7] = 1;                // +0x1C: reference count or flag?
    obj[8] = 0xBADBADBA;       // +0x20: sentinel A
    obj[9] = 0xBEEFBEEF;       // +0x24: sentinel B
    obj[10] = 0xEAC15A55;      // +0x28: sentinel C
    obj[11] = 0x91100911;      // +0x2C: sentinel D (maybe timestamp)

    // Byte field at offset 0x30 (0xC * 4 = 48)? Actually 0xC in dword units is offset 0x30, but writing a byte there:
    *(uint8_t*)(obj + 0xC) = 0; // +0x30: low byte of that dword set to 0

    // Default value at offset 0x34 (0xD * 4 = 52)
    obj[0xD] = 96000;          // +0x34: e.g. max health or distance
}