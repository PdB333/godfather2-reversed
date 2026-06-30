// FUNC_NAME: JobQueue::processJobQueue
void JobQueue::processJobQueue(void)
{
    LARGE_INTEGER startTime;
    LARGE_INTEGER currentTime;
    int i;
    int j;
    int count;
    int* jobPtr;
    uint elapsedHigh;
    int elapsedLow;
    uint64 elapsed;
    float elapsedSeconds;

    QueryPerformanceCounter(&startTime);
    EnterCriticalSection(&gCriticalSection);

    count = gJobCount; // DAT_01205854
    if (count < 1) {
        LeaveCriticalSection(&gCriticalSection);
        return;
    }

    do {
        if (*(char*)(gJobArray1[count] + 0x29) == '\0') { // job not finished?
            jobPtr = (int*)gJobArray0[count];
            gJobCount = count - 1;
            processJob(jobPtr[7], jobPtr[9]); // FUN_0060be80
            if (*jobPtr != 0) {
                (*(code**)(**GlobalVTable + 4))(jobPtr[7], jobPtr[8]); // release/finish callback
                jobPtr[7] = 0;
                *(char*)(jobPtr + 10) = 1; // mark as done
            }
            if (*(char*)(gJobArray1[count] + 0x28) == '\0') {
                gJobCount = count + 1;
                goto done;
            }
        } else {
            // find a finished job slot in array 1 to swap with current
            for (i = 0; i < count; i++) {
                int* slotPtr = gJobArray1[i];
                if (*(char*)(slotPtr + 0x29) == '\0') {
                    gJobArray1[i] = gJobArray0[count];
                    gJobArray0[count] = slotPtr;
                    break;
                }
            }
        }

        QueryPerformanceCounter(&currentTime);
        elapsedLow = currentTime.LowPart - startTime.LowPart;
        elapsedHigh = currentTime.HighPart - startTime.HighPart - (uint)(currentTime.LowPart < startTime.LowPart);
        elapsed = ((uint64)elapsedHigh << 32) | (uint64)(uint)elapsedLow;
        elapsedSeconds = (float)(elapsed & 0x7FFFFFFFFFFFFFFF) * gTimeMultiplier; // _DAT_01163ecc
        if (elapsedSeconds > 1.0f) {
            goto done;
        }
    } while (count < gJobCount);

    LeaveCriticalSection(&gCriticalSection);
    return;

done:
    LeaveCriticalSection(&gCriticalSection);
}