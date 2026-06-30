// FUNC_NAME: DataBuffer::readCompressedFloat
// Address: 0x006312e0
// Reads a compressed float from a buffer containing (type, value) pairs.
// Type 3 = direct float, type 4 = compressed via FUN_00636850.
// Sentinel value in DAT_00e2b05c triggers skipping.
// Updates internal read/write pointer by 8 bytes.

int DataBuffer::readCompressedFloat(int param_1) {
    int* currentEntry; // pointer to current entry in buffer
    int targetType; // what type we are looking for (3 -> 2 -> 1)
    float value; // parsed float
    int tempType; // temporary type for synthetic entry
    float tempValue; // temporary value for synthetic entry
    float parsedValue; // the float after conversion or direct read

    // Initial attempt: read first entry from buffer
    currentEntry = (int*)(*(int*)(param_1 + 0xC) + 8); // point to second entry? Actually buffer+8
    targetType = 3;
    if (*(int**)(param_1 + 8) <= currentEntry || currentEntry == nullptr)
        goto skipFirst; // insufficient data? set value to 0

    if (*currentEntry != 3) {
        if (*currentEntry != 4)
            goto skipFirst;
        // type 4: try to convert via FUN_00636850
        int result = FUN_00636850(&tempValue);
        if (result == 0)
            goto skipFirst;
        tempType = 3;
        parsedValue = tempValue;
        currentEntry = &tempType; // synthetic entry
    }

    // Now currentEntry points to a valid entry of type 3 or synthetic
    parsedValue = (float)currentEntry[1]; // value from entry
    if (parsedValue == DAT_00e2b05c) { // sentinel? skip until finding valid entry
        while (true) {
            currentEntry = (int*)(*(int*)(param_1 + 0xC) + 8);
            if (*(int**)(param_1 + 8) > currentEntry && currentEntry != nullptr &&
                (*currentEntry == targetType || (*currentEntry == 4 && FUN_00636850(&tempValue) != 0))) {
                break;
            }
            targetType = 2;
            FUN_00627ac0(PTR_s_number_00e2a8a8); // log "number"
skipFirst:
            parsedValue = 0.0f;
        }
    }

    // Now process the second entry similarly with targetType now possibly 2
    currentEntry = *(int**)(param_1 + 0xC);
    if (*(int**)(param_1 + 8) <= currentEntry || currentEntry == nullptr)
        goto skipSecond;

    if (*currentEntry != targetType) {
        if (*currentEntry != 4)
            goto skipSecond;
        int result = FUN_00636850(&tempValue);
        if (result == 0)
            goto skipSecond;
        tempType = targetType;
        parsedValue = tempValue;
        currentEntry = &tempType;
    }

    value = (float)currentEntry[1];
    if (value == DAT_00e2b05c) {
        while (true) {
            currentEntry = *(int**)(param_1 + 0xC);
            if (*(int**)(param_1 + 8) > currentEntry && currentEntry != nullptr &&
                (*currentEntry == targetType || (*currentEntry == 4 && FUN_00636850(&tempType) != 0))) {
                break;
            }
            targetType = 1;
            FUN_00627ac0(PTR_s_number_00e2a8a8);
skipSecond:
            value = 0.0f;
        }
    }

    // Write final result to output position
    int* outputPtr = *(int**)(param_1 + 8);
    *outputPtr = targetType;
    double dVal = (double)value;
    FUN_00b9a9fa(); // possibly debug/breakpoint
    outputPtr[1] = (int)(float)dVal; // store value as int? might be a reinterpretation
    *(int*)(param_1 + 8) = *(int*)(param_1 + 8) + 8; // advance pointer

    return 1;
}