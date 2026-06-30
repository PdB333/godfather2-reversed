// FUNC_NAME: checkModuleInitialization
bool checkModuleInitialization(uint32_t moduleHandle, uint32_t initData)
{
    // Global resource identifiers (likely file paths or IDs)
    uint32_t resourceId1 = DAT_00e50ca4;  // +0x00e50ca4
    uint32_t resourceId2 = DAT_00e50ca0;  // +0x00e50ca0

    // Call to load/initialize subsystem with the given handles and resource IDs
    FUN_00542650(moduleHandle, initData, resourceId1, resourceId2, 0, 0);

    // Local variables for vtable lookup and result
    void** vtablePtr = &PTR_FUN_00e32a8c;  // Global function pointer table
    uint32_t unknown1 = 0xFFFFFFFF;
    uint32_t unknown2 = 0xFFFFFFFF;
    uint8_t flag = 1;                     // Some flag, possibly for initialization
    uint32_t result = 0;                  // Success flag
    uint32_t globalValue = _DAT_00d5780c; // Another global constant
    uint32_t anotherGlobal = _DAT_00d5780c; // Same global (overlap)
    uint32_t zero = 0;

    // Buffer for vtable entry retrieval (32 bytes)
    uint8_t buffer[32];

    // Resolve a function pointer from the vtable (likely a virtual method)
    FUN_009e5ed0(buffer, &vtablePtr);

    // Return whether the initialization succeeded
    return result != 0;
}