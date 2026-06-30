// FUNC_NAME: StreamManager::clearResources
void StreamManager::clearResources(void)
{
    // local buffer of 12 bytes, likely a temporary for some operation
    char tempBuffer[12];
    // Get pointer to resource (e.g., stream object) at offset 0x1c
    void* pResource = *(void**)(this + 0x1c);
    // Call helper function with temp buffer, this pointer, and resource pointer
    FUN_00623210(tempBuffer, this, *(void**)((char*)this + 0x1c), this, *(void**)((char*)this + 0x1c));
    // Call vtable+4 on the object at offset 0x4 (likely a manager or interface)
    // This may be a destructor or release call with parameter 0x18 (24)
    (**(code**)(**(int**)((char*)this + 4) + 4))(*(int*)((char*)this + 0x1c), 0x18);
    // Clear resource pointers
    *(int*)((char*)this + 0x1c) = 0;
    *(int*)((char*)this + 0x20) = 0;
    // If there is another resource at offset 0x18
    if (*(int*)((char*)this + 0x18) != 0) {
        // Call vtable+4 on object at offset 0x14 (another manager) passing 0
        (**(code**)(**(int**)(*(int*)((char*)this + 0x14)) + 4))(*(int*)((char*)this + 0x18), 0);
        *(int*)((char*)this + 0x18) = 0;
    }
    // Call vtable+12 on the same manager (possibly a final shutdown)
    (**(code**)(**(int**)(*(int*)((char*)this + 0x14)) + 12))();
    // Call global cleanup function
    FUN_00621f80();
    return;
}