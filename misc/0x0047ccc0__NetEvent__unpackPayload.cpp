// FUNC_NAME: NetEvent::unpackPayload
void __thiscall NetEvent::unpackPayload(int thisPtr, int bitStream) {
    int fieldSelector;
    int *ptrA;
    int *ptrB;
    int *unkPtr;
    int localInt0;
    int localInt1;
    int localInt2;
    int localInt3;
    int localInt4;
    int localInt5;
    int localInt6;
    int localInt7;
    char hasMore;
    int basePtr;
    int *fieldArray;
    uint fieldIndex;
    uint fieldCount;
    int *currentField;
    uint magicFieldSize;
    int localStruct[4]; // replaced local_98/94/90/8c
    int localStruct2[4]; // replaced local_88/84/80/7c
    int *localAPtr;
    int *localBPtr;
    int *localCPtr = nullptr;

    // Initialize bitstream reader with a key
    readStreamInit(bitStream, 0xb390b11a);
    readFlag(1);

    // Check if stream is valid? This logic is odd; likely checks for empty buffer
    if (hasMore == 0) {
        fieldArray = localStruct; // actually local_1c is used, but here we simplify
    } else {
        fieldArray = (int*)&fieldCount;
    }
    bool streamEmpty;
    if (hasMore == 0) {
        streamEmpty = (fieldArray[0] == 0);
    } else {
        streamEmpty = (fieldCount == magicFieldSize);
    }
    if (!streamEmpty) {
        clearStruct(thisPtr + 0x80);
    }

    // Initialize local arrays with magic constants (likely default vector values)
    localStruct[0] = -0x153ea5ab; // 0xEAC15A55
    localStruct[1] = -0x153ea5ab;
    localStruct[2] = -0x45245246; // 0xBADBBDBA
    localStruct[3] = -0x41104111; // 0xBEEFBEEF
    localStruct2[0] = -0x45245246;
    localStruct2[1] = -0x41104111;
    localStruct2[2] = -0x6eeff6ef; // 0x91100911
    localStruct2[3] = -0x6eeff6ef;
    localAPtr = nullptr;
    localBPtr = nullptr;
    bool hasSetOffset = false;

    // Mark beginning of data read
    readStreamInit(bitStream, 0xb1a6d45b);

    // Loop over fields
    while (true) {
        if (hasMore == 0) {
            streamEmpty = (fieldArray[0] == 0);
        } else {
            streamEmpty = (fieldCount == magicFieldSize);
        }
        if (streamEmpty) break;

        currentField = &localInt3; // pointer to temporary field descriptor
        if (hasMore == 0) {
            currentField = fieldArray;
        }

        // Read field type or data based on a magic marker
        fieldSelector = (*(short*)((int)currentField + 6) == 0x25e3) ? (uint)*(ushort*)(currentField + 1) : (int)currentField[1];

        switch (fieldSelector) {
            case 0: // field type 0: set offset
                if (hasMore == 0) currentField = fieldArray;
                *(int**)(thisPtr + 0xe4) = (int*)currentField[2];
                break;
            case 1: // field type 1: read base pointer 1
                if (hasMore == 0) currentField = fieldArray;
                if (*(short*)((int)currentField + 6) == 0x25e3) {
                    currentField = (currentField[0] == 0) ? (int*)&DAT_00e2a89b : (int*)((int)currentField[2] + (int)currentField[0]);
                } else {
                    currentField = currentField + 2;
                }
                readPointerMessageData(thisPtr + 0x54, currentField, "BasePtrMsgData*");
                break;
            case 2: // field type 2: read base pointer 2
                if (hasMore == 0) currentField = fieldArray;
                if (*(short*)((int)currentField + 6) == 0x25e3) {
                    currentField = (currentField[0] == 0) ? (int*)&DAT_00e2a89b : (int*)((int)currentField[2] + (int)currentField[0]);
                } else {
                    currentField = currentField + 2;
                }
                readPointerMessageData(thisPtr + 0x5c, currentField, "BasePtrMsgData*");
                break;
            case 3: // field type 3: read first struct
                readStructFromStream(&localStruct);
                fieldArray = (int*)localStruct; // actually local_1c, but we track with hasMore
                if (localStruct[0] != 0 || localStruct[1] != 0 || localStruct[2] != 0 || localStruct[3] != 0) {
                    localAPtr = localStruct;
                }
                break;
            case 4: // field type 4: read second struct
                readStructFromStream(&localStruct2);
                fieldArray = (int*)localStruct2;
                if (localStruct2[0] != 0 || localStruct2[1] != 0 || localStruct2[2] != 0 || localStruct2[3] != 0) {
                    localBPtr = localStruct2;
                }
                break;
            case 5: // field type 5: read something into this+0xc4
                readStructFromStream(thisPtr + 0xc4);
                fieldArray = (int*)localStruct; // update for loop iteration
                break;
            case 6: // field type 6: read base pointer 3 (at offset 100)
                if (hasMore == 0) currentField = fieldArray;
                if (*(short*)((int)currentField + 6) == 0x25e3) {
                    currentField = (currentField[0] == 0) ? (int*)&DAT_00e2a89b : (int*)((int)currentField[2] + (int)currentField[0]);
                } else {
                    currentField = currentField + 2;
                }
                readPointerMessageData(thisPtr + 100, currentField, "BasePtrMsgData*");
                break;
            case 7: // field type 7: read pointer into localCPtr
                if (hasMore == 0) currentField = fieldArray;
                localCPtr = (int*)currentField[2];
                break;
            case 8: // field type 8: set thisField to pointer or fallback
                if (hasMore == 0) currentField = fieldArray;
                int* address = (int*)currentField[2];
                *(int**)(thisPtr + 0xc0) = address;
                if (address == nullptr) {
                    *(int*)(thisPtr + 0xc0) = DAT_0110ac04; // global default
                } else {
                    hasSetOffset = true;
                }
                break;
        }

        // Advance to next field in the stream
        if (hasMore == 0) {
            if ((int)fieldIndex < 0) {
                fieldArray = (int**)((int)fieldArray + (int)*fieldArray);
                advanceStream();
                fieldArray = (int*)fieldArray;
            } else if ((int)fieldIndex < (int)(fieldCount - 1)) {
                fieldArray = (int**)((int)fieldArray + (int)*fieldArray);
                fieldIndex++;
                fieldArray = (int*)((int)fieldArray + (int)*fieldArray);
            } else {
                fieldArray = (int*)&DAT_01163cf8;
            }
        } else {
            fieldIndex++;
            if (fieldIndex != fieldCount) {
                magicFieldSize = (ushort)fieldIndex; // local_60 = short of fieldIndex
                if ((*(byte*)((fieldIndex >> 3) + basePtr) & (1 << (fieldIndex & 7))) == 0) {
                    // Field is present
                    localInt3 = (int)fieldArray;
                    localInt4 = *fieldArray;
                    fieldArray++;
                } else {
                    localInt3 = 0;
                    localInt4 = 0;
                }
            }
        }
    }

    // If we didn't set a custom pointer, use default from localCPtr
    if (!hasSetOffset) {
        int defaultPtr = callFunctionAt_0110ac0c(localCPtr); // some function pointer
        *(int*)(thisPtr + 0xc0) = defaultPtr;
    }

    // Copy struct data if available (prefer localAPtr over localBPtr)
    if (localBPtr == nullptr) {
        if (localAPtr == nullptr) goto LABEL_end;
    } else if (localAPtr == nullptr) {
        *(int*)(thisPtr + 0x6c) = localBPtr[0];
        *(int*)(thisPtr + 0x70) = localBPtr[1];
        *(int*)(thisPtr + 0x74) = localBPtr[2];
        *(int*)(thisPtr + 0x78) = localBPtr[3];
        goto LABEL_end;
    }
    // localAPtr takes priority
    *(int*)(thisPtr + 0x6c) = localAPtr[0];
    *(int*)(thisPtr + 0x70) = localAPtr[1];
    *(int*)(thisPtr + 0x74) = localAPtr[2];
    *(int*)(thisPtr + 0x78) = localAPtr[3];

LABEL_end:
    // Check if any conditions trigger a world interaction (likely a notification)
    if ((((*(int*)(thisPtr + 0xc4) != 0) || (*(int*)(thisPtr + 200) != 0)) ||
         (*(int*)(thisPtr + 0xcc) != 0)) ||
        ((*(int*)(thisPtr + 0xd0) != 0 || ((*(byte*)(thisPtr + 0xe4) & 1) != 0)))) {
        if (DAT_0120e93c != 0) {
            sendNotification(thisPtr + 0x3c, &DAT_0120e93c);
        }
    }
}