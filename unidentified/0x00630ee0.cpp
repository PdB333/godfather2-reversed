// FUN_NAME: CommandStream::filterAndCopyEvents
int CommandStream::filterAndCopyEvents(void* thisPtr) {
    // Read pointers from this: +0x8 = write position (output), +0xC = read position (input)
    // The read buffer extends from readCur to readEnd (stored at +0x8 initially? Actually +0x8 is used as readEnd at start, then reused as write position.)
    int* readCur  = *(int**)((uint8_t*)thisPtr + 0xC);
    int* readEnd  = *(int**)((uint8_t*)thisPtr + 0x8);

    // If no more data, fall back
    bool readEndReached = (readCur >= readEnd || readCur == nullptr);
    if (readEndReached) {
        goto fallback;
    }

    int type = *readCur;
    float value;

    if (type == 3) {
        // Direct float value
        value = *(float*)(readCur + 1);
    } else if (type == 4) {
        // Requires conversion via external function
        float converted;
        if (FUN_00636850(&converted) != 0) {
            // Conversion succeeded: use a temporary type-3 pair
            value = converted;
        } else {
            goto fallback; // conversion failed
        }
    } else {
        goto fallback; // unknown type
    }

    // Sentinel elimination: if the value matches a global sentinel, skip this and subsequent invalid entries
    if (value == DAT_00e2b05c) {
        // Skip past the sentinel command (2 ints)
        readCur += 2;
        // Continue scanning until a valid command is found or end is reached
        while (readCur < readEnd && readCur != nullptr) {
            int scanType = *readCur;
            if (scanType == 3) {
                value = *(float*)(readCur + 1);
                break; // found replacement
            } else if (scanType == 4) {
                float scanConvert;
                if (FUN_00636850(&scanConvert) != 0) {
                    value = scanConvert;
                    break; // found replacement
                }
            }
            // Invalid entry: issue debug warning and advance
            FUN_00627ac0(PTR_s_number_00e2a8a8); // "Number" assertion
            readCur += 2;
        }
        // If loop exited because end was reached, reset value to 0
        if (readCur >= readEnd || readCur == nullptr) {
            value = 0.0f;
        }
    }

    // Write the output command (always type 3) to the output buffer
    {
        int* writePos = *(int**)((uint8_t*)thisPtr + 0x8);
        *writePos = 3; // command type
        FUN_00b9c041(); // likely floating-point state sync
        double dVal = (double)value;
        *(float*)(writePos + 1) = (float)dVal;
        // Advance write pointer by 8 bytes
        *(int**)((uint8_t*)thisPtr + 0x8) = (int*)((uint8_t*)writePos + 8);
    }
    return 1; // success

fallback:
    // On any failure (invalid type, conversion failure, out-of-range), write 0.0 value
    value = 0.0f;
    // The sentinel check will be skipped because 0.0f != DAT_00e2b05c
    // Then the write block above is executed (omitted here for brevity, but same code)
    // (In original, this fallback sets local_14=0.0 and falls through to the write block.)
    // To match original behavior, we actually write 0.0:
    {
        int* writePos = *(int**)((uint8_t*)thisPtr + 0x8);
        *writePos = 3;
        FUN_00b9c041();
        *(float*)(writePos + 1) = 0.0f;
        *(int**)((uint8_t*)thisPtr + 0x8) = (int*)((uint8_t*)writePos + 8);
    }
    return 1; // returns 1 even on fallback
}