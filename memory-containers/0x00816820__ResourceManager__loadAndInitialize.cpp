//FUNC_NAME: ResourceManager::loadAndInitialize
// Address: 0x00816820
// Role: Loads a resource (likely a string/script) from a constant, initializes the object, and returns a handle.
// Calls base constructor, static initializers, and resource loading functions.

undefined4 ResourceManager::loadAndInitialize(ResourceManager *this) {
    void *resourceData;          // local_20 - pointer to loaded resource data
    int resourceLoadResult;      // local_1c - result code from resource load
    void (*resourceDestructor)(void *); // local_14 - destructor for resource data
    int someHandle;              // local_10 - another handle/resource
    void (*someDestructor)(int); // local_4 - destructor for someHandle
    void *puVar1;                // temporary pointer
    undefined4 result;           // uVar2 - return value

    // Call base class constructor (likely EARSObject or similar)
    FUN_004d3bc0(this);

    // Static initialization (e.g., global state setup)
    FUN_004d55d0();

    // Load resource from a constant string (DAT_00e2f04c)
    // Sets resourceData and resourceLoadResult
    FUN_004d5170(&resourceData, &DAT_00e2f04c);

    // If resource load succeeded (resourceLoadResult == 0), perform additional initialization
    if (resourceLoadResult == 0) {
        FUN_004d3d90(this);
    }

    // Another static initialization step
    FUN_004d57e0();

    // Use the loaded resource data, or fall back to a default string (DAT_0120546e)
    puVar1 = resourceData;
    if (resourceData == (void *)0x0) {
        puVar1 = &DAT_0120546e;
    }

    // Process the resource string and return a handle
    result = FUN_004dafd0(puVar1);

    // Clean up the loaded resource if it was allocated
    if (resourceData != (void *)0x0) {
        (*resourceDestructor)(resourceData);
    }

    // Clean up the second handle if non-zero
    if (someHandle != 0) {
        (*someDestructor)(someHandle);
    }

    return result;
}