// FUNC_NAME: HandleManager::resolveHandle
int __thiscall HandleManager::resolveHandle(int this, int param_2) {
    uint handle = *(uint *)(this + 0x1c); // +0x1c: handle field
    int basePtr = *(int *)this;           // +0x00: base pointer to another object
    int result;

    // Handle decoding: high 2 bits indicate pointer type
    if ((handle & 0xC0000000) == 0x80000000) {
        // Direct index into an array (offset = handle * 4)
        result = (int)(handle * 4);
    }
    else if ((handle & 0xC0000000) == 0xC0000000) {
        // Index into a table at offset 0x60 from some base
        result = *(int *)(handle * 4 + 0x60);
    }
    else {
        result = 0;
        goto fallback;
    }

    if (result != 0) {
        return result;
    }

fallback:
    if (param_2 == -1) {
        // Return a fixed offset from basePtr
        result = *(int *)(basePtr + 8);
    }
    else {
        int typeId = *(int *)(basePtr + 0xc); // +0x0c: type ID
        if (typeId == 0xb) { // Type 11
            int inner = *(int *)(basePtr + 0x34);
            if (inner == 0) {
                // Call virtual function at vtable[4] on null/global object?
                (**(code **)(**(int **)(iRam00000000) + 0x10))(param_2);
            }
            else {
                // Call virtual function at vtable[4] on inner object
                (**(code **)(*(int *)(*(int *)(inner + 0x10) + 0x10)))(param_2);
            }
            result = FUN_005413c0(); // likely object allocation/creation
            return result;
        }
        else if (typeId == 0xa || typeId == 0x1e) { // Type 10 or 30
            // Call virtual function at vtable[4] on object at basePtr+0x10
            (**(code **)(*(int *)(basePtr + 0x10) + 0x10))(param_2);
            result = FUN_005413c0();
            if (result == 0) {
                int obj = (**(code **)(*(int *)(basePtr + 0x10) + 0x14))(param_2, someStackBuffer);
                // Check type of obj
                int objType = *(int *)(obj + 0xc);
                if (objType == 0x1c) { // Type 28
                    obj = *(int *)(obj + 0x14);
                }
                result = *(int *)(obj + 8);
            }
        }
        // else: result remains 0 (from earlier fallback)
    }
    return result;
}