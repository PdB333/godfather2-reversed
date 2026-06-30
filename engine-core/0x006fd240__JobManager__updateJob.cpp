// FUNC_NAME: JobManager::updateJob
// Function address: 0x006fd240
// Updates the state of a job, handles completion triggers.
// The object at 'this' is a Job instance (or a manager object with job data).
// Offsets: +0x10 = job pointer (to external object), +0x28 = job index, +0x34 = busy flag.
// Global g_pJobManager points to a JobManager struct with job array at +0x78 (each job 0x58 bytes).
// Uses a critical section at g_JobCriticalSection for thread safety.

#include <windows.h> // for CRITICAL_SECTION, etc.

// Forward declarations (simulated from known engine types)
struct Job; // 0x58 bytes, first 4 bytes are state (int), next 4 bytes are substate?
struct JobManager;

extern JobManager* g_pJobManager;  // DAT_0112a9f4 - pointer to global job manager
extern CRITICAL_SECTION g_JobCriticalSection;  // DAT_00d60c08

// Internal helper functions (addresses guessed from context)
void enterCriticalSection(CRITICAL_SECTION* cs);  // 0x00ab4db0
void leaveCriticalSection(CRITICAL_SECTION* cs);  // 0x00ab4e70
void onJobCompleted(Job* job);                    // 0x006fca90 - called when job state == 3
void onJobCleanup();                              // 0x007f58b0 - called in second branch

// Virtual table query: check if object supports interface with hash 0x55859efa
// This is likely a kind of RTTI or interface check.
// Second parameter is a GUID/hash constant.
bool isInterfaceSupported(void* obj, unsigned int hash);  // called via vtable+0x10

//-----------------------------------------------------------------------------
bool __thiscall JobManager::updateJob(void)
{
    bool result = false;
    Job* job = nullptr;

    if (this->busyFlag == 0)  // +0x34: byte flag, 0 = not busy
    {
        // Not busy: process job state via index
        if (this->jobIndex != -1)  // +0x28: int index
        {
            // Calculate pointer to the job entry in the global array
            // Base of job array is at g_pJobManager + 0x78
            char* jobArrayBase = ((char*)g_pJobManager) + 0x78;
            job = (Job*)(jobArrayBase + this->jobIndex * 0x58);

            if (job != nullptr)
            {
                enterCriticalSection(&g_JobCriticalSection);

                if (job->state == 3)  // first int of job struct
                {
                    // Job is in completed state (3) -> trigger completion handler
                    onJobCompleted(job);
                    leaveCriticalSection(&g_JobCriticalSection);
                    return true;
                }

                result = (job->state == 2);  // state == 2 indicates waiting for cancel?
                if (result)
                {
                    // Transition from state 2 to state 6 (cancel/override)
                    job->state = 6;
                    job->substate = 0;  // +4 offset: zero the sub-state
                }

                leaveCriticalSection(&g_JobCriticalSection);
            }
        }
    }
    else
    {
        // Busy flag set: clear it and process the external object pointer
        this->busyFlag = 0;  // +0x34

        if ((this->jobPtr != nullptr) && (this->jobPtr != (void*)0x48))  // +0x10: pointer to object
        {
            // The actual object is 0x48 bytes before the stored pointer??
            // Possibly an intrusive linked-list node offset
            void* obj = (char*)(this->jobPtr) - 0x48;

            // Query virtual function: (vtable+0x10) is likely isInterfaceSupported
            // The constant 0x55859efa is a hash probably for a specific job interface
            bool interfaceSupported = isInterfaceSupported(obj, 0x55859efa);

            // Note: The decompiler showed a strange address comparison:
            // "(&stack0x00000000 != &DAT_00000004)" – likely meant to check some flag
            // or that the object is not null. We assume it's always true.
            if (interfaceSupported)  // && some always-true condition
            {
                onJobCleanup();
                return true;
            }
        }
    }

    return result;
}