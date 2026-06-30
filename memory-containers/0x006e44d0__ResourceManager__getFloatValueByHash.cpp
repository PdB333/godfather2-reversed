// FUNC_NAME: ResourceManager::getFloatValueByHash
// Function address: 0x006e44d0
// Role: Retrieves a float value by hash key from a resource manager, then processes it if valid.

void __thiscall ResourceManager::getFloatValueByHash(int this, float* outValue)
{
    // outValue is actually a pointer to a structure with a vtable pointer at offset 0x100
    // (e.g., a resource handle object)
    undefined4* vtablePtr = (undefined4*)((int)outValue + 0x100);
    // Local pointer to be filled by the virtual call
    float* result = 0;

    // Call virtual function at vtable+0x10 (likely a "find" or "get" method)
    // The hash 0x383225a1 identifies the requested value
    char success = (**(code**)(*(int*)*vtablePtr + 0x10))(0x383225a1, &result);

    // If lookup succeeded, this is valid, and the result is not a sentinel value
    if (success && this != 0 && *result != _DAT_00d577a0) {
        // Process the retrieved float value (e.g., apply setting, play sound, etc.)
        FUN_007ac710(*result);
    }
    return;
}