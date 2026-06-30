// FUNC_NAME: ObjectiveManager::applyObjectivePacket
void __thiscall ObjectiveManager::applyObjectivePacket(void* this, void* dataBuffer)
{
    bool hasUpdated = false;
    bool isArrayFormat;
    char* bitmaskArray;
    undefined4* dataArray;
    uint currentIndex;
    uint totalCount;
    undefined4* entryData;
    short indexShort;
    undefined4 entryType;
    undefined4** currentEntry;

    // Deserialize the incoming data stream
    readStream(dataBuffer, 0xb1079603);

    do {
        if (isArrayFormat == '\0') {
            // Linked list format: check if current entry is null
            hasReachedEnd = *currentEntry == (undefined4*)0x0;
        }
        else {
            // Array format: check if index equals count
            hasReachedEnd = currentIndex == totalCount;
        }

        if (hasReachedEnd) {
            // Check if any objective flags are set and if the objective state is appropriate
            if (((((this->objectiveFlags1 != 0) || (this->objectiveFlags2 != 0)) ||
                 (this->objectiveFlags3 != 0)) || (this->objectiveFlags4 != 0)) &&
               (((this->objectiveState == 0) || (this->objectiveState == 0x48)) &&
                (g_globalObjectiveCondition != 0))) {
                fireEvent(this + 0x3c, &g_globalObjectiveCondition);
            }

            if (!hasUpdated) {
                return;
            }

            // Evaluate result based on current state and thresholds
            if (cleanFloat(this->objectiveProgress) <= g_thresholdLow) {
                if (this->objectiveSuccessFlag != '\0') {
                    this->objectiveResult = 2;
                    return;
                }
                if ((this->objectiveState == 0) || (this->objectiveState == 0x48)) {
                    this->objectiveResult = 0;
                    return;
                }
            }
            else {
                if ((this->objectiveState == 0) || (this->objectiveState == 0x48)) {
                    this->objectiveResult = 3 - (uint)(this->objectiveSuccessFlag != '\0');
                    return;
                }
                if (g_thresholdLow <= cleanFloat(this->objectiveProgress - g_thresholdOffset)) {
                    this->objectiveResult = 3;
                    return;
                }
            }
            this->objectiveResult = 1;
            return;
        }

        // Determine entry data pointer
        if (isArrayFormat == '\0') {
            entryData = (undefined4*)currentEntry;
        }
        else {
            entryData = &entryData; // local_5c is the entry in array format
        }

        // Extract the operation type
        undefined4 operationType;
        if (*(short*)((int)entryData + 6) == 0x25e3) {
            operationType = (undefined4)(uint)*(ushort*)(entryData + 1);
        }
        else {
            operationType = entryData[1];
        }

        switch(operationType) {
        case 0: // Reset objective flags
            clearObjectiveFlags(this + 0x68);
            hasUpdated = true;
            break;

        case 1: // Set objective completion flag
            if (isArrayFormat == '\0') {
                this->objectiveCompleteFlag = (currentEntry[2] != 0);
            }
            else {
                this->objectiveCompleteFlag = (entryData[2] != 0);
            }
            break;

        case 2: // Set objective success flag
            if (isArrayFormat == '\0') {
                this->objectiveSuccessFlag = (currentEntry[2] != 0);
            }
            else {
                this->objectiveSuccessFlag = (entryData[2] != 0);
            }
            hasUpdated = true;
            break;

        case 3: // Set objective progress float
            if (isArrayFormat == '\0') {
                this->objectiveProgress = (float)(uint)currentEntry[2];
            }
            else {
                this->objectiveProgress = (float)(uint)entryData[2];
            }
            hasUpdated = true;
            break;

        case 4: // Set some additional data
            if (isArrayFormat == '\0') {
                this->additionalData = (void*)currentEntry[2];
            }
            else {
                this->additionalData = (void*)entryData[2];
            }
            break;

        case 5: // Set objective description string (linked list variant)
            {
                int* targetString;
                undefined4** stringData;
                if (isArrayFormat == '\0') {
                    if (*(short*)((int)currentEntry + 6) == 0x25e3) {
                        if (*currentEntry == (undefined4*)0x0) {
                            targetString = (int*)(this + 0x58);
                            stringData = (undefined4**)&g_emptyString;
                        }
                        else {
                            stringData = (undefined4**)((int)currentEntry[2] + (int)*currentEntry);
                            targetString = (int*)(this + 0x58);
                        }
                    }
                    else {
                        targetString = (int*)(this + 0x58);
                        stringData = currentEntry + 2;
                    }
                }
                else {
                    // Array format
                    if (*(short*)((int)entryData + 6) == 0x25e3) {
                        if (*(undefined4**)entryData == (undefined4*)0x0) {
                            stringData = (undefined4**)&g_emptyString;
                        }
                        else {
                            stringData = (undefined4**)((int)entryData[2] + (int)*entryData);
                        }
                    }
                    else {
                        stringData = entryData + 2;
                    }
                    targetString = (int*)(this + 0x58);
                }
                goto setAndFireStringEvent;
            }
            break;

        case 6: // Set objective title string
            {
                int* targetString;
                undefined4** stringData;
                if (isArrayFormat == '\0') {
                    if (*(short*)((int)currentEntry + 6) == 0x25e3) {
                        if (*currentEntry == (undefined4*)0x0) {
                            stringData = (undefined4**)&g_emptyString;
                        }
                        else {
                            stringData = (undefined4**)((int)currentEntry[2] + (int)*currentEntry);
                        }
                    }
                    else {
                        stringData = currentEntry + 2;
                    }
                }
                else {
                    if (*(short*)((int)entryData + 6) == 0x25e3) {
                        if (*(undefined4**)entryData == (undefined4*)0x0) {
                            stringData = (undefined4**)&g_emptyString;
                        }
                        else {
                            stringData = (undefined4**)((int)entryData[2] + (int)*entryData);
                        }
                    }
                    else {
                        stringData = entryData + 2;
                    }
                }
                targetString = (int*)(this + 0x50);
                goto setAndFireStringEvent;
            }
            break;

        case 7: // Set objective target name string
            {
                int* targetString;
                undefined4** stringData;
                if (isArrayFormat == '\0') {
                    if (*(short*)((int)currentEntry + 6) == 0x25e3) {
                        if (*currentEntry == (undefined4*)0x0) {
                            targetString = (int*)(this + 0x60);
                            stringData = (undefined4**)&g_emptyString;
                        }
                        else {
                            stringData = (undefined4**)((int)currentEntry[2] + (int)*currentEntry);
                            targetString = (int*)(this + 0x60);
                        }
                    }
                    else {
                        targetString = (int*)(this + 0x60);
                        stringData = currentEntry + 2;
                    }
                }
                else {
                    if (*(short*)((int)entryData + 6) == 0x25e3) {
                        if (*(undefined4**)entryData == (undefined4*)0x0) {
                            targetString = (int*)(this + 0x60);
                            stringData = (undefined4**)&g_emptyString;
                        }
                        else {
                            stringData = (undefined4**)((int)entryData[2] + (int)*entryData);
                            targetString = (int*)(this + 0x60);
                        }
                    }
                    else {
                        targetString = (int*)(this + 0x60);
                        stringData = entryData + 2;
                    }
                }

setAndFireStringEvent:
                freeString(targetString);
                clearString(targetString);
                if ((stringData != (undefined4**)0x0) && (*(char*)stringData != '\0')) {
                    copyString(targetString, stringData);
                    if (*targetString != 0) {
                        fireEvent(this + 0x3c, targetString);
                    }
                }
            }
            break;
        }

        // Advance to next entry in the data stream
        if (isArrayFormat == '\0') {
            // Linked list: each entry has a size field at the start
            if ((int)currentIndex < 0) {
                currentEntry = (undefined4**)((int)currentEntry + (int)*currentEntry);
                advanceLinkedList();
            }
            else if ((int)currentIndex < (int)(totalCount - 1)) {
                currentIndex = currentIndex + 1;
                currentEntry = (undefined4**)((int)currentEntry + (int)*currentEntry);
            }
            else {
                currentEntry = (undefined4**)&g_endOfListSentinel; // DAT_01163cf8 likely a sentinel
            }
        }
        else {
            // Array with bitmask: read next entry based on bitmask
            currentIndex = currentIndex + 1;
            if (currentIndex != totalCount) {
                indexShort = (short)currentIndex;
                if ((*(byte*)((currentIndex >> 3) + bitmaskArray) & (byte)(1 << ((byte)currentIndex & 7))) == 0) {
                    // Entry is present
                    entryType = *dataArray;
                    entryData = dataArray;
                    dataArray = dataArray + 1;
                }
                else {
                    // Entry skipped
                    entryData = (undefined4*)0x0;
                    entryType = 0;
                }
            }
        }
    } while(true);
}