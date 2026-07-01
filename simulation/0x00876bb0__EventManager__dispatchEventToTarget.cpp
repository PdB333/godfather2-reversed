// FUNC_NAME: EventManager::dispatchEventToTarget
// Function address: 0x00876bb0
// Role: Dispatches an event callback to a target object, with stack integrity checks
void __thiscall EventManager::dispatchEventToTarget(EventManager* thisObj, int* targetObj) {
    int* currentTarget;
    int vtablePtr;
    char result;
    int* esiVal; // unknown register, likely a global or this of another object

    if (targetObj != nullptr) {
        // Set a flag in the target object's large data region (offset 0x1B94 in bytes)
        targetObj[0x6E5] |= 0x40; // +0x1B94 (int index 0x6E5)

        // Get the vtable pointer
        vtablePtr = *targetObj;
        currentTarget = &targetObj; // store address of target pointer for later

        // Virtual call at vtable index 4 (offset 0x10) – likely "canProcessEvent" or similar
        result = (**(code**)(vtablePtr + 0x10))();
        if (result != 0 && esiVal != 0) {
            // Set flags on the object pointed to by esiVal (likely a manager or global)
            *(uint*)(esiVal + 0x1F58) |= 0x1000000; // bit 24
            *(uint*)(esiVal + 0x1F5C) |= 0x2000;   // bit 13
        }

        // Virtual call at vtable index 162 (offset 0x288) – "processEvent" with parameters
        (**(code**)(*currentTarget + 0x288))(3, thisObj, 0 /* unaff_retaddr placeholder */);

        // Stack integrity check: first store a magic value, then validate
        uStack_10 = 0x369AC561;
        uStack_10 = 0; // clear after validation? 
        // Another virtual call at index 4 with a magic identifier
        result = (**(code**)(*currentTarget + 0x10))(0x383225A1, &uStack_10);
        if (result != 0 && thisObj != nullptr) {
            FUN_007a6700(); // likely a cleanup or notification function
        }
    }
    return;
}