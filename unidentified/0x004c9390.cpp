// FUN_004c9390: EARSUpdateManager::processCleanupQueue

#include <cstdint>

// Forward declarations of external functions
void MutexLock(void* mutex);
void ReleaseObject(void* obj);
void SomeTextureRelease(uint32_t handle, void* param);
void DebugAssert();
void ProcessQueueNode(void* queue, uint8_t* outHash, void* node, void* listEntry);
void FreeMemory(void* ptr);
void FinalizeCleanup();

// Global variables (addresses from Ghidra)
extern void* gMutex;                // DAT_012069d4
extern uint32_t gTextureManager;    // DAT_01223508
extern uint32_t gGlobalFlag;       // DAT_012234bc
extern BufferManager* gBufferMgr;  // DAT_0122350c

struct BufferManager {
    // +0x1738: pointer to buffer (array of pairs)
    uint32_t* buffer;  // actually void* but treat as uint32_t*
    // +0x173c: count of valid entries
    int32_t count;
};

void EARSUpdateManager::processCleanupQueue()
{
    // Lock mutex for thread safety
    MutexLock(gMutex);

    // If there's an active resource operation, release it
    if (this->activeOperation != 0) {
        ReleaseObject(this->activeOperation);
        int32_t op = this->activeOperation;
        if (*(uint8_t*)(op + 4) != 0 && *(int32_t*)(op + 0x290) != 0) {
            SomeTextureRelease(gTextureManager, *(int32_t*)(op + 0x290));
            *(uint8_t*)(op + 4) = 0;
        }
        this->activeOperation = 0;
    }

    // Process pending cleanup queue (doubly-linked list with sentinel)
    if (this->cleanupQueue != 0) {
        int32_t head = *(int32_t*)(this->cleanupQueue + 0x20);
        while (head != 0) {
            int32_t queue = this->cleanupQueue;  // container
            int32_t* listSentinel = *(int32_t**)(queue + 0x1c);
            int32_t* firstEntry = (int32_t*)*listSentinel;
            if (firstEntry == listSentinel) {
                DebugAssert();  // Empty list should not happen
            }
            int32_t dataPtr = firstEntry[4];
            uint8_t hashBuffer[12];  // 12-byte hash
            ProcessQueueNode(this->cleanupQueue, hashBuffer, queue, firstEntry);
            if (dataPtr != 0) {
                FreeMemory((void*)dataPtr);
            }
            head = *(int32_t*)(this->cleanupQueue + 0x20);
        }
    }

    // Finalize global cleanup
    if (gGlobalFlag != 0) {
        FinalizeCleanup();
    }

    // Pop last element from buffer manager's deferred deletion stack
    BufferManager* mgr = gBufferMgr;
    if (mgr != 0 && mgr->count != 0) {
        int32_t cnt = mgr->count;
        if (cnt != 1) {
            uint32_t* buf = mgr->buffer;
            // Move last pair to front
            buf[0] = buf[cnt * 2 - 2];
            buf[1] = buf[cnt * 2 - 1];
        }
        mgr->count--;
    }
}