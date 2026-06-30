// FUNC_NAME: NetworkLayer::processOutgoingQueue
int NetworkLayer::processOutgoingQueue(void* context) {
    // Global array of object pointers (likely network ghosts or packets)
    int* current = (int*)DAT_01129f8c;   // +0x0: start of array
    int* end = (int*)DAT_01129f90;       // +0x4: end of array

    while (current != end) {
        int objectPtr = *current;        // Dereference to get object address
        FUN_004d3bc0(context);           // Initialize/begin processing (e.g., packet encoding start)
        
        // Retrieve next element from a container; returns a pointer to an int
        int* dataPtr = (int*)FUN_00698c00(local_14, local_10);
        int retrievedValue = *dataPtr;   // Value from the container

        // Compare retrieved value with expected (objectPtr + 12)
        // +12 likely a field offset (e.g., sequence number, ID, or self-pointer)
        bool isDifferent = (retrievedValue != (objectPtr + 0xC));
        
        if (isDifferent) {
            // Call virtual function at offset 0x20 on the retrieved object
            // (i.e., object->vtable[0x20/4] ?)
            FUN_004d3e20(retrievedValue + 0x20);
        }

        // local_10[0] might hold a reference count or flag; if nonzero, call function pointer
        // local_4 appears uninitialized in decompilation – likely a member or global callback
        if (local_10[0] != 0) {
            (*local_4)(local_10[0]);     // Callback with the count
        }

        if (isDifferent) {
            return 1;                    // Successfully processed this entry
        }
        current++;
    }
    return 0;                            // No entries processed
}