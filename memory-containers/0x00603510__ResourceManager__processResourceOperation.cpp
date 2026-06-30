// FUNC_NAME: ResourceManager::processResourceOperation
struct ResourceOperationData {
    int handle;          // +0x00
    int param1;          // +0x04
    int param2;          // +0x08
    void (*release)(int); // +0x0C
    char* resourceName;  // +0x10
    int flags;           // +0x14
    int unknown;         // +0x18
    void (*nameCleanup)(char*); // +0x1C
};

void __thiscall ResourceManager::processResourceOperation(void* this, void* param2)
{
    ResourceOperationData data;
    char* resourceName = nullptr;
    char* savedResourceName;

    // Retrieve resource name from this (e.g., a member pointer or string)
    ResourceManager::getResourceName(this, &resourceName); // FUN_00603330

    savedResourceName = resourceName;
    if (resourceName == nullptr) {
        resourceName = ""; // &DAT_0120546e
    }

    // Perform the operation, filling data struct
    ResourceManager::lookupResource(param2, &data, resourceName, 0); // FUN_00603610

    // Use the handle and parameter
    ResourceManager::someUtil(data.handle, 0, data.param1); // FUN_004d43f0

    if (data.handle != 0) {
        data.release(data.handle);
    }

    if (savedResourceName != nullptr) {
        data.nameCleanup(savedResourceName);
    }
}