// FUNC_NAME: EARSGhostManager::processGhostUpdatePacket
int __thiscall EARSGhostManager::processGhostUpdatePacket(int thisPtr, int packet) {
    char* stringPtr;
    char tmpChar;
    int hash;
    int* refCountPtr;
    int retVal = 0;
    char* stringStart;
    uint lookupResult;
    undefined* formattedString;
    undefined1* tempStr;
    int* tableEntry;

    // Check packet type magic (likely a reliable ghost update marker)
    if (*(int*)(packet + 0x8) == 0x32A046EE) {
        // Extract embedded update data (offset +0x14)
        int updateData = *(int*)(packet + 0x14);
        // Check subtype (short at offset +8 in update data)
        if (*(short*)(updateData + 0x8) == 7) {
            // String identifier at offset +0x20 in update data
            stringPtr = (char*)(updateData + 0x20);
            // Compute length? (FUN_004dafd0 might be strlen or similar)
            retVal = FUN_004dafd0(stringPtr); // likely returns string length or ID
            stringStart = stringPtr;
            do {
                tmpChar = *stringStart;
                stringStart = stringStart + 1;
            } while (tmpChar != '\0');
            // Copy string? (FUN_00ab8560 parameters: 0, stringPtr, length)
            FUN_00ab8560(0, stringPtr, (int)stringStart - (updateData + 0x21));
            // Get some global state (e.g., current mission or room)
            lookupResult = FUN_00616720();
            if (lookupResult == 0) {
                // Build key from string and context (e.g., "%s_%s")
                if (*(uint*)(DAT_012234a4 + 0x3C) < *(uint*)(*(int*)(DAT_012234a4 + 0x20) + 0xA4)) {
                    formattedString = (undefined*)(
                        *(uint*)(DAT_012234a4 + 0x3C) * 0x61 +
                        *(int*)(*(int*)(DAT_012234a4 + 0x20) + 0xAC));
                } else {
                    formattedString = &DAT_01222260;
                }
                // Format string: "%s_%s" with stringPtr and formattedString
                FUN_004d4a60(&tempStr, 1, "%s_%s", stringPtr, formattedString);
                if (tempStr == (undefined1*)0x0) {
                    tempStr = &DAT_0120546E; // fallback string
                }
                // Lookup something (e.g., hash table ID)
                lookupResult = FUN_00616d70(tempStr);
                if (tempStr != (undefined1*)0x0) {
                    // free temporary string? (calling function pointer local_c)
                    // Note: local_c is uninitialized; this is likely a bug or a thunk
                    // In decompiled output, local_c might be a freed function pointer
                }
            }
            // If lookup succeeded, update reference count in global table
            if ((((lookupResult != 0xFFFFFFFF) && (lookupResult < 0x1000)) &&
                 (lookupResult * 0x38 != -0x11A0F28)) &&
                (tableEntry = *(int**)(&DAT_011A0F38 + lookupResult * 0x38), tableEntry != (int*)0x0)) {
                *tableEntry = *tableEntry + 1; // increment reference count
            }
            // Store update data pointer for later processing
            *(int*)(packet + 0x1C) = *(int*)(packet + 0x14);
            // Process update via another method (e.g., register ghost)
            retVal = FUN_00489790(thisPtr, *(int*)(packet + 0x14), retVal);
            return retVal;
        }
    } else {
        // Unknown packet type: redirect to default handler
        *(int*)(packet + 0x1C) = *(int*)(packet + 0x14);
        retVal = FUN_00489660();
    }
    return retVal;
}