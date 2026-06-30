// FUNC_NAME: BitStream::writeFloatTyped
// Address: 0x00630be0
// Reads a typed value (float or int) from input stream and writes a float to output stream.
// Part of TNL serialization for packet building.

int __thiscall BitStream::writeFloatTyped(void* thisPtr) {
    // Offsets:
    // +0x08: pointer to current write position (output cursor)
    // +0x0C: pointer to current read position (input cursor)
    // The write buffer is assumed to be at +0x08, size derived from +0x00/+0x04 (not shown)
    // The read buffer is similarly at +0x0C

    float floatValue;
    int typeCheck;
    int* readCursor;           // piVar3

    readCursor = *(int**)((char*)thisPtr + 0x0C);
    // If no more data to read, fall through to write placeholder
    if (*(int**)((char*)thisPtr + 0x08) <= readCursor) {
        goto skipRead;
    }
    if (readCursor == nullptr) {
        goto skipRead;
    }

    // Check type marker: 3 = float, 4 = int
    if (*readCursor != 3) {
        if (*readCursor != 4) {
            goto skipRead;   // Unknown type, treat as missing
        }
        // int type: check if convertible to float (e.g., not NaN)
        if (FUN_00636850(&floatValue) == 0) {
            goto skipRead;
        }
        // Prepare to read the int value as float
        typeCheck = 3;      // Will write as float
        floatValue = floatValue;   // local_c was set but unused
        readCursor = &typeCheck;   // Force type to 3 for reading? (unusual)
    }

    // Read the float value from the stream
    floatValue = *((float*)(readCursor + 1));  // piVar3[1] cast to float

    // Check for sentinel value indicating invalid data (e.g., -0.0 or NaN flag)
    if (floatValue == DAT_00e2b05c) {
        // Skip forward through any invalid entries, logging warnings
        do {
            // Update read cursor from stream
            readCursor = *(int**)((char*)thisPtr + 0x0C);
            // If no more data or cursor invalid, break out of skip
            if (*(int**)((char*)thisPtr + 0x08) <= readCursor) break;
            if (readCursor == nullptr) break;
            if (*readCursor == 3) break;      // valid float
            if (*readCursor == 4) {           // int, check conversion
                if (FUN_00636850(&typeCheck) != 0) break;
            }
            // Invalid entry: log warning
            FUN_00627ac0(PTR_s_number_00e2a8a8);
            // And set a safe default
skipRead:
            floatValue = 0.0f;
        } while (true);
    }

    // Write the float value to the output stream
    int* writeCursor = *(int**)((char*)thisPtr + 0x08);
    *writeCursor = 3;                         // type = float
    writeCursor[1] = (int)(floatValue) & DAT_00e44680;   // value with mask
    // Advance write cursor by 8 bytes (two ints)
    *(int*)((char*)thisPtr + 0x08) += 8;

    return 1;   // success
}