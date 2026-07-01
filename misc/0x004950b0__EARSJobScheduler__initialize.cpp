// FUNC_NAME: EARSJobScheduler::initialize
// Address: 0x004950b0
// This function initializes the job scheduler, setting up job queues per priority and allocating job objects.
// It takes an allocator (vtable), number of priority levels, array of job counts per priority, and total job count.
// Uses internal spinlocks (LOCK/UNLOCK) for thread safety.

void __thiscall EARSJobScheduler::initialize(EARSJobScheduler* this,
    MemoryAllocator* allocator,      // param_2: allocator interface (+0x80)
    int numPriorities,                // param_3: number of priority levels (+0x84)
    uint* jobCountsPerPriority,       // param_4: array of job counts per priority
    uint totalJobCount)               // param_5: total number of job slots (+0x81)
{
    void* mem;
    int i;
    uint* ptr;
    uint* dst;
    uint uVar5;
    int* pQueue; // pointer to queue pointer array (+0x89)
    int loopCount;
    EARSJobScheduler* curSlot; // local_44, advances through priority structures

    // Store parameters
    this->allocator = allocator;                  // +0x80
    this->totalJobCount = totalJobCount;           // +0x81
    this->numPriorities = numPriorities;           // +0x84

    // Initialize sync counters
    LOCK();
    this->activeJobs = 0;                         // +0x8e (some job count)
    UNLOCK();

    LOCK();
    this->pendingJobs = 0;                        // +0x8d (another count)
    UNLOCK();

    this->initialized = 0; // byte                  +0x83

    if (numPriorities != 0) {
        pQueue = (int*)(&this->priorityQueues);   // +0x89
        loopCount = numPriorities;
        curSlot = this;

        do {
            // Store count for this priority (at offset before queue pointer array)
            pQueue[-4] = (int)*jobCountsPerPriority; // +0x85 (relative to slot)

            // Clear first two dwords of the priority slot (likely lock/status)
            LOCK();
            curSlot->someLock = 0;                // +0x00
            UNLOCK();

            LOCK();
            curSlot->someOther = 0;               // +0x04
            UNLOCK();

            // Allocate memory for job queue of this priority
            // Virtual function call on allocator: (vtable+8) is Alloc(size, name, tag)
            mem = (void*)(allocator->vtable->alloc)(*jobCountsPerPriority * 0x1c, "EARSJobScheduler", 0x80);
            *pQueue = (int)mem;                   // +0x89

            // Zero out the allocated job queue
            memset(mem, 0, *jobCountsPerPriority * 0x1c);

            // Initialize each job entry in the queue
            uVar5 = 0;
            if (*jobCountsPerPriority != 0) {
                i = 0;
                do {
                    LOCK();
                    *(uint*)((uint)mem + i + 0x14) = 0xFFFFFFFF; // job entry +0x14
                    UNLOCK();
                    LOCK();
                    *(uint*)((uint)mem + i + 0x18) = 0xFFFFFFFF; // job entry +0x18
                    UNLOCK();
                    uVar5++;
                    i += 0x1c;
                } while (uVar5 < *jobCountsPerPriority);
            }

            // Advance to next priority slot (each slot is 0x20 ints = 0x80 bytes)
            curSlot = (EARSJobScheduler*)((uint)curSlot + 0x80);
            pQueue++;
            jobCountsPerPriority++;
            loopCount--;
        } while (loopCount != 0);
    }

    // Initialize EARS subsystem components
    EARS_init(0, 1, 0);                          // FUN_00ab5070
    EARS_someSetup(local_20);                     // FUN_00ab50c0 (local_20 is a buffer)

    // Allocate array of job object pointers (size totalJobCount*4 + 4 for header)
    uVar5 = totalJobCount * 4; // size per job pointer is 4 bytes
    ptr = (uint*)heapAlloc(uVar5 + 4);            // FUN_009c8e50: allocates size+4
    if (ptr != 0) {
        dst = ptr + 1;
        *ptr = totalJobCount; // store count at beginning
        for (i = totalJobCount - 1; i >= 0; i--) {
            jobObjectInit();                      // FUN_00ab54d0: initialize job object
        }
    }
    this->jobObjects = (uint*)dst;                // +0x82

    // Register callbacks for each job object
    for (i = 0; i < (int)totalJobCount; i++) {
        jobPrepare();                             // FUN_00ab5450
        const char* name = "EARSJob";
        uint param = 0xFFFFFFFE;
        uint callbackContext = getCallbackContext(); // FUN_00ab5470
        registerJobCallback(&jobProcessorFunc, 0, someStack, callbackContext); // FUN_00ab7410, jobProcessorFunc at 0x004956b0
    }

    return;
}