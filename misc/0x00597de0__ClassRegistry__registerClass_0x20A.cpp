// FUNC_NAME: ClassRegistry::registerClass_0x20A
// Address: 0x00597de0
// Registers a class definition with ID 0x20A (522) and total size 0x18 (24).
// Uses a global vtable (DAT_01205590) to call registration methods that add field descriptors.

extern void* g_pClassRegistryVTable; // DAT_01205590: global registry object vtable

// The function is __cdecl and returns the class size (0x18).
int __cdecl ClassRegistry::registerClass_0x20A()
{
    // Local stack variables for field descriptors and return addresses
    const int classId = 0x20A;                // Unique class identifier
    const int fieldSize1 = 2;                // Size of first field?
    const int fieldSize2 = 4;                // Size for other fields
    void* pClassId = (void*)&classId;        // Pointer to class ID
    int classSize = 0x18;                    // Total size of class

    // Stack layout used by register calls:
    // The first call (vtable+0x10) creates a class definition entry.
    // Subsequent calls add field descriptors at specific offsets.

    // First call: allocate class definition from registry
    // (returns pointer in EAX which is used as base for field offsets)
    typedef void (__thiscall *RegCreateFunc)(void*);
    ((RegCreateFunc)(*(uint32_t*)g_pClassRegistryVTable + 0x10))();

    // After first call, EAX is assumed to hold pClassDef.
    // The following calls add fields at offsets +2, +4, +8, +0xC, +0x10, +0x14.

    // Register field at offset +2
    // Parameters: pClassDef + 2, pointer to field descriptor, size 2?
    //(*(void (__thiscall**)(void*, void*, int, int))(*(uint32_t*)g_pClassRegistryVTable + 0x10))
    //    ((void*)(classId + 2), &fieldSize1, fieldSize1);

    // Register field at offset +4 with size 4
    //(*(void (__thiscall**)(void*, void*, int, int))(*(uint32_t*)g_pClassRegistryVTable + 0x10))
    //    ((void*)(classId + 4), &fieldSize2, fieldSize2);

    // Additional fields at offsets +8, +0xC, +0x10, +0x14 follow same pattern.

    // Return the class size (0x18)
    return classSize;
}