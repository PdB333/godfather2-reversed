// FUNC_NAME: PacketQueue::~PacketQueue
// Function address: 0x00620350
// Role: Destructor for a thread-safe packet queue. Drains remaining items, waiting up to 250 iterations (timeout), then releases resources.

// Assumed extern helper functions (from EA EARS engine threading library)
extern void criticalSectionEnter();          // FUN_00c9eac0
extern void criticalSectionLeave();          // FUN_00c9eae0
extern int criticalSectionTryLock(int mode, int* timeoutPtr); // FUN_00c9cd40, returns 0 on success? (param 3 is mode, 1 or 3)
extern void pushToExternalBuffer(int bufferID, void* item, int size); // FUN_00c9cbe0, first arg is param_1[2] (some queue ID)
extern void tempSleep();                     // FUN_00ab4b40, yields thread
extern void cleanupA();                      // FUN_006200d0
extern void cleanupB();                      // FUN_00ab4d30
extern void cleanupC();                      // FUN_00c9ec70

// Constants
extern float g_timeoutCheckValue; // DAT_00e2b1a4, likely 0.0f (sentinel for "timed out")
extern void* g_vtable1;           // PTR_FUN_00e41490
extern void* g_vtable2;           // PTR_LAB_00e4145c

struct PacketQueue {
    // Offset 0x00: virtual function table pointer
    void* vtable;

    // Offset 0x04-0x08: probably other fields
    
    // Offset 0x09: flag indicating initialization (used to decide whether to call a cleanup function)
    char initialized;

    // Offset 0x0C-0x1F: padding? Decompiler shows param_1+3 used in a call (offset 0x0C)
    
    // Offset 0x20: (param_1[2]) - identifier for push operation (buffer ID)
    int bufferID;

    // Offset 0x84: (param_1[0x21]) - ring buffer capacity
    int capacity;

    // Offset 0x88: (param_1[0x22]) - current number of items in queue
    int count;

    // Offset 0x8C: (param_1[0x23]) - value to write into each dequeued item (maybe a flag)
    int itemValue;

    // Offset 0x90: (param_1[0x24]) - unknown

    // Offset 0x94: (param_1[0x25]) - ring buffer write index (head)
    int headIndex;

    // Offset 0x98: (param_1[0x26]) - base pointer for items (each item is 0x10 bytes)
    char* itemBase;

    // Offset 0x9C: (param_1[0x27]) - flag indicating whether to run final cleanup
    int needsCleanupFlag;

    // Offset 0xA0: (param_1[0x28]) - pointer to an external structure with a field at +0x10 used in push
    void* externalData;
};

void __fastcall PacketQueue::destructor(PacketQueue* this) {
    int retryCount;
    int* timeoutResult;
    float timeoutValue; // actually an int from criticalSectionTryLock

    // Set vtable to base class (derived destructor)
    this->vtable = g_vtable1;

    criticalSectionEnter(); // acquire lock?

    // If initialized flag is set, call some cleanup routine (probably for the external buffer)
    if (this->initialized != 0) {
        // The parameter is at offset 0x0C (param_1 + 3)
        cleanupExternalBuffer(&this->initialized);
    }

    // Try to lock with mode 1 and no timeout? (second param = 0)
    criticalSectionTryLock(1, 0);
    criticalSectionLeave();

    retryCount = 0;
    int currentCount = this->count;

    while (currentCount != 0) {
        // Push current item to some external queue (using bufferID, data at externalData+0x10)
        pushToExternalBuffer(this->bufferID, this->externalData + 0x10, 3);

        if (this->count == 0) {
            timeoutResult = 0;
        } else {
            // Compute address of current item: itemBase + headIndex * 0x10
            timeoutResult = this->itemBase + this->headIndex * 0x10;
        }

        // Re-enter critical section and try to lock with mode 3 (with timeout)
        criticalSectionEnter();
        criticalSectionTryLock(3, &timeoutResult);
        criticalSectionLeave();

        // Check if the operation timed out (fStack_18 is actually the return from criticalSectionTryLock)
        timeoutValue = (float)timeoutResult; // Assumption: returned value stored in fStack_18
        if (timeoutValue == g_timeoutCheckValue) {
            // Successfully got the item: write value into the buffer
            if (this->count != 0) {
                char* itemPtr = this->itemBase + this->headIndex * 0x10;
                *(int*)itemPtr = this->itemValue;
                // The original code: puVar2[2] = puVar2[2]; (no-op)
                *(int*)(itemPtr + 4) = 0; // second int field set to 0
                this->headIndex++;
                if (this->headIndex >= this->capacity) {
                    this->headIndex = 0;
                }
                this->count--;
            } else {
                // If count was zero, break out?
                break;
            }
        } else {
            // Timeout occurred: perform a small sleep and increment retry count
            tempSleep();
            retryCount++;
            if (retryCount >= 250) {
                break; // max retries exceeded
            }
        }
        currentCount = this->count;
    }

    // If final cleanup flag is set, perform additional cleanup
    if (this->needsCleanupFlag != 0) {
        criticalSectionEnter();
        finalCleanup(); // FUN_00ca5940
        criticalSectionLeave();
    }

    // Chain cleanup calls
    cleanupA(); // FUN_006200d0
    cleanupB(); // FUN_00ab4d30
    cleanupC(); // FUN_00c9ec70

    // Set vtable to final destructor state
    this->vtable = g_vtable2;
    return;
}