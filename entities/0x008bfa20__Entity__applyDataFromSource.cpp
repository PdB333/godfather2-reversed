// FUNC_NAME: Entity::applyDataFromSource
int __thiscall Entity::applyDataFromSource(void* this, void* sourceData, void** outSourceRef)
{
    // Store reference to source data
    *outSourceRef = sourceData;

    // Check type identifier at +0x54 (hash of class name)
    if (*(int*)((char*)this + 0x54) == 0x637b907) {
        // Use global singleton value (DAT_01129908 + 0x14)
        *(int*)((char*)this + 0x100) = *(int*)(DAT_01129908 + 0x14);
        // If double pointer at +0x230 is valid, write the same value there
        if (*(void**)((char*)this + 0x230) != nullptr) {
            **(int**)((char*)this + 0x230) = *(int*)((char*)this + 0x100);
        }
    } else {
        // Copy from source data at offset +0x4
        *(int*)((char*)this + 0x100) = *(int*)((char*)sourceData + 4);
    }

    // Copy transform data (position, rotation, etc.)
    // Source offsets: 0x10, 0x14, 0xc, 0x18, 0x1c, 0x20 (last is bool)
    // Destination offsets: 0x148, 0x14c, 0x150, 0x154, 0x158, 0x15c
    *(float*)((char*)this + 0x148) = *(float*)((char*)sourceData + 0x10);
    *(float*)((char*)this + 0x14c) = *(float*)((char*)sourceData + 0x14);
    *(float*)((char*)this + 0x150) = *(float*)((char*)sourceData + 0xc);
    *(float*)((char*)this + 0x154) = *(float*)((char*)sourceData + 0x18);
    *(float*)((char*)this + 0x158) = *(float*)((char*)sourceData + 0x1c);
    *(bool*)((char*)this + 0x15c) = *(int*)((char*)sourceData + 0x20) != 0;

    // Copy additional fields
    *(int*)((char*)this + 0x84) = *(int*)((char*)sourceData + 0x40);
    *(int*)((char*)this + 0x120) = *(int*)((char*)sourceData + 0x4c);

    // Return size of structure (0x60 = 96 bytes)
    return 0x60;
}