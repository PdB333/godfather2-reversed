// FUNC_NAME: ObjectManager::setupObject

int __thiscall ObjectManager::setupObject(void* thisPtr, int* obj, int data) {
    // Call virtual function at vtable+0x28 on obj with argument data + 0x90
    // This likely initializes a component or sub-object
    (**(code**)(*obj + 0x28))(data + 0x90);

    // Release any existing resource held by this manager at offset +0x58
    if (*(int*)((char*)thisPtr + 0x58) != 0) {
        FUN_007ff260(*(int*)((char*)thisPtr + 0x58));
    }

    // Get the global SimManager singleton
    int* simManager = (int*)FUN_007351c0();

    // Set a global flag at offset +0x5C (bit 0x10000000 = 268435456)
    *(uint*)((char*)simManager + 0x5C) |= 0x10000000;

    // Set a flag in the object's large flags array at index 0x7D6 (bit 0x200000 = 2097152)
    obj[0x7D6] |= 0x200000;

    // Return pointer to the global flag field (for potential quick access)
    return (int)((char*)simManager + 0x5C);
}