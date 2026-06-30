// FUNC_NAME: SimManager::shutdown
// Address: 0x006f4710
// This function cleans up the SimManager, destroying its internal dynamic array of objects and releasing resources.

void __thiscall SimManager::shutdown(SimManager *this) {
    uint count;
    ObjectContainer *container;
    uint i;

    // Set vtable to destructor vtable (likely a special destructor-only vtable)
    *(DWORD *)this = &PTR_FUN_00d606c8;
    // Offset +0x08: probably a secondary vtable for internal handling
    *(DWORD *)(this + 0x08) = &PTR_LAB_00d606c4;

    // Offset +0x0C: pointer to a dynamic container (ObjectContainer)
    container = (ObjectContainer *)*(DWORD *)((BYTE *)this + 0x0C);
    if (container != NULL) {
        // container->pArray: pointer to array of DWORDs (object pointers)
        // container->count: number of elements
        count = *(DWORD *)((BYTE *)container + 4); // offset +0x04 from container
        i = 0;
        if (count != 0) {
            do {
                DWORD *object = *(DWORD **)(*(DWORD *)container + i * 4);
                if (object != NULL) {
                    // Call destructor (or release) on each object via its vtable
                    (**(code **)*object)(1); // argument 1 indicates deletion
                }
                i++;
            } while (i < count);
        }
        // container->vtable is at offset +0x10 (container[4])
        // Call container's internal deallocation function on the array buffer
        (**(code **)(*(DWORD *)((BYTE *)container + 0x10) + 4))(*(DWORD *)container, 0);
        // Clear container fields
        *(DWORD *)container = 0;
        *(DWORD *)((BYTE *)container + 8) = 0;
        *(DWORD *)((BYTE *)container + 4) = 0;

        // Second pass: deallocate the container itself
        container = (ObjectContainer *)*(DWORD *)((BYTE *)this + 0x0C);
        if (container != NULL) {
            // First release array buffer again? Unlikely but as per code.
            (**(code **)(*(DWORD *)((BYTE *)container + 0x10) + 4))(*(DWORD *)container, 0);
            if (*(DWORD *)((BYTE *)container + 0x0C) != 0) {
                // Release secondary buffer at offset +0x0C
                (**(code **)(*(DWORD *)((BYTE *)container + 0x10) + 4))(*(DWORD *)((BYTE *)container + 0x0C), 0);
            }
            // Call container's destructor at vtable offset 0x0C
            (**(code **)(*(DWORD *)((BYTE *)container + 0x10) + 0x0C))();
            // Free container memory (operator delete)
            FUN_009c8eb0(container);
        }
    }

    // Offset +0x10: another vtable pointer (member object)
    // Call its destructor at offset 0x0C
    (**(code **)(*(DWORD *)((BYTE *)this + 0x10) + 0x0C))();
    // Update internal vtable to a different state
    *(DWORD *)(this + 0x08) = &PTR_LAB_00d606bc;
    // Clear global initialization flag
    DAT_01129970 = 0;
    // Perform global cleanup / shutdown
    FUN_0049c640();
}