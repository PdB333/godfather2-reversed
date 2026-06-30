// FUNC_NAME: EntityFactory::createOrAlloc
uint __thiscall EntityFactory::createOrAlloc(int index, uint flags) // index: type ID or slot; flags: bitfield or value
{
    // Global arrays: gEntityFactoryTable (size 0x10 per entry, first DWORD is vtable pointer)
    // and gFactoryFlags (byte array, indexed by original index)
    // Addresses: 0x011eb8f4 and 0x011eb8fc (relative to base)
    int factoryOffset = index * 0x10;
    EntityFactoryStruct* factory = (EntityFactoryStruct*)(&gEntityFactoryTable + factoryOffset);

    // Vtable call at offset 0x24: returns a handle (probably allocation or id)
    uint handle = factory->vtable->func24(factory, 0);
    if (handle == 0)
        return 0;

    // Vtable call at offset 0x18: performs some check or initialization, outputs two ints via stack
    int out1, out2;
    int result = factory->vtable->func18(factory, handle, &out1, &out2);
    if (result != 0)
        return 0;

    // EBX is a third parameter (likely register-passed, e.g., __fastcall) – mode/type
    // SI (byte) is a fourth parameter – sub-type
    int mode = unaff_EBX; // from caller's EBX
    byte subType = unaff_SI; // from caller's SI (low byte of ESI)

    if (mode == 1 || mode == 2) {
        // For specific modes, return the handle directly
        return handle;
    } else {
        // Build packed return value:
        // Bits 0-7: original flags
        // Bits 8-15: subType (from SI)
        // Bit 16: always 1
        // Bit 31: sign from factory flag byte (non-zero => negative)
        bool flagByte = gFactoryFlags[index] != 0;
        return ((uint)(((uint)subType << 8) | 1) << 8) | // 0x0001?? actually: ((subType << 8) | 1) << 8 = (subType << 16) | (1 << 8)
               (flagByte ? 0x80000000u : 0u) |
               flags;
    }
}