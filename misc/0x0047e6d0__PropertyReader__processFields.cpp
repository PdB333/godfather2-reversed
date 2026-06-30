// FUNC_NAME: PropertyReader::processFields

void __thiscall PropertyReader::processFields(int thisPtr, void* buffer)
{
    int* intPtr;
    uint* uintPtr;
    uint tempValue;
    uint** tempPtrArray;
    uint** nodePtr;
    bool doneFlag;
    char compactFlag;
    int bitfieldBase;
    uint* dataPtr;
    uint currentIndex;
    uint totalCount;
    uint* fieldPtr;
    short indexShort;
    uint fieldType;
    uint** iterator;

    // Initialize the reader with a hash (0x883fb8ef) for format identification
    FUN_0043aff0(buffer, 0x883fb8ef);
    nodePtr = iterator; // This assignment is likely from the initialization; iterator is a stack variable set by FUN_0043aff0

    while (true) {
        // Check termination condition depending on mode
        if (compactFlag == '\0') {
            doneFlag = (*nodePtr == nullptr);
        } else {
            doneFlag = (currentIndex == totalCount);
        }
        if (doneFlag) break;

        // Determine current field pointer
        uint** currentFieldPtr;
        if (compactFlag == '\0') {
            currentFieldPtr = nodePtr;
        } else {
            currentFieldPtr = &fieldPtr;  // Use stack fieldPtr as temp
        }

        // Extract field type (offset 6 check for magic 0x25E3)
        if (*(short*)((int)currentFieldPtr + 6) == 0x25E3) {
            uintPtr = (uint*)(uint)*(ushort*)(currentFieldPtr + 1);
        } else {
            uintPtr = currentFieldPtr[1];
        }

        switch ((int)uintPtr) {
        case 0:
            // Clear the field at +0x50 (e.g., a list or sub-object)
            FUN_0043ad10(thisPtr + 0x50);
            nodePtr = iterator;
            break;
        case 1:
            // Set pointer at +0x68 from the third element of the current field
            if (compactFlag == '\0') {
                currentFieldPtr = nodePtr;
            } else {
                currentFieldPtr = &fieldPtr;
            }
            *(uint**)(thisPtr + 0x68) = currentFieldPtr[2];
            break;
        case 2:
            // Set pointer at +0x74 from the third element
            if (compactFlag == '\0') {
                currentFieldPtr = nodePtr;
            } else {
                currentFieldPtr = &fieldPtr;
            }
            *(uint**)(thisPtr + 0x74) = currentFieldPtr[2];
            break;
        case 3:
            // Handle string field (offset +0x6C)
            if (compactFlag == '\0') {
                currentFieldPtr = nodePtr;
            } else {
                currentFieldPtr = &fieldPtr;
            }
            if (*(short*)((int)currentFieldPtr + 6) == 0x25E3) {
                // String is stored with length prefix
                if (*currentFieldPtr == nullptr) {
                    currentFieldPtr = (uint**)&DAT_00e2a89b; // empty string placeholder
                } else {
                    currentFieldPtr = (uint**)((int)currentFieldPtr[2] + (int)*currentFieldPtr);
                }
            } else {
                // String pointer is at offset +8 (currentFieldPtr + 2)
                currentFieldPtr = currentFieldPtr + 2;
            }
            intPtr = (int*)(thisPtr + 0x6C);
            FUN_004086d0(intPtr); // Clear string
            FUN_00408310(intPtr); // Possibly initialize or reserve
            if (currentFieldPtr != nullptr && *(char*)currentFieldPtr != '\0') {
                tempValue = FUN_004dafd0(currentFieldPtr); // Convert to internal string
                FUN_00408260(intPtr, tempValue);            // Assign string
                if (*intPtr != 0) {
                    // Push the string area into the list at +0x3C
                    FUN_00407e60(thisPtr + 0x3C, intPtr);
                }
            }
            break;
        }

        // Advance iterator based on mode
        if (compactFlag == '\0') {
            // Linked list traversal: move to next node using size field at node start
            if ((int)currentIndex < 0) {
                iterator = (uint**)((int)nodePtr + (int)*nodePtr);
                FUN_0043b140();
                nodePtr = iterator;
            } else if ((int)currentIndex < (int)(totalCount - 1)) {
                currentIndex = currentIndex + 1;
                iterator = (uint**)((int)nodePtr + (int)*nodePtr);
                nodePtr = (uint**)((int)nodePtr + (int)*nodePtr);
            } else {
                iterator = (uint**)&DAT_01163cf8; // end-of-list sentinel
                nodePtr = (uint**)&DAT_01163cf8;
            }
        } else {
            // Compact array with presence bitmap
            currentIndex = currentIndex + 1;
            if (currentIndex != totalCount) {
                indexShort = (short)currentIndex;
                // Check if bit at currentIndex is set in bitfield
                if ((*(byte*)((currentIndex >> 3) + bitfieldBase) & (byte)(1 << ((byte)currentIndex & 7))) == 0) {
                    // Field present: copy from dataPtr
                    fieldType = *dataPtr;
                    fieldPtr = dataPtr;
                    dataPtr = dataPtr + 1;
                } else {
                    // Field absent: mark as null
                    fieldPtr = nullptr;
                    fieldType = 0;
                }
            }
        }
    }

    // Final check: if any of the first four fields (offsets 0x50-0x5C) are non-zero and a global is set,
    // push that global into the list at +0x3C
    if ( (*(int*)(thisPtr + 0x50) != 0 || *(int*)(thisPtr + 0x54) != 0 ||
          *(int*)(thisPtr + 0x58) != 0 || *(int*)(thisPtr + 0x5C) != 0) &&
          DAT_0120e93c != 0 ) {
        FUN_00407e60(thisPtr + 0x3C, &DAT_0120e93c);
    }
    return;
}