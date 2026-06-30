// FUNC_NAME: ResourceTable::Insert
int ResourceTable::Insert(void* item) {
    int handle = ComputeItemHash(item); // FUN_004cfe00
    int size = *(int*)((char*)this + 0x14);
    int capacity = *(int*)((char*)this + 0x18);
    
    if (size == capacity) {
        if (capacity == 0)
            capacity = 1;
        else
            capacity <<= 1;
        ResizeArray(capacity); // FUN_0048edd0
    }
    
    int* array = *(int**)((char*)this + 0x10);
    *(int*)((char*)this + 0x14) = size + 1;
    if (array) {
        array[size] = handle;
    }
    
    // Log handle to a global debug buffer (DAT_01206880 + 0x14 is a write pointer)
    int* globalWritePtr = *(int**)(DAT_01206880 + 0x14);
    *(void**)(DAT_01206880 + 0x14) = &PTR_LAB_01123c24; // push a vtable pointer
    *globalWritePtr += 4;
    *(int*)(*globalWritePtr) = handle;
    *globalWritePtr += 4;
    
    // Initialize sub-structure if not yet created (likely a hash table or index)
    if (*(int*)((char*)this + 0x1c) == 0) {
        if (DAT_01163d94 != 0)
            item = (void*)DAT_01163d94;
        bool success = InitItemTable((int*)((char*)this + 0x1c), item); // FUN_00489a80
        if (success) {
            int subHandle = *(int*)((char*)this + 0x1c);
            int* globalWritePtr2 = *(int**)(DAT_01206880 + 0x14);
            *(void**)(DAT_01206880 + 0x14) = &PTR_LAB_01123c4c;
            *globalWritePtr2 += 4;
            *(int*)(*globalWritePtr2) = subHandle;
            *globalWritePtr2 += 4;
        }
    }
    
    // Invoke callback if handle is valid and callback is set
    if (handle != 0 && *(void**)((char*)this + 0x50) != 0) {
        ((void (*)(int))(* (int**)((char*)this + 0x50)))(handle);
    }
    
    return handle;
}