// FUNC_NAME: GlobalObjectFactory::createObject
// Address: 0x008dba40
// Creates and registers a new object of size 0x38 if the global system is initialized.

void* __fastcall GlobalObjectFactory::createObject(undefined4 param_1)
{
    char isReady;
    int newObject;
    void* result;

    // Check if system is initialized
    isReady = isGlobalSystemReady();  // FUN_00481660
    if (isReady != '\0') {
        // Allocate memory for object (56 bytes)
        newObject = allocateMemory(0x38);  // FUN_009c8e50
        if (newObject != 0) {
            // Construct the object using param_1 (likely a context or parent pointer)
            result = (void*)constructObject((int)newObject, param_1);  // FUN_008db8f0
            registerObject(result);  // FUN_00481690
            return result;
        }
        // Allocation failed, register null
        registerObject(0);  // FUN_00481690
    }
    return 0;
}