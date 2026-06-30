// FUNC_NAME: ResourceCache::acquireResource
int* ResourceCache::acquireResource() // __thiscall, this = param_1
{
    bool isEmpty;
    int* existingObj;
    uint handle;
    int* newObj;
    int* vtable;
    // Stack locals for vtable call
    undefined4 unknownArg; // at uStack_c, initial value 2
    uint unknownFlags; // at uStack_8, from this->field_0x10
    undefined4 zero; // at uStack_4

    // Check if all four resource pointers (for some type groups) are null
    if (this->field_0x18 == 0 && this->field_0x1C == 0 && 
        this->field_0x20 == 0 && this->field_0x24 == 0) {
        isEmpty = true;
    } else {
        isEmpty = false;
    }

    // If not empty, try to find an existing resource in the first group
    if (!isEmpty) {
        existingObj = findExistingResource(&this->field_0x18); // FUN_00421170
        if (existingObj != nullptr) {
            // Increment reference count (first int in resource)
            *existingObj = *existingObj + 1;
            return existingObj;
        }
    }

    // No existing resource found; allocate a new one (size 0x30)
    handle = getMemoryManager(); // FUN_0049c5c0
    int allocResult = allocateMemory(0x30); // FUN_009c8e50
    if (allocResult == 0) {
        return nullptr;
    }
    newObj = (int*)constructResource(handle); // FUN_004c6850

    // Get vtable for the resource
    vtable = getResourceVTable(); // FUN_00420be0
    newObj[4] = (int)vtable; // offset 0x10: vtable pointer

    // Call virtual function at vtable+8 (initializer)
    (*(void (__thiscall**)(void))(*vtable + 8))();

    // Store resource type identifier (from this->field_0x28)
    newObj[3] = this->field_0x28; // offset 0x0C

    // Prepare arguments for vtable[0] call
    unknownFlags = (uint)*(ushort*)&this->field_0x10; // ushort at offset 0x10
    unknownArg = 2;
    zero = 0;

    // Call vtable[0] (a create/initialize method) with these arguments
    // vtable[0] takes: (this->field_0x28, &unknownArg) and returns int
    newObj[2] = (*(int (__thiscall**)(int, undefined4*))(*vtable))(this->field_0x28, &unknownArg); // offset 0x08

    // If the cache was not empty, set a flag in the new object (bit 1 at offset 6)
    if (!isEmpty) {
        *(ushort*)((int)newObj + 6) |= 2; // set flag: "not first" or "additional"
    }

    return newObj;
}