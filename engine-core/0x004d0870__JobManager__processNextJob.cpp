// FUNC_NAME: JobManager::processNextJob

#include <cstdint>

// Forward declarations
class JobNode;

// Global mutex flag (0 or 1)
static volatile bool g_jobMutex = false;

// External callback for job validation (function pointer at DAT_01223378 + 0x50)
extern bool (*g_jobValidationCallback)(JobNode* job, int param); // assumed signature

// External function: start a streaming/async operation on a job node
// Parameters: node data pointer, unknown (0), callback, node pointer, unknown (0)
extern void startAsyncJob(void* data, int arg, void (*callback)(), void* userData, int arg2);

// JobNode structure offsets (relative to this node pointer)
// +0x00: next pointer
// +0xA8: flags (byte) – bits: 0x02 = skip flag, 0x04 = priority flag
// +0xB0: active flag (int) – 0 = inactive, 1 = in progress
struct JobNode {
    JobNode* next;
    // ... other fields ...
    uint8_t flags;          // offset 0xA8 (within a larger struct, accessed via byte)
    int32_t active;         // offset 0xB0
    // The actual data block starts at offset 0x8 (piVar2 + 2)
    // After flags/active there is more data, but startAsyncJob uses node + 2 as data pointer
};

// JobManager class (structure at param_1)
class JobManager {
public:
    JobNode* jobListHead; // +0x4c (offset 76)
    JobNode* currentJob;  // +0x48 (offset 72)
    uint8_t unknownFlag;  // +0x64 (offset 100) – set to 1 or 0 based on validation result
};

void __fastcall JobManager::processNextJob(JobManager* this_) {
    char cVar1;

    if (g_jobMutex) {
        return;
    }

    JobNode* node = this_->jobListHead; // +0x4c

    if (node == nullptr) {
        return;
    }

    g_jobMutex = true;

    // Find the first node that is not active and not marked for skip (flags & 2)
    while ( (node->active != 0) || ((node->flags & 2) != 0) ) {
        node = node->next;
        if (node == nullptr) {
            g_jobMutex = false;
            return;
        }
    }

    // Check if node has priority (flags & 4) and a validation callback exists and returns true
    if ((node->flags & 4) && (g_jobValidationCallback != nullptr)) {
        cVar1 = g_jobValidationCallback(node, 1);
        if (cVar1 != 0) {
            this_->unknownFlag = 1; // +0x64
            g_jobMutex = false;
            return;
        }
    }

    // No priority or validation failed – start the job
    this_->unknownFlag = 0;          // +0x64
    this_->currentJob = node;        // +0x48
    node->active = 1;                // mark as active (offset 0xB0)

    // Start async operation on the job's data (node + 2 = offset 0x8)
    startAsyncJob(node + 2, 0, FUN_004d19a0, node, 0);

    g_jobMutex = false;
}