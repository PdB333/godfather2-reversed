// FUNC_NAME: DataBlockParser::parseBlockStream
void __thiscall DataBlockParser::parseBlockStream(void* thisObj, undefined4 param2)
{
    // Local variables
    char bUseArray;              // flag: 0 = linked list iteration, 1 = bitmask array iteration
    int arrayBase;               // base of bitmask array
    undefined4* arrayCurrentPtr; // current position in array
    uint arrayIndex;             // current index in array
    uint arrayCount;             // total count in array
    undefined4* currentNode;     // current node from array mode (used as ppuVar10 source)
    uint16_t storeIndexShort;    // temporary short
    undefined4 storeValue;       // temporary value
    undefined4** listNodePtr;    // pointer to current node in linked list mode
    undefined4 nodeData0, nodeData1, nodeData2, nodeData3; // four words from node
    undefined4 tempZero;         // always 0
    uint typeId;                 // type identifier for some operations

    initParser(param2, 0x9c326942);

    do {
        // Check termination condition
        bool bTerminate;
        if (bUseArray == '\0') {
            bTerminate = (*listNodePtr == 0);
        } else {
            bTerminate = (arrayIndex == arrayCount);
        }
        if (bTerminate) {
            return;
        }

        // Determine source of node data (ppuVar10)
        undefined4** ppuVar10 = (bUseArray == '\0') ? listNodePtr : &currentNode;

        // Get the type/command from node
        undefined4* puVar6;
        if (*(int16_t*)((int)ppuVar10 + 6) == 0x25e3) {
            // Node has a short size field after header
            puVar6 = (undefined4*)(uint)*(uint16_t*)(ppuVar10 + 1);
        } else {
            puVar6 = ppuVar10[1];
        }

        if (puVar6 == 0) {
            // Type 0: string data
            // Resolve pointer to actual data
            undefined4** dataPtr;
            if (bUseArray == '\0') {
                dataPtr = listNodePtr;
            } else {
                dataPtr = &currentNode;
            }
            if (*(int16_t*)((int)dataPtr + 6) == 0x25e3) {
                if (*dataPtr == 0) {
                    dataPtr = (undefined4**)&DAT_00e2a89b; // empty string
                } else {
                    dataPtr = (undefined4**)((int)dataPtr[2] + (int)*dataPtr);
                }
            } else {
                dataPtr = dataPtr + 2;
            }

            int* stringBuffer = (int*)(thisObj + 0x50);
            clearStringBuffer(stringBuffer);
            resetStringBuffer(stringBuffer);
            if (dataPtr != 0 && *(char*)dataPtr != '\0') {
                undefined4 strVal = getStringFromData(dataPtr);
                setStringBuffer(stringBuffer, strVal);
                if (*stringBuffer != 0) {
                    addStringToList(thisObj + 0x3c, stringBuffer);
                }
            }
        } else if (puVar6 == 1) {
            // Type 1: similar string data, different buffer offset
            undefined4** dataPtr;
            if (bUseArray == '\0') {
                dataPtr = listNodePtr;
            } else {
                dataPtr = &currentNode;
            }
            if (*(int16_t*)((int)dataPtr + 6) == 0x25e3) {
                if (*dataPtr == 0) {
                    dataPtr = (undefined4**)&DAT_00e2a89b;
                    int* stringBuffer2 = (int*)(thisObj + 0x58);
                } else {
                    dataPtr = (undefined4**)((int)dataPtr[2] + (int)*dataPtr);
                    int* stringBuffer2 = (int*)(thisObj + 0x58);
                }
            } else {
                dataPtr = dataPtr + 2;
                int* stringBuffer2 = (int*)(thisObj + 0x58);
            }
            int* stringBuffer2 = (int*)(thisObj + 0x58);
            clearStringBuffer(stringBuffer2);
            resetStringBuffer(stringBuffer2);
            if (dataPtr != 0 && *(char*)dataPtr != '\0') {
                undefined4 strVal = getStringFromData(dataPtr);
                setStringBuffer(stringBuffer2, strVal);
                if (*stringBuffer2 != 0) {
                    addStringToList(thisObj + 0x3c, stringBuffer2);
                }
            }
        } else if (puVar6 == 0x14) {
            // Type 20: copy 16 bytes to slot (offset +0x60)
            undefined4** dataPtr;
            if (bUseArray == '\0') {
                dataPtr = listNodePtr;
            } else {
                dataPtr = &currentNode;
            }
            if (*(int16_t*)((int)dataPtr + 6) == 0x25e3) {
                if (*dataPtr == 0) {
                    dataPtr = (undefined4**)&DAT_0120e700; // null data
                } else {
                    dataPtr = (undefined4**)((int)dataPtr[2] + (int)*dataPtr);
                }
            } else {
                dataPtr = dataPtr + 2;
            }
            int* slot = (int*)(((int)puVar6 - 0xe) * 0x10 + (int)thisObj);
            slot[0] = (int)*dataPtr;
            slot[1] = (int)dataPtr[1];
            slot[2] = (int)dataPtr[2];
            slot[3] = (int)dataPtr[3];
        } else if ((int)puVar6 - 0x15U < 2) {
            // Types 21,22: copy 16 bytes to slots (offset +0x70 or +0x80)
            undefined4** dataPtr;
            if (bUseArray == '\0') {
                dataPtr = listNodePtr;
            } else {
                dataPtr = &currentNode;
            }
            if (*(int16_t*)((int)dataPtr + 6) == 0x25e3) {
                if (*dataPtr == 0) {
                    dataPtr = (undefined4**)&DAT_0120e700;
                } else {
                    dataPtr = (undefined4**)((int)dataPtr[2] + (int)*dataPtr);
                }
            } else {
                dataPtr = dataPtr + 2;
            }
            int* slot = (int*)(((int)puVar6 - 0xe) * 0x10 + (int)thisObj);
            slot[0] = (int)*dataPtr;
            slot[1] = (int)dataPtr[1];
            slot[2] = (int)dataPtr[2];
            slot[3] = (int)dataPtr[3];
        } else if ((int)puVar6 - 2U < 0x12) {
            // Types 2..19: process block data
            undefined4** dataPtr;
            if (bUseArray == '\0') {
                dataPtr = listNodePtr;
            } else {
                dataPtr = &currentNode;
            }
            if (*(int16_t*)((int)dataPtr + 6) == 0x25e3) {
                if (*dataPtr == 0) {
                    dataPtr = (undefined4**)&DAT_0120e700;
                } else {
                    dataPtr = (undefined4**)((int)dataPtr[2] + (int)*dataPtr);
                }
            } else {
                dataPtr = dataPtr + 2;
            }
            undefined4* p0 = *dataPtr;
            undefined4* p1 = dataPtr[1];
            undefined4* p2 = dataPtr[2];
            undefined4* p3 = dataPtr[3];

            if ((p0 != 0) || (p1 != 0) || (p2 != 0) || (p3 != 0)) {
                bool bAllow = checkAllowDuplicates();
                if (bAllow) {
                    uint uIdx = 0;
                    if (*(uint*)(thisObj + 0x394) != 0) {
                        int* entry = (int*)(thisObj + 0x9c);
                        do {
                            if (((undefined4*)entry[-2] == p0) &&
                                ((undefined4*)entry[-1] == p1) &&
                                ((undefined4*)*entry == p2) &&
                                ((undefined4*)entry[1] == p3)) {
                                goto skip_block;
                            }
                            uIdx++;
                            entry += 6;
                        } while (uIdx < *(uint*)(thisObj + 0x394));
                    }
                }
                if ((p0 != 0) || (p1 != 0) || (p2 != 0) || (p3 != 0)) {
                    tempZero = 0;
                    nodeData0 = p0;
                    nodeData1 = p1;
                    nodeData2 = p2;
                    nodeData3 = p3;
                    typeId = (int)puVar6 - 2;
                    processSubBlock();
                }
            }
        } else if ((int)puVar6 - 0x17U < 0x12) {
            // Types 23..40: update reference array
            undefined4** dataPtr;
            if (bUseArray == '\0') {
                dataPtr = listNodePtr;
            } else {
                dataPtr = &currentNode;
            }
            undefined4* p1 = dataPtr[2];
            uint uIdx = 0;
            if (*(int*)(thisObj + 0x394) != 0) {
                int* entry = (int*)(thisObj + 0xa4);
                do {
                    if ((int)puVar6 - 0x17U == entry[1]) {
                        *entry = (int)p1;
                    }
                    uIdx++;
                    entry += 6;
                } while (uIdx < *(uint*)(thisObj + 0x394));
            }
        }
skip_block:
        // Advance iteration
        if (bUseArray == '\0') {
            // Linked list mode: advance to next node
            if ((int)arrayIndex < 0) {
                listNodePtr = (undefined4**)((int)listNodePtr + (int)*listNodePtr);
                advanceListPointer();
            } else if ((int)arrayIndex < (int)(arrayCount - 1)) {
                arrayIndex++;
                listNodePtr = (undefined4**)((int)listNodePtr + (int)*listNodePtr);
            } else {
                listNodePtr = (undefined4**)&DAT_01163cf8; // end marker
            }
        } else {
            // Array mode: advance index
            arrayIndex++;
            if (arrayIndex != arrayCount) {
                storeIndexShort = (uint16_t)arrayIndex;
                if ((*(byte*)((arrayIndex >> 3) + arrayBase) & (uint8_t)(1 << (arrayIndex & 7))) == 0) {
                    // Bit not set: this entry is present
                    storeValue = *arrayCurrentPtr;
                    currentNode = arrayCurrentPtr;
                    arrayCurrentPtr++;
                } else {
                    // Bit set: this entry is missing
                    currentNode = 0;
                    storeValue = 0;
                }
            }
        }
    } while (true);
}