// FUNC_NAME: ConfigParser::loadItemSlots
void __thiscall ConfigParser::loadItemSlots(int thisPtr) {
    // 0xd891b9ac is likely a hash or identifier for the data block
    initParseContext(0xd891b9ac); // FUN_0043aff0

    bool isSparse = local_64;       // false for linked list, true for sparse bitfield
    uint totalCount = local_54;     // number of items
    uint currentIndex = local_58;   // current position
    int bitfieldBase = local_60;    // pointer to bitfield byte array (for sparse)
    uint* dataPtr = local_5c;       // pointer to data entries (for sparse)
    ItemNode* currentNode = local_8; // linked list node pointer
    ItemNode currentItem;           // local_50, current item data

    while (true) {
        bool done;
        if (!isSparse) {
            done = (*currentNode == nullptr);
        } else {
            done = (currentIndex == totalCount);
        }
        if (done) break;

        ItemNode** ppNode;
        if (!isSparse) {
            ppNode = &currentNode;
        } else {
            ppNode = (ItemNode**)&currentItem;
        }

        // Check type field at offset +6 (short)
        void* value;
        if (*(short*)((int)ppNode + 6) == 0x25e3) {
            // Type is 0x25e3, interpret as ushort index (slot number)
            value = (void*)(uint)*(ushort*)(ppNode + 1);
        } else {
            value = ppNode[1]; // pointer at +4
        }

        // Store slot pointers based on value (0,1,2)
        if (value == nullptr) {
            *((void**)(thisPtr + 0x8)) = ppNode[2]; // slot0
        } else if (value == (void*)0x1) {
            *((void**)(thisPtr + 0xC)) = ppNode[2]; // slot1
        } else if (value == (void*)0x2) {
            *((void**)(thisPtr + 0x10)) = ppNode[2]; // slot2
        }

        // Advance to next item
        if (!isSparse) {
            // Linked list traversal: next node = (current + *current)
            int* nodePtr = (int*)currentNode;
            if ((int)currentIndex < 0) {
                currentNode = (ItemNode**)((int)currentNode + *nodePtr); // negative case (initial?)
                iterateList(); // FUN_0043b140
                currentIndex = local_58; // reload
            } else if ((int)currentIndex < (int)(totalCount - 1)) {
                currentNode = (ItemNode**)((int)currentNode + *nodePtr);
                currentIndex++;
            } else {
                currentNode = (ItemNode**)0x01163cf8; // sentinel global
            }
        } else {
            // Sparse bitfield iteration
            currentIndex++;
            if (currentIndex != totalCount) {
                // Check if this index is present in bitfield
                uint byteOffset = currentIndex >> 3;
                uint bitMask = 1 << (currentIndex & 7);
                if (!(*(byte*)(byteOffset + bitfieldBase) & bitMask)) {
                    // Present: read from data buffer
                    currentItem = (ItemNode)*dataPtr;
                    local_48 = *dataPtr; // unused?
                    dataPtr++;
                } else {
                    // Not present: mark as null
                    currentItem = (ItemNode)0;
                    local_48 = 0;
                }
            }
        }
    }
}