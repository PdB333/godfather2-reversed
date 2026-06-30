// FUNC_NAME: IDValidator::validateIDList
int __thiscall IDValidator::validateIDList(int *thisPtr, int count, int *outResult)
{
    int i;
    int returnCode;
    uint *tablePtr;
    int local_14; // used by sub_669520
    uint bufferSize;
    int something; // local_c
    uint *buffer; // local_4

    *outResult = 0;
    if (count > 256) {
        return -3;
    }

    // Scan the global table for a matching entry
    for (int idx = 0; idx < 256; idx++) {
        uint entry = g_globalIDTable[idx];
        // Condition: field at thisPtr+8 != 1, *thisPtr < 2, and the value pointed by thisPtr[3] equals entry
        if ((thisPtr[2] != 1) && (*thisPtr < 2) &&
            (*(uint *)thisPtr[3] <= entry) && (entry <= *(uint *)thisPtr[3])) {
            *outResult = 1;
            goto found;
        }
    }

    // Not found; try to allocate a temporary buffer and call sub_669520
    returnCode = sub_669520(&local_14);
    if (returnCode != 0) {
        return returnCode;
    }
    if (local_14 == 1) {
found:
        return 0;
    }

    buffer = (uint *)_calloc(4, 0x40); // allocate 256 bytes
    if (buffer == nullptr) {
        return -2;
    }

    bufferSize = 0;
    int something = 0x40; // loop count? Actually used in memset
    int local_8 = 0;

    // Try each entry up to count
    for (int j = 0; j < count; j++) {
        tablePtr = buffer;
        uint uVar1 = g_globalIDTable[j];
        local_8 = 0;
        _memset(buffer, 0, something << 2); // zero 256 bytes (0x40 * 4)
        bufferSize = (uVar1 & 0xfffffff) ? 1 : 0; // flag if lower 28 bits non-zero
        *tablePtr = uVar1 & 0xfffffff; // store lower 28 bits
        returnCode = sub_6696f0(thisPtr, &bufferSize, &local_14);
        if ((returnCode != 0) || (local_14 == 0)) {
            goto cleanup;
        }
    }

    *outResult = 1;

cleanup:
    if (buffer != nullptr) {
        _memset(buffer, 0, bufferSize << 2); // zero only the used part? Actually bufferSize is flag, not size.
        _free(buffer);
    }
    return returnCode;
}