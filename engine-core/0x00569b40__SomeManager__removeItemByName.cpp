// FUNC_NAME: SomeManager::removeItemByName
void __thiscall SomeManager::removeItemByName(int* thisPtr, const wchar_t* name) {
    // 0x8a offset: array of pointers to items? each item has a flag at +0x104 and a pointer to object at +4
    // thisPtr[0xca] is count of items
    // thisPtr[0x8a] start of array of pointers to item structures

    // Acquire mutex (likely thread lock)
    // FUN_00ab4db0(&DAT_00e2cbe8);
    uint idx = 0;

    if (thisPtr[0xca] == 0) {
        goto cleanup;
    }

    int** itemPtrArray = (int**)(thisPtr + 0x8a);
    do {
        int* itemStruct = *itemPtrArray;  // each entry is a pointer to an item structure
        if (itemStruct != nullptr && itemStruct[0x104/4] != 0) // +0x104: likely a flag indicating alive/valid
        {
            int* object = (int*)itemStruct[1]; // +4: pointer to the actual object
            // Compare the name at object+8 (wchar_t) with the given name
            wchar_t* objName = (wchar_t*)(object + 2); // +8 bytes -> +2 ints
            wchar_t* givenName = (wchar_t*)name;
            int cmpResult = wcscmp(objName, givenName); // simplified: the decompiled code does two-byte compare
            if (cmpResult == 0) {
                // Call virtual function at offset 0x18 on the object
                // (Assuming object's vtable has a method at slot 6? 0x18/4 = 6)
                typedef void (__thiscall *DestroyFunc)(int*);
                DestroyFunc destroy = (DestroyFunc)(*(int**)*object)[0x18/4]; // vtable[6]
                destroy(object);
                goto cleanup;
            }
        }
        idx++;
        itemPtrArray++;
    } while (idx < (uint)thisPtr[0xca]);

cleanup:
    // Release mutex
    // FUN_00ab4e70();
    return;
}