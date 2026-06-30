// FUNC_NAME: ObjectManager::ReleaseObject

void __thiscall ObjectManager::ReleaseObject(int this, int obj) {
    uint count;
    uint index;
    uint i;
    
    // Decrement reference count if not about to release
    if (*(int *)(obj + 0x18) != 1) {
        *(int *)(obj + 0x18) = *(int *)(obj + 0x18) - 1;
        return;
    }
    
    count = *(uint *)(this + 0x234);          // +0x234: object count
    index = 0;
    i = 0xffffffff;                           // sentinel for not found
    
    // Search for obj in the pointer array at +0x20c
    if (count != 0) {
        do {
            i = index;
            if (*(int *)(this + 0x20c + index * 4) == obj) break;
            index = index + 1;
            i = 0xffffffff;
        } while (index < count);
    }
    
    // If found, remove it by shifting elements left
    if (i < count) {
        if (i < count - 1) {
            do {
                *(int *)(this + 0x20c + i * 4) = *(int *)(this + 0x210 + i * 4); // shift down
                i = i + 1;
            } while (i < *(int *)(this + 0x234) - 1);
        }
        *(int *)(this + 0x234) = *(int *)(this + 0x234) - 1;  // decrement count
    }
    
    // Free associated sub-object if present
    if (*(int *)(obj + 0x1c) != 0) {
        FUN_004daf90(obj + 0x1c);  // likely delete or free internal resource
    }
    
    // Call virtual destructor or finalize function via vtable
    (**(code **)(*(int *)(this + 0x1e4) + 4))(obj, 0);  // vtable[1] is destructor with param 0
}