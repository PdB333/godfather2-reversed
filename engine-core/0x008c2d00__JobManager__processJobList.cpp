//FUNC_NAME: JobManager::processJobList
void __thiscall JobManager::processJobList(int thisPtr, int* jobArray, int newJobCount, int processQueue)
{
    int* dataPtr;
    int jobId;
    int objectPtr;
    int i;
    uint index;
    char newObjectParams[68];

    index = 0;
    if (jobArray[1] != 0) {
        do {
            jobId = *(int*)(*jobArray + index * 4);
            int randomVal = getRandomInt();
            if (randomVal < 3) {
                addToProcessQueue(processQueue);
            }
            else {
                objectPtr = getObjectByID(jobId);
                if ((objectPtr != 0) && (isObjectActive(1), *(int*)(objectPtr + 4) != 7)) {
                    removeFromProcessQueue(processQueue);
                    setObjectState(2, 0);
                }
            }
            index = index + 1;
        } while (index < (uint)jobArray[1]);
    }
    if (newJobCount != 0) {
        lockMutex(*(int*)(thisPtr + 0x54), 2);
        if (newJobCount != 0) {
            do {
                int newJobId = createNewObject(newObjectParams);
                if (newJobId != 0) {
                    incrementNewObjectCounter(1);
                    addToProcessQueue(processQueue);
                    int currentCount = jobArray[1];
                    int capacity = jobArray[2];
                    if (currentCount == capacity) {
                        if (capacity == 0) {
                            capacity = 1;
                        }
                        else {
                            capacity = capacity * 2;
                        }
                        reallocateArray(capacity);
                    }
                    dataPtr = (int*)(*jobArray + jobArray[1] * 4);
                    jobArray[1] = jobArray[1] + 1;
                    if (dataPtr != (int*)0x0) {
                        *dataPtr = newJobId;
                    }
                }
                newJobCount = newJobCount - 1;
            } while (newJobCount != 0);
        }
        unlockMutex();
    }
    return;
}