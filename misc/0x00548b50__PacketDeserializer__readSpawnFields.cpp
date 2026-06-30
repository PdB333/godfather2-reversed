// FUNC_NAME: PacketDeserializer::readSpawnFields
// Address: 0x00548b50
// This function deserializes a stream of item entries into a spawn data structure at this+0x8..0x2C.
// It supports two modes: linked list (mode==0) and bitmask-compacted array (mode!=0).
// The stream is initialized by FUN_0043aff0 with a hash key 0x6173a1d6.
// The global variable DAT_00e2b1a4 is used for case 4's extra field (likely a timestamp or instance counter).
// DAT_01163cf8 is a sentinel node for end-of-list.

void __thiscall PacketDeserializer::readSpawnFields(int this, int streamContext) { // this is unaff_EDI
    int fieldId;
    int *itemData;
    int *tempPtr;
    int *entryPtr;
    unsigned int currentIndex;
    unsigned int count;
    char modeFlag; // local_64: 0=linked list, 1=bitmask array
    int *bitmaskArray; // local_60: points to bitmask data in array mode
    int *dataPointer; // local_5c: current data pointer in array mode
    unsigned int index; // local_58: current item index
    unsigned int totalItems; // local_54: total number of items per header
    int *currentNode; // local_8: current linked list node
    int *currentItem; // local_50: current item descriptor
    int unusedData; // local_48: unused, used for alignment
    short rawIndex; // local_4c: index cast to short

    // Initialize stream reader with a magic hash
    FUN_0043aff0(streamContext, 0x6173a1d6);

    index = currentIndex; // local_58
    int globalValue = DAT_00e2b1a4; // uVar6

    while (true) {
        if (modeFlag == '\0') {
            // Linked list mode: check if current node is null
            if (*currentNode == 0) break;
        } else {
            // Array mode: check if index == totalItems
            if (index == totalItems) break;
        }

        // Determine which pointer holds the item descriptor
        if (modeFlag == '\0') {
            entryPtr = currentNode; // linked list node itself holds item data
        } else {
            entryPtr = &currentItem; // array entry
        }

        // Extract field ID from the item descriptor
        // If the descriptor's short at offset 6 equals 0x25e3 (magic flag for compact format),
        // then fieldId is read from the ushort at offset 4 (as pointer-casted), otherwise it's the int at offset 4.
        if (*(short *)((int)entryPtr + 6) == 0x25e3) {
            fieldId = (int)(unsigned short)*(short *)((int)entryPtr + 4); // cast to unsigned short then int
        } else {
            fieldId = (int)entryPtr[1]; // second int in descriptor (offset 4)
        }

        // Dispatch based on fieldId (0-4) to write into this+offsets
        switch (fieldId) {
            case 0:
                *(int **)(this + 0x8) = (int *)entryPtr[2]; // offset 0x8
                break;
            case 1:
                *(int **)(this + 0xC) = (int *)entryPtr[2]; // offset 0xC
                break;
            case 2:
                *(int **)(this + 0x10) = (int *)entryPtr[2]; // offset 0x10
                break;
            case 3:
                *(int **)(this + 0x14) = (int *)entryPtr[2]; // offset 0x14
                break;
            case 4:
                // Read three consecutive values starting from entryPtr[0..2] (or adjusted for compact)
                if (*(short *)((int)entryPtr + 6) == 0x25e3) {
                    // Compact format: entryPtr[0] is a base pointer, entryPtr[2] is an offset?
                    if (*entryPtr == 0) {
                        tempPtr = (int *)&DAT_00e2e5d0; // fallback global
                    } else {
                        tempPtr = (int *)((int)entryPtr[2] + (int)*entryPtr);
                    }
                } else {
                    tempPtr = entryPtr + 2; // normal: skip first two ints, pointer to first value
                }
                // Write three ints (likely position x,y,z) and one extra global value
                *(int **)(this + 0x20) = (int *)tempPtr[0]; // offset 0x20 (x)
                *(int **)(this + 0x24) = (int *)tempPtr[1]; // offset 0x24 (y)
                *(int **)(this + 0x28) = (int *)tempPtr[2]; // offset 0x28 (z)
                *(int *)(this + 0x2C) = globalValue; // offset 0x2C (extra int, e.g., timestamp)
                break;
        }

        // Advance to next item
        if (modeFlag == '\0') {
            // Linked list: each node includes a size field at offset 0; advance by that size.
            if ((int)index < 0) {
                currentNode = (int *)((int)currentNode + (int)*currentNode); // move to next node
                FUN_0043b140(); // likely decrement reference or clean up
                index = currentIndex; // reload? possibly resets index
            } else if ((int)index < (int)(totalItems - 1)) {
                currentNode = (int *)((int)currentNode + (int)*currentNode);
                currentIndex = index + 1;
                index = currentIndex;
            } else {
                // End of list: set sentinel
                currentNode = (int *)&DAT_01163cf8;
            }
        } else {
            // Array mode: increment index, read next item if exists
            currentIndex = index + 1;
            index = currentIndex;
            if (currentIndex != totalItems) {
                rawIndex = (short)currentIndex; // cast to short for bitmask check
                // Check if bit at position currentIndex in bitmaskArray is set (1 = present, 0 = absent)
                if ((*(unsigned char *)((currentIndex >> 3) + (int)bitmaskArray) & (1 << (currentIndex & 7))) == 0) {
                    // Entry absent: skip, set currentItem to data pointer and advance
                    unusedData = *dataPointer; // might be tag or size
                    currentItem = dataPointer;
                    dataPointer++;
                } else {
                    // Entry present: null pointer indicates missing data?
                    currentItem = 0;
                    unusedData = 0;
                }
            }
        }
    }
}