// FUNC_NAME: StreamManager::loadStreamToMemory
// Function at 0x005e8510: Loads a stream into an aligned memory buffer, using a manager's vtable for size queries and a global allocator.
// Offsets: this+0x1f0 (file size), this+0x1c0 (allocation pointer), this+0x1c4 (aligned size), this+0x1c8 (stream handle).
bool StreamManager::loadStreamToMemory()
{
    // Global pointer to a vtable/manager (offsets: 0x58=?, 0x60=?, 0x50=?, 0x6c=?)
    // Assuming *DAT_01223510 points to a class instance with virtual methods
    void* vtablePtr = *(void**)DAT_01223510; // base pointer for vtable-like dispatch
    
    // Get two size values from the manager (e.g., block size, alignment)
    int blockSize = (*(code**)((int)vtablePtr + 0x58))();   // returns base block size?
    int alignment = (*(code**)((int)vtablePtr + 0x60))();   // returns alignment requirement

    bool success = false;  // return value (uVar5)
    
    if (blockSize != 0) {
        // Update file size accumulator
        *(int*)(this + 0x1F0) = *(int*)(this + 0x1F0) + blockSize;
        
        // Calculate total bytes to allocate: current size - 1 + alignment
        int neededBytes = *(int*)(this + 0x1F0) - 1 + alignment;
        
        // Allocation pointer from global allocator (DAT_01223518+4)
        // DAT_01223518 is likely a struct with allocator pointer at offset 4
        if (*(int*)(DAT_01223518 + 4) != 0 && neededBytes != 0) {
            // Stack variables for allocation flags/alignment: {2, 4, 0}
            int stackArgs[3] = {2, 4, 0}; // alignment=4? 
            int allocPtr = (**(code***)(*(int*)(DAT_01223518 + 4)))(neededBytes, stackArgs);
            *(int*)(this + 0x1C0) = allocPtr;
        }
        
        // Compute aligned size (next multiple of alignment)
        *(int*)(this + 0x1C4) = (allocPtr - 1 + alignment) & ~(alignment - 1);
        
        if (allocPtr == 0) {
            return false;
        }
    }
    
    // Call manager's seek/initialize function using aligned size and accumulated offset
    int streamHandle = (*(code**)((int)vtablePtr + 0x50))(*(int*)(this + 0x1C4), *(int*)(this + 0x1F0));
    *(int*)(this + 0x1C8) = streamHandle;
    
    if (streamHandle >= 0) {
        // Check viability (virtual function 0x6c) and then load actual data
        char viable = (*(code**)((int)vtablePtr + 0x6c))(streamHandle, 0);
        success = false;
        if (viable != 0) {
            // FUN_005e80f0 likely performs the actual memory load
            if (FUN_005e80f0() != 0) {
                success = true;
            }
        }
        // FUN_005dbc10 likely cleans up after the loading process
        FUN_005dbc10(*(int*)(this + 0x1C8), *(int*)(this + 0x1F0));
    }
    
    return success;
}