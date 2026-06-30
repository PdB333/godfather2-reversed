// FUNC_NAME: JobQueue::removeMatchingJob
// Removes a job from the array that matches m_matchType and has state < 3, then cleans up the job's owner and deletes the job.
// Function address: 0x006b4080
// Class fields:
//   +0x40 m_matchType (int)
//   +0xB4 m_pArray (int**) - array of job pointers
//   +0xB8 m_count (int)

typedef int* Job; // Each job is a pointer to its data

// External helper functions (from other modules)
int __fastcall getJobType(Job job);          // FUN_007914e0
int __fastcall getJobState(Job job);         // FUN_00791750
int* __fastcall getJobOwnerManager(void);    // FUN_00791300 - singleton manager
bool __fastcall isOwnerActive(int* manager); // FUN_0083e6a0
void __fastcall releaseOwner(int* manager);  // FUN_0083de30
void __fastcall deleteJob(Job job);          // FUN_006b2f70

int __fastcall JobQueue::removeMatchingJob(JobQueue* this)
{
    int count = *(int*)((char*)this + 0xB8);
    if (count == 0) {
        return 0;
    }

    int** array = *(int***)((char*)this + 0xB4);
    uint i = 0;
    Job removedJob = 0;

    do {
        Job job = array[i];
        int jobType = getJobType(job);
        if (jobType == *(int*)((char*)this + 0x40)) {
            int jobState = getJobState(job);
            if (jobState < 3) {
                removedJob = job;
                if (i != (uint)(count - 1)) {
                    // Replace removed element with the last element
                    array[i] = array[count - 1];
                }
                *(int*)((char*)this + 0xB8) = count - 1;
                break;
            }
        }
        i++;
    } while (i < (uint)count);

    if (removedJob != 0) {
        int* ownerManager = getJobOwnerManager();
        if (ownerManager != 0) {
            int** somePtr = (int**)(ownerManager + 0x158);
            if (*somePtr != 0) {
                *somePtr = 0;
                if (isOwnerActive(ownerManager)) {
                    releaseOwner(ownerManager);
                }
            }
        }
        deleteJob(removedJob);
    }

    return removedJob;
}