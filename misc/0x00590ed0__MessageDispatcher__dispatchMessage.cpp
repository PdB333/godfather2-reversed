// FUNC_NAME: MessageDispatcher::dispatchMessage
float MessageDispatcher::dispatchMessage(int this, void* message, void* data) {
    // Stack buffer management
    int bufferSize = 0; // local_10
    int* buffer = nullptr; // local_14
    int* stackPtr = nullptr; // piStack_c
    int* vtablePtr = nullptr; // local_4

    // Initialize stack frame (likely sets up local variables)
    FUN_0058ab50();

    // If buffer size is small, allocate a small temporary buffer
    if (bufferSize < 0x100) {
        int temp = 0;
        FUN_00591c00(&temp); // Possibly allocate or initialize
    }

    // Store data pointer at offset 0x3FC in the buffer structure
    *(void**)((int)buffer + 0x3FC) = data;

    // Copy data from message into buffer (reverse order? indices from 0xFE down)
    int count = 0;
    if (*(char*)((int)message + 1) > 0) {
        uint* src = (uint*)((int)message + 0xC);
        do {
            uint index = 0xFE - count;
            // Ensure buffer has space for the copy
            if (bufferSize <= index) {
                int needed = (index - bufferSize) + 1;
                if (needed != 0) {
                    FUN_005822d0(bufferSize + needed); // Reallocate buffer
                    uint newSize = needed + bufferSize;
                    do {
                        int* slot = (int*)((int)buffer + bufferSize * 4);
                        bufferSize++;
                        if (slot != nullptr) {
                            *slot = 0;
                        }
                    } while (newSize != bufferSize);
                }
            }
            // Copy value from message into buffer at computed index
            *(uint*)((int)buffer + index * 4) = *src;
            src++;
            count++;
        } while (count < *(char*)((int)message + 1));
    }

    // Look up message handler in hash table
    // this+0x70 points to a manager object, which has a hash table at offset 0x30
    int* manager = *(int**)(this + 0x70);
    int* hashTable = *(int**)(manager + 0x30);
    uint messageId = **(uint**)((int)message + 4); // Message ID from message
    uint hashIndex = messageId % hashTable[1]; // hashTable[1] is table size
    uint* entry = *(uint**)(hashTable[0] + hashIndex * 4); // hashTable[0] is bucket array

    // Traverse linked list to find matching entry
    while (entry != nullptr) {
        if (*entry == messageId) {
            if (entry != nullptr && entry != (uint*)0xFFFFFFFC) {
                byte* handler = (byte*)entry[2]; // Handler data pointer
                goto foundHandler;
            }
            break;
        }
        entry = (uint*)entry[3]; // Next entry
    }
    handler = nullptr;

foundHandler:
    if (handler != nullptr) {
        float result = DAT_00e2b1a4; // Default result (some constant)
        // Check handler type (low 6 bits of first byte)
        if ((*handler & 0x3F) < 0x23) {
            // Call handler function from a table indexed by handler type
            result = ((float (*)(int, byte*, int*))(&DAT_0103b050[(*handler & 0x3F) * 4]))(this, handler, &buffer);
        }
        // Get offset from handler (short at offset 2)
        short offset = *(short*)(handler + 2);
        // Ensure buffer is large enough for the result
        if (bufferSize <= (uint)(int)offset) {
            void* tempPtr = nullptr;
            FUN_00591c00(&tempPtr); // Possibly reallocate or clear
        }
        // Store result in buffer at the specified offset
        *(float*)((int)buffer + offset * 4) = result;
    }

    // Cleanup: call virtual destructors or deallocation functions
    (**(code**)(*vtablePtr + 4))(buffer, 0); // Destructor for buffer?
    if (bufferSize != 0) {
        (**(code**)(*stackPtr + 4))(bufferSize, 0); // Deallocate?
    }
    (**(code**)(*stackPtr + 0xC))(); // Final cleanup

    // Return the result (stored in unaff_retaddr by the handler call)
    return result;
}