// FUNC_NAME: StreamManager::shutdown
// Function address: 0x0071bd10
// Role: Shutdown/reset a manager that holds an array of resource pointers.
//       Iterates over all items, releases each if they have a sub-resource at offset 0x1c,
//       then calls a virtual method on each (via vtable at offset 0x79*4).
//       Finally cleans up global state and resets vtable to base class.

void __thiscall StreamManager::shutdown(StreamManager* this) {
    int itemPtr;
    int* itemsArray;
    uint i;

    // Set vtable to current class vtable (likely already set, but done for safety)
    *(int*)this = &PTR_FUN_00d61da0; // vtable for StreamManager (or derived)

    i = 0;
    // param_1[0x8d] = count of items in the array (e.g., number of streams)
    if (this->itemCount != 0) {
        // param_1[0x83] = pointer to an array of pointers (each pointing to a item object)
        itemsArray = (int*)&this->itemsArray; // offset 0x83*4 = 0x20C
        do {
            itemPtr = *itemsArray;
            // Each item has a resource handle at offset 0x1c
            if (*(int*)(itemPtr + 0x1c) != 0) {
                FUN_004daf90(itemPtr + 0x1c); // Release the sub-resource
            }
            // Call a virtual method on the item: presumably a "release" or "destroy"
            // The vtable pointer for the item class is stored at offset 0x79*4 in this object.
            // Offset 4 from that vtable is the function to call (e.g., IDispose::Dispose)
            (**(code**)(this->itemVtable[0] + 4))(itemPtr, 0);
            i++;
            itemsArray++;
        } while (i < (uint)this->itemCount);
    }

    // Global cleanup function (e.g., shutdown a subsystem)
    FUN_004abf00();

    // Nullify the vtable pointer for items to prevent further calls
    this->itemVtable = &PTR___purecall_00e30fac; // purecall placeholder

    // Reset this object's vtable to base class (probably before base destructor)
    *(int*)this = &PTR_LAB_00d61d9c;

    // Clear the global singleton/instance pointer
    DAT_011298b0 = 0;
}