// FUNC_NAME: JobManager::processJob

// Reconstructed from 0x005f37f0 - Processes a job/task item, handling allocation, callback setup, and cleanup.
// Uses a global mutex (gJobMutex) for thread safety.
// The job data structure is pointed to by this+0x14.

#include <atomic>

// Forward declarations of external functions
extern void lockMutex(void* mutex);        // FUN_00ab4db0
extern void unlockMutex(void* mutex);      // FUN_00ab4e70
extern int allocateBuffer();               // FUN_00ac28b0 - returns handle/pointer
extern void setCallback(int handle, void* callback, int jobData, int param); // FUN_00ac3b80
extern void queueAsyncWork(int handle, int* output, int a, int b, int size, int c, void* completion, int jobData, int d); // FUN_00ac4290
extern void cleanupJob();                  // FUN_005ea0d0

// Global mutex (DAT_00e2aea0)
extern void* gJobMutex;

// Global pool base (DAT_01223510) - array of 0x10-byte entries at offset 0x81bc
extern int* gJobPoolBase;

// Static callback functions (addresses)
extern void sJobCallback();                // LAB_005f3c50
extern void sJobCompletionCallback();      // FUN_005f38d0

// Job data structure (pointed to by this+0x14)
struct JobData {
    int field_0x00;      // unknown
    int field_0x04;      // unknown
    int field_0x08;      // unknown
    int field_0x0c;      // unknown
    int field_0x10;      // unknown
    int field_0x14;      // unknown
    int field_0x18;      // unknown
    int field_0x1c;      // unknown
    int field_0x20;      // unknown
    int field_0x24;      // unknown
    int field_0x28;      // unknown
    int field_0x2c;      // unknown
    int field_0x30;      // unknown
    int field_0x34;      // unknown
    int field_0x38;      // unknown
    int field_0x3c;      // unknown
    int field_0x40;      // unknown
    int field_0x44;      // unknown
    int field_0x48;      // unknown
    int field_0x4c;      // unknown
    int field_0x50;      // unknown
    int field_0x54;      // unknown
    int field_0x58;      // unknown
    int field_0x5c;      // unknown
    int field_0x60;      // unknown
    int field_0x64;      // unknown
    int field_0x68;      // unknown
    int field_0x6c;      // unknown
    int field_0x70;      // unknown
    int field_0x74;      // unknown
    int field_0x78;      // unknown
    int field_0x7c;      // unknown
    int field_0x80;      // unknown
    int field_0x84;      // unknown
    int field_0x88;      // unknown
    int field_0x8c;      // unknown
    int field_0x90;      // unknown
    int field_0x94;      // unknown
    int poolIndex;       // +0x9c - index into global pool
    int stateFlag;       // +0xa0 - >=0 means active
    int jobType;         // +0xa4 - 2 for one path, else other
    int field_0xa8;      // unknown
    int field_0xac;      // unknown
    int field_0xb0;      // unknown
    int field_0xb4;      // unknown
    int field_0xb8;      // unknown
    int field_0xbc;      // unknown
    int field_0xc0;      // unknown
    int field_0xc4;      // unknown
    int field_0xc8;      // unknown
    int field_0xcc;      // unknown
    int field_0xd0;      // unknown
    int field_0xd4;      // unknown
    int field_0xd8;      // unknown
    int field_0xdc;      // unknown
    int field_0xe0;      // unknown
    int field_0xe4;      // unknown
    int field_0xe8;      // unknown
    int field_0xec;      // unknown
    int field_0xf0;      // unknown
    int field_0xf4;      // unknown
    int bufferHandle;    // +0xf8 - handle from allocateBuffer
    int outputField;     // +0xfc - output pointer for async work
};

// JobManager class (this points to it)
class JobManager {
public:
    JobData* jobData;    // +0x14 - pointer to the job data being processed

    void processJob() {
        JobData* data = this->jobData;
        if (data == nullptr) {
            return;
        }

        lockMutex(gJobMutex);

        if (data->stateFlag >= 0) {
            int handle = allocateBuffer();
            data->bufferHandle = handle;

            if (data->jobType == 2) {
                // Type 2: synchronous callback
                if (handle != 0) {
                    setCallback(handle, sJobCallback, (int)data, 0);
                    unlockMutex(gJobMutex);
                    return;
                }
            } else {
                // Other types: async work with completion callback
                if (handle != 0) {
                    queueAsyncWork(handle, &data->outputField, 0, 0, 0x20, 0, sJobCompletionCallback, (int)data, 0);
                    unlockMutex(gJobMutex);
                    return;
                }

                // If allocation failed, release pool entry if valid
                if (data->poolIndex >= 0) {
                    int* poolEntry = gJobPoolBase + 0x81bc / sizeof(int) + data->poolIndex * 0x10 / sizeof(int);
                    // Atomic decrement on pool entry (LOCK prefix)
                    std::atomic_fetch_sub((std::atomic<int>*)poolEntry, 1);
                }

                cleanupJob();
            }
        }

        unlockMutex(gJobMutex);
    }
};