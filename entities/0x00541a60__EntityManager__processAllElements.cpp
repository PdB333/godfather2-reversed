// FUNC_NAME: EntityManager::processAllElements
// Function at 0x00541a60: Iterates over a collection (linked list or bitfield-packed array) 
// and for each element, if its second field is null, stores the third field into this+0x180.
// Then calls a virtual function (offset 4) from a vtable at this+0x190.
// Expected to be a method of a manager class that processes a set of objects.

void __thiscall EntityManager::processAllElements(void* thisPtr, void* iteratorContext) {
    // Iterator initialization with a constant token (likely a type identifier)
    iteratorBegin(iteratorContext, 0x4f3368d0);

    // Local variables for two iteration modes:
    // - bVar5: loop continuation condition
    // - uVar4: current index (for array mode)
    // - local_64: mode flag (0 = linked list, 1 = bitfield-packed array)
    // - local_54: total count (array mode)
    // - local_58: current index (array mode)
    // - local_5c: pointer to data array (array mode)
    // - local_60: pointer to bitfield byte array (array mode)
    // - local_50: current element pointer (array mode)
    // - local_48: current element value (array mode)
    // - local_4c: short storage for array mode
    // - local_8: current node pointer (linked list mode)

    // The decompiled code shows a while(true) with two different iteration strategies
    // selected by the flag at local_64.
    // The iteration variables are manipulated inside the loop.

    // Start of iteration (initialized by iteratorBegin?)
    void** currentNodePtr = iteratorContext->someField; // local_8
    uint currentIndex = 0; // local_58
    uint maxCount = 10; // local_54 (actual value comes from iterator)
    bool isLinkedList = true; // local_64 (assumed from initialization)

    // For array mode:
    uint dataEntrySize = 12; // example size
    char* bitfieldBase = 0;
    uint* dataArray = 0;

    while (true) {
        bool loopCond;
        if (isLinkedList) {
            loopCond = (*currentNodePtr == 0);
        } else {
            loopCond = (currentIndex == maxCount);
        }
        if (loopCond) break;

        // Determine which pointer to use for reading element fields
        void** elementSlot;
        if (isLinkedList) {
            elementSlot = currentNodePtr;
        } else {
            elementSlot = &local_50 intrinsic; // points to local_50 in array mode
        }

        // Read a tag from offset 6 of the element slot
        short nodeTag = *(short*)((char*)elementSlot + 6);
        void* elementPtr;
        if (nodeTag == 0x25e3) {
            // If tag matches, interpret next field as a short index
            elementPtr = (void*)(uint)*(unsigned short*)((char*)elementSlot + 4);
        } else {
            // Otherwise read as a full pointer
            elementPtr = elementSlot[1];
        }

        // If the element's second field is null, store the third field into this+0x180
        if (elementPtr == 0) {
            void* thirdField;
            if (isLinkedList) {
                thirdField = currentNodePtr[2];
            } else {
                // In array mode, elementSlot points to local_50, so elementSlot[2] is local_50+8? Actually need careful.
                // From decomp: ppuVar3[2] is written. ppuVar3 is either &local_50 or ppuVar1.
                // In linked list mode, ppuVar3 = currentNodePtr, so ppuVar3[2] = currentNodePtr[2].
                // In array mode, ppuVar3 = &local_50, so ppuVar3[2] = local_50+8? Actually local_50 is a pointer, so &local_50[2] is the third element of the data entry.
                // Assuming data entry has three fields: first is pointer, second we read as elementPtr, third is data.
                thirdField = ((void**)elementSlot)[2];
            }
            *(void**)((char*)thisPtr + 0x180) = thirdField;
        }

        // Advance iteration
        if (isLinkedList) {
            if ((int)currentIndex < 0) {
                // This path likely iterates through linked list by following offsets
                currentNodePtr = (void**)((char*)currentNodePtr + (int)(*currentNodePtr));
                // iteratorUpdate? called
                iteratorUpdate();
                // currentIndex remains? Actually from decomp: local_58 is updated? In this branch, uVar4 is checked but not updated? The decomp is messy.
                // For simplicity, we assume linked list advances by following next pointer.
                // currentNodePtr = (void**)*currentNodePtr; // or similar.
            } else if ((int)currentIndex < (int)(maxCount - 1)) {
                ++currentIndex;
                // currentNodePtr advances by offset stored in *currentNodePtr
                currentNodePtr = (void**)((char*)currentNodePtr + (int)(*currentNodePtr));
            } else {
                // End of list, set to a sentinel value
                currentNodePtr = (void**)0x01163cf8; // sentinel
            }
        } else {
            // Array mode: advance index
            ++currentIndex;
            if (currentIndex != maxCount) {
                // Use bitfield to check if slot is occupied
                if ( (*(unsigned char*)(bitfieldBase + (currentIndex >> 3)) & (1 << (currentIndex & 7))) == 0 ) {
                    // Slot occupied, read from data array and advance
                    local_50 = (void*)dataArray;
                    local_48 = *dataArray;
                    dataArray++;
                } else {
                    // Slot empty, set local_50 to null
                    local_50 = 0;
                    local_48 = 0;
                }
                // local_4c = (short)currentIndex; // not used in condition
            }
        }
    }

    // Iterator destruction
    iteratorEnd(iteratorContext);

    // Call virtual function at offset 4 from a vtable pointer stored at this+0x190
    void** vtable = *(void***)((char*)thisPtr + 0x190);
    ((void (*)(void*))(vtable[1]))(iteratorContext);
}