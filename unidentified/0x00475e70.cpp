// FUN_00475e70: ConfigParser::parseConfig

void __thiscall ConfigParser::parseConfig(void* thisPtr, const char* dataBuffer) {
    int* piVar1;
    int stringResult;
    void** itemPtr;
    void** listEnd;
    bool conditionFlag;
    char iteratorMode;                      // local_64: 0 = null-terminated list, 1 = compact bit-vector
    int bitfieldBase;                       // local_60: base for bitfield indexing
    void** nullTermListCursor;              // local_5c: pointer for null-terminated mode
    int currentIndex;                       // local_58: current index in compact mode
    int totalCount;                         // local_54: total items in compact mode
    void* currentNode;                      // local_50: current node/item
    unsigned short shortIndex;              // local_4c: compact mode index cast to short
    int nodeType;                           // local_48: type ID of current node
    void** iteratorPtr;                     // local_8: main iterator

    // Initialize parser state: find a specific section identified by hash 0x87e3d6e
    findSection(dataBuffer, 0x87e3d6e);
    iteratorPtr = listEnd;
    
    // Main iteration loop
    while (true) {
        // Determine if there are more items to process
        if (iteratorMode == '\0') {
            conditionFlag = (*iteratorPtr == nullptr);
        } else {
            conditionFlag = (currentIndex == totalCount);
        }
        if (conditionFlag) break;

        // Select the current node pointer based on mode
        void** nodePtr = &currentNode;
        if (iteratorMode == '\0') {
            nodePtr = iteratorPtr;
        }

        // Extract type ID from node
        int typeId;
        if (*(short*)((int)nodePtr + 6) == 0x25e3) {
            // Short type encoding: type is stored as unsigned short after a short
            typeId = (int)*(unsigned short*)(nodePtr + 1);
        } else {
            // Normal encoding: type is a pointer-sized field
            typeId = (int)nodePtr[1];
        }

        // Handle type-based actions
        if (typeId - 1 < 8) {                       // Types 1..8
            processTypeHandler(thisPtr + 0x58 + (typeId - 1) * 0x10);
            iteratorPtr = listEnd;                  // Reset iterator? Might be needed after processing
        } else if (typeId == 0) {                    // Type 0: string assignment to a list
            // Determine target string pointer
            void** sourceNode;
            if (iteratorMode == '\0') {
                sourceNode = iteratorPtr;
            } else {
                sourceNode = &currentNode;
            }
            if (*(short*)((int)sourceNode + 6) == 0x25e3) {
                if (*sourceNode == nullptr) {
                    sourceNode = (void**)&globalDefaultString;
                } else {
                    sourceNode = (void**)((int)sourceNode[2] + (int)*sourceNode);
                }
            } else {
                sourceNode = sourceNode + 2;
            }

            // Operate on list at offset +0x50
            piVar1 = (int*)(thisPtr + 0x50);
            listClear(piVar1);
            listInit(piVar1);
            if (sourceNode != nullptr && **(char**)sourceNode != '\0') {
                stringResult = stringToUnicode(sourceNode);
                listAddItem(piVar1, stringResult);
                if (*piVar1 != 0) {
                    callbackFunction(thisPtr + 0x3c, piVar1);
                }
            }
        } else if (typeId == 9) {                     // Type 9: store pointer to offset +0xd8
            // Select current node in compact mode
            void** targetNode;
            if (iteratorMode == '\0') {
                targetNode = iteratorPtr;
            } else {
                targetNode = &currentNode;
            }
            *(void**)(thisPtr + 0xd8) = targetNode[2];
        }

        // Advance to next item
        if (iteratorMode == '\0') {
            // Null-terminated list: linked list using a pointer chain
            if ((int)currentIndex < 0) {                // Emulate decompiler's sign check (likely always false)
                iteratorPtr = (void**)((int)iteratorPtr + (int)*iteratorPtr);
                advanceNullTerminated();
                iteratorPtr = listEnd;
            } else if ((int)currentIndex < (int)(totalCount - 1)) {
                currentIndex = currentIndex + 1;
                iteratorPtr = (void**)((int)iteratorPtr + (int)*iteratorPtr);
                // Advance to next element in the list
            } else {
                iteratorPtr = (void**)&globalSentinel;
            }
        } else {
            // Compact bit-vector mode: indexed access with a bitmask
            currentIndex = currentIndex + 1;
            if (currentIndex != totalCount) {
                shortIndex = (unsigned short)currentIndex;
                // Check if current index is present in bitfield
                if ((*(byte*)(bitfieldBase + (currentIndex >> 3)) & (byte)(1 << (currentIndex & 7))) == 0) {
                    // Missing -> skip this index
                    currentNode = *nullTermListCursor;
                    nullTermListCursor = nullTermListCursor + 1;
                } else {
                    currentNode = nullptr;
                    nodeType = 0;
                }
            }
        }
    }
}