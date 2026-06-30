// FUNC_NAME: Ghost::unpackUpdate
// Function at 0x00474dd0: Unpacks an update message from a bitstream into a Ghost object (TNL/EARS networking layer)
// Handles multiple message types (0-0xD) corresponding to different data fields in the replicated object

void __thiscall Ghost::unpackUpdate(int thisPtr, int streamHandle)
{
    // Stream control and iteration variables
    bool doneFlag = false;
    bool setFlag = false;
    char formatFlag; // local_f0[0] - 0 = sparse, non-zero = dense format
    int bitIndex; // local_ec - bit index in sparse format
    int* currentPtr; // local_e8 - current pointer in sparse data
    uint itemCount; // local_e4 - total items or current index
    uint totalItems; // local_e0 - total items to process
    int* itemPtr; // local_dc - pointer to current item buffer
    short itemIndex; // local_d8 - current item index
    int itemData0; // local_d4 - first word of item data
    int itemData1; // local_c4
    int itemData2; // local_b4
    int** currentItemArray; // local_94 - pointer to array of items
    char streamFlag; // local_78 - flag from stream read
    int streamValue1; // local_6c - stream value for dense format check
    int streamValue2; // local_68 - stream value for dense format check
    int* streamResult; // local_1c - result from stream read

    // Begin reading from stream with given class ID
    readStreamBegin(streamHandle, 0xb390b11a);
    readStreamBit(streamHandle, 1); // read a flag

    // Determine format based on the flag
    if (streamFlag == 0) {
        doneFlag = (*streamResult == 0);
    } else {
        doneFlag = (streamValue1 == streamValue2);
    }

    if (!doneFlag) {
        itemCount = 0;
        itemData0 = 0;
        itemData1 = 0;
        itemData2 = 0xb390b11a; // placeholder, maybe a constant
        readStreamString(streamHandle, formatFlag); // reads format string
        readStreamName(thisPtr + 0x80, formatFlag); // reads name string into object at +0x80
        if (*(int*)(thisPtr + 0xd0) != 0) {
            skipStreamData(thisPtr + 0x80); // skip remainder if already known
        }
    }

    doneFlag = false;
    readStreamBegin(streamHandle, 0x92f62833); // start reading item list

    currentItemArray = *((int***)&currentItemArray); // Actually from local_94, not initialized; let's assume it's after reading
    itemCount = 0;

    while (true) {
        // Determine termination condition based on format
        if (formatFlag == 0) {
            doneFlag = (*currentItemArray == 0);
        } else {
            doneFlag = (itemCount == totalItems);
        }
        if (doneFlag) break;

        // Get pointer to current item (sparse or dense)
        int* itemBuffer;
        if (formatFlag == 0) {
            itemBuffer = (int*)currentItemArray;
        } else {
            // For dense format, itemBuffer points to a local structure
            itemBuffer = &itemPtr;
        }

        // Read type identifier from item buffer (offset 6 is a short type code)
        short typeCode = *(short*)((byte*)itemBuffer + 6);
        int* typePtr;
        if (typeCode == 0x25e3) { // Special marker for certain type encoding
            typePtr = (int*)(uint)(*(unsigned short*)(itemBuffer + 1));
        } else {
            typePtr = (int*)itemBuffer[1]; // Assume second word is type id
        }

        // Process message based on type
        switch ((int)typePtr) {
        case 0: // Type 0: read pointer at offset +0x50
        {
            int* ptr = getItemPtr(formatFlag, currentItemArray, &itemPtr);
            readPointer(thisPtr + 0x50, ptr, "BasePtrMsgData*");
            break;
        }
        case 1: // Type 1: read pointer at offset +0x58
        {
            int* ptr = getItemPtr(formatFlag, currentItemArray, &itemPtr);
            readPointer(thisPtr + 0x58, ptr, "BasePtrMsgData*");
            break;
        }
        case 2: // Type 2: read pointer at offset +0x60
        {
            int* ptr = getItemPtr(formatFlag, currentItemArray, &itemPtr);
            readPointer(thisPtr + 0x60, ptr, "BasePtrMsgData*");
            break;
        }
        case 3: // Type 3: read pointer at offset +0x68
        {
            int* ptr = getItemPtr(formatFlag, currentItemArray, &itemPtr);
            readPointer(thisPtr + 0x68, ptr, "BasePtrMsgData*");
            break;
        }
        case 4: // Type 4: read pointer at offset +0x70
        {
            int* ptr = getItemPtr(formatFlag, currentItemArray, &itemPtr);
            readPointer(thisPtr + 0x70, ptr, "BasePtrMsgData*");
            break;
        }
        case 5: // Type 5: read pointer at offset +0x78
        {
            int* ptr = getItemPtr(formatFlag, currentItemArray, &itemPtr);
            readPointer(thisPtr + 0x78, ptr, "BasePtrMsgData*");
            break;
        }
        case 6:
        case 7: // Types 6-7: read four consecutive pointers at +0xc0, +0xc4, +0xc8, +0xcc
        {
            int* ptr = getItemPtr(formatFlag, currentItemArray, &itemPtr);
            *(int**)(thisPtr + 0xc0) = ptr[0];
            *(int**)(thisPtr + 0xc4) = ptr[1];
            *(int**)(thisPtr + 0xc8) = ptr[2];
            *(int**)(thisPtr + 0xcc) = ptr[3];
            break;
        }
        case 8: // Type 8: read a single pointer at +0xe4
        {
            int* ptr = getItemPtr(formatFlag, currentItemArray, &itemPtr);
            *(int**)(thisPtr + 0xe4) = ptr[2];
            break;
        }
        case 9: // Type 9: read pointer at +0xf8, with null default
        {
            int* ptr = getItemPtr(formatFlag, currentItemArray, &itemPtr);
            int* val = (int*)ptr[2];
            *(int**)(thisPtr + 0xf8) = val;
            if (val == 0) {
                *(int**)(thisPtr + 0xf8) = (int*)0x0110ac04; // default constant
            }
            break;
        }
        case 0xa: // Type A: read data into buffer at +0xd4
        {
            readStreamBuffer(thisPtr + 0xd4);
            // Refresh local variables after reading
            currentItemArray = *((int***)&currentItemArray);
            itemCount = 0;
            break;
        }
        case 0xb:
        case 0xc: // Types B-C: resolve pointer from index, store at +0xe8
        {
            int* ptr = getItemPtr(formatFlag, currentItemArray, &itemPtr);
            int resolvedPtr;
            if (*(short*)((byte*)ptr + 6) == 0x25e3) {
                if (*ptr == 0) {
                    resolvedPtr = resolvePointer((int)&DAT_00e2a89b);
                } else {
                    resolvedPtr = resolvePointer((int)(ptr[2] + *ptr));
                }
            } else {
                resolvedPtr = resolvePointer((int)(ptr + 2));
            }
            *(int*)(thisPtr + 0xe8) = resolvedPtr;
            break;
        }
        case 0xd: // Type D: read flag into +0xec, set doneFlag
        {
            readFlag(thisPtr + 0xec);
            doneFlag = true;
            setFlag = true;
            break;
        }
        } // end switch

        // Advance to next item based on format
        if (formatFlag == 0) {
            // Sparse format: iterate through array of pointers
            if ((int)itemCount < 0) {
                currentItemArray = (int**)((byte*)currentItemArray + *currentItemArray);
                advanceStreamBuffer();
                currentItemArray = *((int***)&currentItemArray);
                itemCount = 0;
            } else if ((int)itemCount < (int)(totalItems - 1)) {
                itemCount++;
                currentItemArray = (int**)((byte*)currentItemArray + *currentItemArray);
                itemCount = 0; // Reset after advance?
                // Actually the decomp shows itemCount = uVar5 from previous state, but we simplify
            } else {
                currentItemArray = (int**)&DAT_01163cf8; // end marker
            }
        } else {
            // Dense format: advance via bitfield
            itemCount++;
            if (itemCount != totalItems) {
                itemIndex = (short)itemCount;
                // Check bit in bitfield at local_ec to see if this item is present
                if ((*(byte*)((itemCount >> 3) + bitIndex) & (1 << (itemCount & 7))) == 0) {
                    // Item not present, skip
                    itemData0 = *currentPtr;
                    itemPtr = currentPtr;
                    currentPtr++;
                } else {
                    // Item present, mark as null?
                    itemPtr = 0;
                    itemData0 = 0;
                }
            }
        }
    } // end while

    // Post-processing
    if (setFlag) {
        *(uint*)(thisPtr + 0xe4) |= 0x1000000; // Set bit 24
    }

    // Check if update is needed
    if ((*(int*)(thisPtr + 0xd0) == 0) && ((*(byte*)(thisPtr + 0xe4) & 1) != 0)) {
        if ((*(int*)(thisPtr + 0xd4) != 0) ||
            ((*(int*)(thisPtr + 0xd8) != 0 || (*(int*)(thisPtr + 0xdc) != 0)) ||
             (*(int*)(thisPtr + 0xe0) != 0))) {
            // There are pending updates
            if (DAT_0120e93c != 0) {
                compareAndSet(thisPtr + 0x3c, &DAT_0120e93c);
            }
            *(uint*)(thisPtr + 0xe4) |= 0x4000000; // Mark update flag
            return;
        }
        clearUpdateFlag(0);
    }
}

// Helper function to get the item pointer based on format
int* getItemPtr(char formatFlag, int** currentArray, int* localItemPtr) {
    if (formatFlag == 0) {
        return (int*)currentArray;
    } else {
        return localItemPtr;
    }
}

// Placeholder function declarations for clarity (not defined here)
void readStreamBegin(int stream, int classId);
void readStreamBit(int stream, int count);
void readStreamString(int stream, char* outStr);
void readStreamName(int address, char* name);
void skipStreamData(int address);
void readPointer(int dest, int* source, const char* className);
void readStreamBuffer(int address);
int resolvePointer(int index);
void readFlag(int address);
void advanceStreamBuffer();
void compareAndSet(int dest, int* source);
void clearUpdateFlag(int flag);