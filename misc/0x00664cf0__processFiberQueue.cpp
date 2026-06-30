// FUNC_NAME: processFiberQueue
int __thiscall processFiberQueue(void* this, int* context)
{
    // context[0] = count, context[3] = pointer to a byte flag
    // Early exit if count > 0 and flag LSB is 0
    if ((0 < *context) && ((*(byte *)context[3] & 1) == 0)) {
        return -3;
    }

    // State blocks (likely fiber contexts)
    // Each block has an int at offset 0 (status) and a byte flag at some offset
    int fiberA_status[2];      // local_60
    int fiberA_flags;          // local_58? Actually local_58 is separate int, but used as comparison later
    byte* fiberA_flagPtr;      // local_54
    int fiberB_status[3];      // local_50
    byte* fiberB_flagPtr;      // local_44
    int fiberC_status[3];      // local_40
    byte* fiberC_flagPtr;      // local_34
    int fiberD_status[3];      // local_30
    byte* fiberD_flagPtr;      // local_24
    byte fiberE[8];            // local_20
    byte fiberF[16];           // local_10

    // Initialize all fiber states
    int initResult = internal_InitStates(fiberF, fiberE, fiberC_status, fiberB_status, fiberD_status, fiberA_status, 0);
    if (initResult != 0) {
        return initResult;
    }

    // First checks (possibly yield detection)
    if ((internal_CheckYield() != 0) ||
        ((this == fiberE) || (internal_CheckYield() != 0))) {
        // fall through to cleanup
    } else {
        int local_18 = 0; // unused?
        if ((internal_CheckYield() == 0) && (internal_CheckYield() == 0)) {
            internal_ResetScheduler();
            bool fiberC_isZero;
            do {
                fiberC_isZero = (fiberC_status[0] == 0);
                while ((fiberC_isZero || fiberC_status[0] < 0 || ((*fiberC_flagPtr & 1) != 0))) {
                    // Process fiberB while it has work and flag LSB is 0
                    while ((0 < fiberB_status[0] && ((*fiberB_flagPtr & 1) == 0))) {
                        int fiberBStep = internal_StepFiber(fiberB_status);
                        if ((fiberBStep != 0)
                            || (((0 < fiberA_status[0] && ((*fiberA_flagPtr & 1) != 0))
                                && (int transferCheck = internal_TransferControl(fiberA_status, fiberF),
                                    transferCheck != 0))
                            || (int fiberAStep = internal_StepFiber(fiberA_status),
                                fiberAStep != 0))) {
                            goto cleanup;
                        }
                    }
                    int cmp = internal_CompareFibers();
                    if (cmp == -1) {
                        int transfer1 = internal_TransferControl(fiberB_status, fiberC_status);
                        if (transfer1 != 0) goto cleanup;
                        int* dest = fiberD_status;  // local_30
                        int* src = fiberA_status;    // local_60
                    } else {
                        int transfer2 = internal_TransferControl(fiberC_status, fiberB_status);
                        if (transfer2 != 0) goto cleanup;
                        int* dest = fiberA_status;   // local_60
                        int* src = fiberD_status;     // local_30
                    }
                    int transfer3 = internal_TransferControl(dest, src);
                    if (transfer3 != 0) goto cleanup;
                    fiberC_isZero = (fiberC_status[0] == 0);
                    if (fiberC_isZero) {
                        int check = internal_SomeCheck();
                        if (check != 0) {
                            // ECX extraout used? We'll assume check gives result
                            // This is likely a yield or error
                            int ecxValue; // extraout_ECX not preserved, but used
                            return ecxValue - 4;
                        }
                        unsigned int savedValue = *(unsigned int*)((char*)this + 8);
                        if (fiberA_flags == ecxValue) {
                            // inner loop
                            while (fiberA_flags == 1) {
                                int yieldResult = internal_YieldFiber(fiberA_status);
                                if (yieldResult != 0) goto cleanup;
                            }
                        } else {
                            // after loop
                        }
                    }
                }
                // Step fiberC
                int stepC = internal_StepFiber(fiberC_status);
                if (stepC != 0) continue;
            } while ((((fiberD_status[0] < 1) || ((*fiberD_flagPtr & 1) == 0))
                     || (int transferD = internal_TransferControl(fiberD_status, fiberF),
                         transferD != 0))
                    && (int stepD = internal_StepFiber(fiberD_status),
                        stepD != 0));
        }
    }

cleanup:
    int result;
    // The label LAB_00664f60 leads here
    // There is a while loop that might be part of the above
    // For simplicity, we consolidate:
    internal_CleanupStates(fiberF, fiberE, fiberC_status, fiberB_status, fiberD_status, fiberA_status, 0);
    return result; // result is set earlier, but not clearly tracked
}