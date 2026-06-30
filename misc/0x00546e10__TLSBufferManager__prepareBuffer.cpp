// FUNC_NAME: TLSBufferManager::prepareBuffer
// Function at 0x00546e10: Initializes a thread-local buffer manager with capacity for a given number of elements (size 0x1c each).
// Returns pointer to the TLS buffer manager.
// param_1: unused (possibly flags)
// param_2: pointer to object providing needed element count via virtual function at vtable offset 0x220 (likely getBufferSizeNeeded())
int TLSBufferManager::prepareBuffer(int unused, int* sourceObject)
{
    // Get TLS value (unused result, possibly thread ID or pool handle)
    TlsGetValue(DAT_01139810);

    // Allocate a temporary structure (size 0x1c, flags 0xb) and set element size field
    int* tempBlock = (int*)FUN_00aa2680(0x1c, 0xb);
    *(short*)(tempBlock + 4) = 0x1c; // elementSize = 28 bytes

    // Get pointer to thread-local buffer manager
    TLSBufferManager* manager = (TLSBufferManager*)FUN_00bedf00();

    // Query required element count from source object
    int neededCount = (**(int (__thiscall**)(int*))(*sourceObject + 0x220))(sourceObject);

    // Current capacity (masked high bits)
    uint currentCapacity = *(uint*)(manager + 0x18) & 0x3fffffff;

    // If capacity is insufficient, reallocate the buffer array
    if ((int)currentCapacity < neededCount) {
        int newCapacity = currentCapacity * 2;
        if (newCapacity <= neededCount) {
            newCapacity = neededCount;
        }
        FUN_00aa4110(manager + 0x10, newCapacity, 1); // Realloc buffer at offset 0x10
    }

    // Set buffer manager fields
    int globalData = DAT_00e4458c; // Global data pointer
    *(int*)(manager + 0x14) = neededCount; // Count of elements
    *(int*)(manager + 0x0c) = globalData;  // Data pointer

    // Final initialization using source object
    FUN_00546ec0(manager, sourceObject);

    return (int)manager;
}