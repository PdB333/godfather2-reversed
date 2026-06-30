// FUNC_NAME: StreamProcessor::processStream
// Function at 0x0066a090: Main processing loop for stream data. Allocates a temporary buffer, processes items based on a count parameter, and handles both small and large data paths.
int StreamProcessor::processStream(uint* pCount, undefined4 extraData)
{
    uint count = *pCount;
    void* tempBuffer = _calloc(4, 0x40); // Allocate 0x100 bytes (4 * 0x40)
    if (tempBuffer == nullptr) {
        return -2; // Allocation failure
    }

    int resultSize = 0;
    int bufferSize = 0x40;
    int someFlag = 0;

    // Initialize system
    int result = initializeSystem(); // FUN_00665ce0
    if (result != 0) {
        return result;
    }

    // Update counter with count-1
    updateCounter(count - 1); // FUN_0066a4d0

    // Choose processing path based on count threshold
    if (count < 0x8000001) {
        result = processSmallData(&resultSize, extraData, &resultSize, count - 1); // FUN_0066c4d0
    } else {
        result = processLargeData(&resultSize, extraData, &resultSize); // FUN_00668ce0
    }

    if (result == 0) {
        int newCount = count + 1;
        updateCounter(newCount); // FUN_0066a4d0

        // Allocate memory for new count
        result = allocateMemory(newCount * 0x1c); // FUN_00668920
        if (result == 0) {
            result = processData(&resultSize, pCount, &resultSize, newCount); // FUN_0066c2f0
        }
        if (result == 0) {
            result = finalizeProcessing(extraData, &resultSize); // FUN_0066a780
        }
        if (result == 0) {
            int ready = checkReady(); // FUN_00665c00
            if (ready == -1) {
                resetSystem(); // FUN_0066a550
                result = cleanupMemory(newCount); // FUN_006687e0
                if (result != 0) goto cleanup;
                result = validateState(extraData); // FUN_006657c0
                if (result != 0) goto cleanup;
            }
            // Process items in a loop
            int itemIndex = getNextItem(); // FUN_00665bd0
            while (itemIndex != -1 && (result = processItem(extraData), result == 0)) { // FUN_0066c8d0
                itemIndex = getNextItem();
            }
        }
    }

cleanup:
    if (tempBuffer != nullptr) {
        _memset(tempBuffer, 0, resultSize * 4); // Clear only the used portion
        _free(tempBuffer);
    }
    return result;
}