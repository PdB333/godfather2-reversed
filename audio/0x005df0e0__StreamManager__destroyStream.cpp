// FUNC_NAME: StreamManager::destroyStream
void __thiscall StreamManager::destroyStream() {
    // local buffer for debug logging (12 bytes)
    char debugBuf[12];
    
    // Log debug message? Parameters: buffer, this, pointer from +0x1c, this, pointer from +0x1c
    // FUN_005e0410 is likely a formatted debug output function
    FUN_005e0410(debugBuf, this, *(void**)(this + 0x1c), this, *(void**)(this + 0x1c));
    
    // Call virtual function at vtable offset 1 (0x4) on the stream object at this+0x1c
    // Arg1: value at this+0x1c (the stream object itself), Arg2: 0x18 (some flag)
    (**(code**)(**(int**)(this + 4) + 4))(*(int*)(this + 0x1c), 0x18);
    
    // Clear stream pointer
    *(int*)(this + 0x1c) = 0;
    *(int*)(this + 0x20) = 0;
    
    // If another pointer is non-null, release it
    if (*(int*)(this + 0x18) != 0) {
        // Virtual call at vtable+4 on the object at this+0x14
        // Arg: pointer at this+0x18, Arg2: 0
        (**(code**)(**(int**)(this + 0x14) + 4))(*(int*)(this + 0x18), 0);
        *(int*)(this + 0x18) = 0;
    }
    
    // Finalize the sub-object at this+0x14 via virtual function at vtable+0xC
    (**(code**)(**(int**)(this + 0x14) + 0xC))();
    
    // Perform global stream manager shutdown
    StreamManager::shutdownStatic();
}