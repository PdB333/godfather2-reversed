// FUNC_NAME: MessageQueue::enqueueWithBuffer
void __thiscall MessageQueue::enqueueWithBuffer(void* data, int dataSize, int flags) {
    // Hidden parameter: int param_2 (flags?), but not used directly; only param_3/data and param_4/size appear.
    // Actually the signature from decompiled: void __thiscall FUN_0065d3e0(int this, undefined4 param_2, undefined1* data, undefined4 size)
    // We'll rename: this, param_2 (unused?), data, size.
    int* managerPtr = (int*)FUN_00ad8d40(); // Get some global manager/singleton
    if (managerPtr == 0) {
        return;
    }
    int* someObj = (int*)(**(code**)(*managerPtr + 0x34))(); // Get object via vtable slot 0x34
    if (someObj != 0) {
        int status = (**(code**)(*someObj + 0x24))(); // Check status via vtable slot 0x24
        if (status != 0) {
            // Check if we have a fast-path handler at offset 0x6C
            if (*(int*)(this + 0x6C) == 0 ||
                !(**(code**)(**(int**)(this + 0x6C) + 8))(data, size)) { // If no fast-path or fast-path returns false
                EnterCriticalSection((LPCRITICAL_SECTION)(this + 0xC));
            } else {
                // Use fast-path: call functions on the handler
                (**(code**)(**(int**)(this + 0x6C) + 0x10))(data, size); // Some processing (maybe copy to internal buffer)
                (**(code**)(**(int**)(this + 0x6C) + 4))(data, &localBuffer); // Another operation, perhaps storing the buffer address
                EnterCriticalSection((LPCRITICAL_SECTION)(this + 0xC));
                data = &localBuffer; // Override data pointer with local buffer
            }
            // Core enqueue operation using data pointer
            FUN_0065d730(this, data); // Enqueue actual data (size encoded in data?)
            LeaveCriticalSection((LPCRITICAL_SECTION)(this + 0xC));
        }
    }
}