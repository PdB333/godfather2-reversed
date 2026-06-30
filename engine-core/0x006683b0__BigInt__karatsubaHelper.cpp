// FUNC_NAME: BigInt::karatsubaHelper
int BigInt::karatsubaHelper(int *bigInt)
{
    int *tempPtr;
    uint alignedSize;
    int errorState;
    int *upperHalfPtr;
    int *lowerHalfPtr;
    uint halfSize;
    size_t allocSize;
    int tempSize;
    int *scratchBuffer1;
    int *scratchBuffer2;
    int *resultBuffer1;
    int *resultBuffer2;
    int *combinedResult;
    uint resultSize;

    // Allocate buffer for half operations
    halfSize = *bigInt / 2;
    alignedSize = halfSize & 0x8000003f;
    if ((int)alignedSize < 0) {
        alignedSize = (alignedSize - 1 | 0xffffffc0) + 1;
    }
    allocSize = (halfSize - alignedSize) + 0x80;
    lowerHalfPtr = (int *)_calloc(4, allocSize);
    if (lowerHalfPtr == nullptr) {
        return -2; // 0xFFFFFFFE
    }

    resultSize = 0;
    // local_2c unused
    // bufferSize = allocSize

    // Check multiple initialization states
    errorState = checkInitialization(); // FUN_006678c0
    if (errorState == 0) {
        errorState = checkInitialization();
        if (errorState == 0) {
            errorState = checkInitialization();
            if (errorState == 0) {
                errorState = checkInitialization();
                if (errorState == 0) {
                    errorState = checkInitialization();
                    if (errorState == 0) {
                        // Copy lower half of input
                        tempPtr = (int *)bigInt[3]; // pointer to data
                        lowerHalfPtr = lowerHalfPtr;
                        upperHalfPtr = lowerHalfPtr; // Initially point to same? Actually later differentiated
                        // Copy first half into buffer
                        for (uint i = 0; i < halfSize; i++) {
                            lowerHalfPtr[i] = tempPtr[i];
                        }
                        // Copy second half into same buffer (offsets)
                        upperHalfPtr = lowerHalfPtr; // offset by halfSize? Actually later used as separate pointer
                        uint copyCount = halfSize;
                        if ((int)halfSize < *bigInt) {
                            do {
                                *upperHalfPtr = *tempPtr; // overlapping? This is confusing
                                copyCount++;
                                tempPtr++;
                                upperHalfPtr++;
                            } while ((int)copyCount < *bigInt);
                        }

                        // Setup sizes
                        tempSize = *bigInt - halfSize; // upper half size
                        resultSize = halfSize; // lower half size

                        // Allocate scratch and result buffers
                        int *scratch1 = nullptr;
                        int *scratch2 = nullptr;
                        int scratchAllocResult = bigIntAllocate(scratch1); // FUN_00665b10? Actually calling something
                        if (scratchAllocResult == 0) {
                            errorState = bigIntAdd(lowerHalfPtr, scratchBuffer1); // FUN_0066a660
                            if ((errorState == 0) && (errorState = bigIntAdd(&tempSize, scratchBuffer2), errorState == 0)) {
                                errorState = bigIntAdd(&tempSize, &resultSize); // FUN_0066a780
                                if ((((errorState == 0) &&
                                     ((errorState = bigIntAdd(resultBuffer1, resultBuffer1), errorState == 0 &&
                                      (errorState = bigIntAdd(scratchBuffer1, scratchBuffer2), errorState == 0)) &&
                                     (errorState = bigIntAdd(resultBuffer2, resultBuffer1), errorState == 0)))) &&
                                    (((errorState = bigIntSetZero(halfSize), errorState == 0 &&
                                      (errorState = bigIntSetZero(halfSize * 2), errorState == 0)) &&
                                     (errorState = bigIntFree(resultBuffer1), errorState == 0)))) &&
                                   (errorState = bigIntFree(resultBuffer2), errorState == 0)) {
                                    errorState = 0;
                                }
                            }
                            // Cleanup scratch2
                            if (scratchBuffer2 != nullptr) {
                                memset(scratchBuffer2, 0, tempSize * 4);
                                free(scratchBuffer2);
                                scratchBuffer2 = nullptr;
                                // Reset size
                            }
                        }
                        // Cleanup scratch1
                        if (scratchBuffer1 != nullptr) {
                            memset(scratchBuffer1, 0, tempSize * 4); // size mismatch? Actually using different size
                            free(scratchBuffer1);
                            scratchBuffer1 = nullptr;
                        }
                    }
                    // Cleanup combinedResult
                    if (combinedResult != nullptr) {
                        memset(combinedResult, 0, resultBuffer1[0] * 4);
                        free(combinedResult);
                    }
                }
                // Cleanup scratchBuffer2? Actually different variable
                if (resultBuffer2 != nullptr) {
                    memset(resultBuffer2, 0, scratchBuffer2[0] * 4);
                    free(resultBuffer2);
                }
            }
            // Cleanup upperHalfPtr
            if (upperHalfPtr != nullptr) {
                memset(upperHalfPtr, 0, tempSize * 4);
                free(upperHalfPtr);
                upperHalfPtr = nullptr;
                // Reset size
            }
        }
        // Cleanup lowerHalfPtr
        if (lowerHalfPtr != nullptr) {
            memset(lowerHalfPtr, 0, resultSize * 4);
            free(lowerHalfPtr);
            lowerHalfPtr = nullptr;
        }
    }

    // Final cleanup for primary buffer
    if (lowerHalfPtr != nullptr) {
        memset(lowerHalfPtr, 0, resultSize * 4);
        free(lowerHalfPtr);
    }
    return errorState;
}