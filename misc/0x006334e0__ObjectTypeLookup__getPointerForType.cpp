// FUNC_NAME: ObjectTypeLookup::getPointerForType
// Address: 0x006334e0
// This function is called with the 'this' pointer in ECX and the type ID in EAX.
// It looks up an entry in a table stored at this+0x8. Each entry is 8 bytes:
// [tag (int), dataPtr (int)]. If the tag equals 4, it returns dataPtr + 0x10.
// Otherwise returns a global default sentinel.

__fastcall void* ObjectTypeLookup::getPointerForType(int typeId)
{
    int index = typeId - 250; // 0xFA
    int* table = *(int**)((int)this + 8); // Array of 8-byte entries
    if (index >= 0 && *(table + index * 2) == 4) // Tag check: type 4
    {
        return (void*)(*(table + index * 2 + 1) + 0x10); // Return pointer + 0x10
    }
    return (void*)0x00e41518; // Default sentinel
}