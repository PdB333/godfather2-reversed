// FUNC_NAME: HandleManager::resolveHandle
int __thiscall HandleManager::resolveHandle(void* thisPtr) {
    // Read the handle value from offset 0x1c (likely a member field)
    uint handle = *(uint*)((char*)thisPtr + 0x1c);

    // Check the top two bits to determine the handle type
    if ((handle & 0xC0000000) == 0x80000000) {
        // Direct handle: lower 30 bits are an index into a table with element size 4
        // Return the address computed as index * 4 (base assumed to be 0)
        return (int)((handle & 0x3FFFFFFF) * 4);
    }
    if ((handle & 0xC0000000) == 0xC0000000) {
        // Indirect handle: lower 30 bits index into a global pointer table at address 0x60
        // Return the pointer stored at that table slot
        return *(int*)((handle & 0x3FFFFFFF) * 4 + 0x60);
    }
    // Invalid handle (top bits 00 or 01)
    return 0;
}