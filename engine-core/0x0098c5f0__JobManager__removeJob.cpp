// FUNC_NAME: JobManager::removeJob

#include <cstring> // for memmove

// Job structure (size unknown, but at least 0x34 bytes)
// Offset 0x00: pointer to some object (likely with a virtual release function)
// Offset 0x0C: release function pointer for object at +0x00
// Offset 0x10: pointer to another object
// Offset 0x1C: release function pointer for object at +0x10
// Offset 0x30: job ID (int)
struct Job {
    void* objectA;               // +0x00
    // ... padding ...
    void (*releaseA)(void*);     // +0x0C (called on objectA if non-null)
    void* objectB;               // +0x10
    // ... padding ...
    void (*releaseB)(void*);     // +0x1C (called on objectB if non-null)
    int jobId;                   // +0x30
};

// Forward declaration of memory deallocation function
void FUN_009c8eb0(void* ptr);   // custom deallocator

// JobManager class (member at +0x230 points to array of job pointers,
// +0x234 points to end of used portion)
class JobManager {
public:
    // Remove a job by IDs from the dynamic array
    // Returns 1 on success, 0 if not found
    int __thiscall removeJob(int jobId)
    {
        Job** slot = reinterpret_cast<Job**>(this + 0x230);
        Job** end  = reinterpret_cast<Job**>(this + 0x234);

        while (slot < end)
        {
            Job* job = *slot;
            if (job && job->jobId == jobId)
                break;
            slot++;
        }

        if (slot >= end)
            return 0;  // not found

        Job* job = *slot;
        if (job)
        {
            // Release associated objects
            if (job->objectB)
                job->releaseB(job->objectB);
            if (job->objectA)
                job->releaseA(job->objectA);

            // Deallocate the job structure itself
            FUN_009c8eb0(job);
        }

        // Remove from array by shifting remaining elements
        *slot = nullptr;
        slot++;
        if (slot < end)
        {
            int bytesToMove = reinterpret_cast<int>(end) - reinterpret_cast<int>(slot);
            memmove(slot - 1, slot, bytesToMove);
        }

        // Decrement the end pointer
        end--;
        reinterpret_cast<Job**>(this + 0x234) = end;

        return 1;
    }
};