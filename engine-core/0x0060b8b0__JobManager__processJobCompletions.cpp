// FUNC_NAME: JobManager::processJobCompletions

void __thiscall JobManager::processJobCompletions(float timeoutSeconds)
{
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);

    EnterCriticalSection(&g_jobCriticalSection);

    if (g_jobCount <= 0)
    {
        LeaveCriticalSection(&g_jobCriticalSection);
        return;
    }

    int idx = 0;
    do
    {
        int lastIndex = g_jobCount;

        // g_jobEntryArray is an array of pointers to job structures (size = g_jobCount)
        // Each job struct: +0x00 pointer (vtable?), +0x04 field1, +0x08 field2, +0x10 field3? +0x14 field4? +0x18 field5? +0x1c byte flag, +0x1d byte flag.
        int* lastJob = g_jobEntryArray[lastIndex]; // Actually array at DAT_011da8ec

        // Check if the last job is not currently in use (byte at offset 0x1d == 0)
        if (*(char*)(lastJob + 0x1d / sizeof(int)) == '\0') // offset 0x1d
        {
            // Decrement count (remove last job)
            g_jobCount--;

            // Call a completion helper with two parameters from the job struct
            // FUN_0060b3b0: likely AsyncJob::complete(job->param1, job->param2)
            AsyncJob::complete(lastJob[4], lastJob[6]); // offsets 0x10 and 0x18

            if (lastJob[0] != 0) // has a vtable pointer?
            {
                // Call a virtual function on the job manager's vtable (offset 4)
                // DAT_01205868 points to a vtable/manager object
                ((void (__thiscall*)(int, int))(*g_jobManagerVtable + 4))(lastJob[4], lastJob[5]);

                lastJob[4] = 0;               // clear param1
                *(uint8_t*)(lastJob + 7) = 1;  // set completion flag at offset 0x1c
            }

            // Check the swapped entry (now at index g_jobCount) – if its flag at +0x1c is zero, we still have work pending?
            // g_jobStateArray is an array of pointers (DAT_011da8f0) paralleling g_jobEntryArray
            int* swappedJob = g_jobStateArray[g_jobCount];
            if (*(char*)(swappedJob + 0x1c / sizeof(int)) == '\0') // offset 0x1c
            {
                g_jobCount++; // restore count? 
                break;
            }
        }
        else
        {
            // Find an unused job in the middle and swap it with the last entry
            for (; idx < g_jobCount; idx++)
            {
                int* candidate = g_jobStateArray[idx];
                if (*(char*)(candidate + 0x1d / sizeof(int)) == '\0') // not in use
                {
                    g_jobStateArray[idx] = g_jobEntryArray[lastIndex]; // swap pointers
                    g_jobEntryArray[lastIndex] = candidate;
                    break;
                }
            }
        }

        // Check if we exceeded the allowed time budget
        LARGE_INTEGER currentTime;
        QueryPerformanceCounter(&currentTime);
        int64_t elapsedTicks = currentTime.QuadPart - startTime.QuadPart;
        double elapsedSec = (double)elapsedTicks * g_frequencyInverse; // _DAT_01163ecc is inverse of QPC frequency
        if (elapsedSec >= timeoutSeconds)
            break;

        if (g_jobCount <= idx)
        {
            LeaveCriticalSection(&g_jobCriticalSection);
            return;
        }
    } while (true);

    LeaveCriticalSection(&g_jobCriticalSection);
}