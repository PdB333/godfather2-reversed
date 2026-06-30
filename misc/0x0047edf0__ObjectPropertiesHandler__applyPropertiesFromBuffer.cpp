// FUNC_NAME: ObjectPropertiesHandler::applyPropertiesFromBuffer
void __thiscall ObjectPropertiesHandler::applyPropertiesFromBuffer(int thisObj, void* dataBuffer)
{
    // +0x3c: string buffer property A
    // +0x50: string buffer property B
    // +0x58: string buffer property C
    // +0x60: property list state
    // +0x78: bool flag D
    // +0x79: bool flag E

    // Begin reading properties with a specific format hash
    beginReadProperties(dataBuffer, 0x48af91a8); // FUN_0043aff0

    uint* currentPtr; // ppuVar3 - iteration pointer for flat mode
    bool bIsCompact;  // local_64 - true if using bitmask representation
    int bitmaskArray;   // local_60 - pointer to bitmask bytes (compact mode)
    uint* elementArray; // local_5c - pointer to element array (compact mode)
    uint currentIndex;  // local_58 - current element index (compact mode)
    uint totalElements; // local_54 - total element count (compact mode)
    void* currentElement; // local_50 - current element being processed
    short elementTag;     // local_4c - used for element tag check
    int elementValue;     // local_48 - extra value from element

    currentPtr = (uint*)dataBuffer; // initial pointer for flat mode (from initial call?)

    do {
        // Check termination condition
        bool bTerminate;
        if (bIsCompact) {
            bTerminate = (currentIndex == totalElements);
        } else {
            bTerminate = (*currentPtr == 0);
        }
        if (bTerminate) {
            return;
        }

        void** elementPtr; // ppuVar4 - pointer to the element to process
        if (bIsCompact) {
            elementPtr = &currentElement;
        } else {
            elementPtr = (void**)currentPtr;
        }

        // Determine the type tag of this element
        void* typeTag;
        if (*(short*)((int)elementPtr + 6) == 0x25e3) {
            // Element has a short tag at offset 6 (0x25e3 magic)
            typeTag = (void*)(uint)*(ushort*)(elementPtr + 1);
        } else {
            typeTag = elementPtr[1];
        }

        // Process element by type tag
        switch ((int)typeTag) {
            case 0: // Type 0: apply to property at +0x50
            {
                void** srcPtr;
                if (bIsCompact) {
                    srcPtr = &currentElement;
                } else {
                    srcPtr = (void**)currentPtr;
                }
                if (*(short*)((int)srcPtr + 6) == 0x25e3) {
                    if (*srcPtr == 0) {
                        srcPtr = (void**)&DAT_00e2a89b; // some default
                    } else {
                        srcPtr = (void**)((int)srcPtr[2] + (int)*srcPtr);
                    }
                } else {
                    srcPtr = srcPtr + 2;
                }
                int* propBuffer = (int*)(thisObj + 0x50);
                goto applyStringProperty;
            }
            case 1: // Type 1: apply to property at +0x58
            {
                void** srcPtr;
                if (bIsCompact) {
                    srcPtr = &currentElement;
                } else {
                    srcPtr = (void**)currentPtr;
                }
                if (*(short*)((int)srcPtr + 6) == 0x25e3) {
                    if (*srcPtr == 0) {
                        srcPtr = (void**)&DAT_00e2a89b;
                        int* propBuffer = (int*)(thisObj + 0x58);
                    } else {
                        srcPtr = (void**)((int)srcPtr[2] + (int)*srcPtr);
                        int* propBuffer = (int*)(thisObj + 0x58);
                    }
                } else {
                    srcPtr = srcPtr + 2;
                    int* propBuffer = (int*)(thisObj + 0x58);
                }
applyStringProperty:
                clearStringBuffer(propBuffer); // FUN_004086d0
                freeStringBuffer(propBuffer);  // FUN_00408310
                if (srcPtr != 0 && *(char*)srcPtr != '\0') {
                    int result = readStringFromBuffer(srcPtr); // FUN_004dafd0
                    setString(propBuffer, result); // FUN_00408260
                    if (*propBuffer != 0) {
                        // Apply the string to the object's property at +0x3c
                        applyStringToObject(thisObj + 0x3c, propBuffer); // FUN_00407e60
                    }
                }
                break;
            }
            case 2: // Type 2: reset property list at +0x60
                clearProperties(thisObj + 0x60); // FUN_0043ad10
                currentPtr = (uint*)dataBuffer; // reset pointer? (appears to reinitialize from original)
                break;
            case 3: // Type 3: set boolean flag at +0x78
            {
                void** srcPtr;
                if (bIsCompact) {
                    srcPtr = &currentElement;
                } else {
                    srcPtr = (void**)currentPtr;
                }
                *(bool*)(thisObj + 0x78) = (srcPtr[2] != 0);
                break;
            }
            case 4: // Type 4: set boolean flag at +0x79
            {
                void** srcPtr;
                if (bIsCompact) {
                    srcPtr = &currentElement;
                } else {
                    srcPtr = (void**)currentPtr;
                }
                *(bool*)(thisObj + 0x79) = (*(char*)(srcPtr + 2) != '\0');
                break;
            }
        }

        // Advance to next element
        if (bIsCompact) {
            currentIndex++;
            if (currentIndex != totalElements) {
                // Read next element using bitmask
                short index = (short)currentIndex;
                if ((*(byte*)(bitmaskArray + (currentIndex >> 3)) & (1 << (currentIndex & 7))) == 0) {
                    // Element present
                    elementValue = *elementArray;
                    currentElement = elementArray;
                    elementArray++;
                } else {
                    // Element skipped
                    currentElement = 0;
                    elementValue = 0;
                }
            }
        } else {
            // Flat mode: advance pointer
            if ((int)currentIndex < 0) {
                // Negative index: use a different base (DAT_00e2a89b?)
                currentPtr = (uint*)((int)currentPtr + (int)*currentPtr);
                advanceToNextBlock(); // FUN_0043b140
                currentPtr = (uint*)dataBuffer; //? unclear
            } else if ((int)currentIndex < (int)(totalElements - 1)) {
                currentIndex++;
                currentPtr = (uint*)((int)currentPtr + (int)*currentPtr);
                // ppuVar3 also updated?
            } else {
                currentPtr = (uint*)&DAT_01163cf8; // sentinel
            }
        }
    } while (true);
}