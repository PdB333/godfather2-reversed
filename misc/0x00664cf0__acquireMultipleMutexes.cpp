// FUNC_NAME: acquireMultipleMutexes
// Function address: 0x00664cf0
// Acquires multiple mutex/lock objects with priority ordering, returns 0 on success,
// -3 if state indicates already locked, or other error codes from internal functions.
// Params: context (pointing to some structure with a field at +8), stateArray (int[4]? state count and flags)

int acquireMultipleMutexes(byte* context, int* stateArray) {
    int result;
    int tempECX;
    bool bVar3;
    int* piVar4;
    int* piVar5;

    // Local "mutex" group structures - each group contains a mutex array and its lock byte pointer
    struct MutexGroup {
        int mutex[3];      // actual mutex object (e.g., atomic compare-and-swap value)
        byte* lockFlag;    // points to a byte flag for this mutex (bit 0 = locked?)
    };

    MutexGroup groupLow;     // local_60[2] -> mutex[2] (size 2), lockFlag = local_54
    int groupLowExtra;       // local_58
    MutexGroup groupMid;     // local_50[3], lockFlag = local_44
    MutexGroup groupHigh;    // local_40[3], lockFlag = local_34
    MutexGroup groupTop;     // local_30[3], lockFlag = local_24
    byte contextStruct[8];    // local_20[8]
    byte dummy[16];           // local_10[16]

    // Early exit if state indicates this resource is already locked
    if ((*stateArray > 0) && ((*(byte*)stateArray[3] & 1) == 0)) {
        return -3;
    }

    // Initialize all mutex groups with a zero value
    result = initMultiLock(dummy, contextStruct, groupHigh.mutex, groupMid.mutex, groupTop.mutex, groupLow.mutex, 0);
    if (result != 0) {
        return result;
    }

    // Check multiple conditions; if any fails, proceed to cleanup
    result = checkCondition();
    if ((result == 0) && ((context == contextStruct || (result = checkCondition(), result == 0)))) {
        groupLowExtra = 0;
        result = checkCondition();
        if ((result == 0) && (result = checkCondition(), result == 0)) {
            resetSomething();   // likely clears intermediate flags

            do {
                bVar3 = (groupHigh.mutex[0] == 0);
                // Loop while groupHigh is not locked and groupMid is not locked and their lock flags are clear
                while ((bVar3 || groupHigh.mutex[0] < 0 || ((*groupHigh.lockFlag & 1) != 0))) {
                    while ((groupMid.mutex[0] > 0 && ((*groupMid.lockFlag & 1) == 0))) {
                        // Try to lock groupMid
                        result = tryLock(groupMid.mutex);
                        if ((result != 0) ||
                            (((groupLow.mutex[0] > 0 && ((*groupLow.lockFlag & 1) != 0)) &&
                             (result = swapLocks(groupLow.mutex, dummy), result != 0)))) {
                            goto cleanup;
                        }
                        result = tryLock(groupLow.mutex);
                        if (result != 0) {
                            goto cleanup;
                        }
                    }

                    // Compare and swap between groups depending on return value of compareSwapSlots
                    result = compareSwapSlots();
                    if (result == -1) {
                        result = swapLocks(groupMid.mutex, groupHigh.mutex);
                        if (result != 0) {
                            goto cleanup;
                        }
                        piVar5 = groupTop.mutex;
                        piVar4 = groupLow.mutex;
                    } else {
                        result = swapLocks(groupHigh.mutex, groupMid.mutex);
                        if (result != 0) {
                            goto cleanup;
                        }
                        piVar5 = groupLow.mutex;
                        piVar4 = groupTop.mutex;
                    }

                    result = swapLocks(piVar4, piVar5);
                    if (result != 0) {
                        goto cleanup;
                    }

                    bVar3 = (groupHigh.mutex[0] == 0);
                    if (bVar3) {
                        result = checkSomething();
                        if (result != 0) {
                            result = tempECX - 4;   // error code derived from ECX
                            goto cleanup;
                        }
                        // Read field at context+8
                        int value = *(int*)(context + 8);
                        if (groupLowExtra == tempECX) {  // cryptic equality check
                            goto waitLoop;
                        } else {
                            break;
                        }
                    }
                }

                // Try to lock groupHigh
                result = tryLock(groupHigh.mutex);
            } while ((result == 0) &&
                    (((groupTop.mutex[0] < 1 || ((*groupTop.lockFlag & 1) == 0)) ||
                      (result = swapLocks(groupTop.mutex, dummy), result == 0)) &&
                     (result = tryLock(groupTop.mutex), result == 0)));
        }
    }
    goto cleanup;

waitLoop:
    // Wait on groupLow mutex while groupLowExtra == 1
    while (groupLowExtra == 1) {
        result = waitOnMutex(groupLow.mutex);
        if (result != 0) {
            goto cleanup;
        }
    }

    // After wait, set a global value
    result = getGlobalContext();
    *(int*)(result + 8) = value;   // store previously read value into global
    result = 0;

cleanup:
    cleanupMultiLock(dummy, contextStruct, groupHigh.mutex, groupMid.mutex, groupTop.mutex, groupLow.mutex, 0);
    return result;
}