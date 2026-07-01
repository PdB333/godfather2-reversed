// FUNC_NAME: ObjectManager::releaseObject
void __thiscall ObjectManager::releaseObject(int *typeIdPtr) {
    // Constants for special object types that are handled differently
    const int kSpecialType1 = DAT_0120e93c;
    const int kSpecialType2 = DAT_012067dc;

    if (*typeIdPtr != kSpecialType1 && *typeIdPtr != kSpecialType2) {
        // Access the base class vtable at offset -0x3c from this
        // This is typical for multiple inheritance where the derived class
        // has a base class at a negative offset.
        void *basePtr = *(void **)((char *)this - 0x3c);

        // Call virtual function at vtable offset 0x15c (index 0x57)
        // This function likely returns a pointer to an object-specific deallocator
        int (*getDeallocator)(void *) = *(int (**)(void *))((int *)basePtr + 0x57);
        int deallocator = getDeallocator(basePtr);

        if (deallocator != 0) {
            // Call the second virtual function (index 1) from the deallocator's vtable
            // at offset 0x3c. This function performs the actual release/deletion.
            void (*releaseFunc)(int *) = *(void (**)(int *))((int *)deallocator + 0x10); // 0x3c/4 = 15, +1 = 16 -> offset 0x40? Wait recalc: 0x3c/4 = 15, +1 = 16, so offset 0x40. But decompiled says +4, so it's the second function at vtable offset 0x3c. So vtable pointer at offset 0x3c, then call function at index 1 (offset 4). So it's *(void (**)(int*))((int*)deallocator + 0x3c/4 + 1) = *(void (**)(int*))((int*)deallocator + 0x10). Actually 0x3c/4 = 15, +1 = 16, so offset 0x40. But the decompiled says (*(int *)(iVar1 + 0x3c) + 4). That means iVar1 has a vtable pointer at offset 0x3c, and then we call the function at index 1 (offset 4) from that vtable. So it's ((int**)deallocator)[0x3c/4][1]. So we need to dereference twice. Let me correct.
            // Actually: (**(code **)(*(int *)(iVar1 + 0x3c) + 4))(param_2);
            // So iVar1 is deallocator. *(int*)(deallocator + 0x3c) gets a vtable pointer.
            // Then +4 gets the second function pointer. Then call it with param_2.
            void **vtable = *(void ***)((char *)deallocator + 0x3c);
            void (*releaseFunc)(int *) = (void (*)(int *))vtable[1];
            releaseFunc(typeIdPtr);
        }
    } else {
        // For special types, use a direct free function
        FUN_0046efc0(typeIdPtr);
    }
}