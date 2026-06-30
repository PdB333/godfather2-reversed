// FUNC_NAME: Entity::findComponentByTypeIdAndStoreNextPointer
// Address: 0x005489d0
// This function iterates over either a linked list (mode 0) or a fixed array with a bitmask (mode 1),
// searching for a component whose typeId is 0x25e3. When found, it stores the component's "next" field
// (offset 8) into the object's member at +0x370.
// The iteration mode and data are set up by the caller via local variables.

void Entity::findComponentByTypeIdAndStoreNextPointer()
{
    // Initial hash/check; likely asserts or locks
    FUN_0043aff0(/*some register*/ , 0x34f699a5);

    uint currentIndex = local_58; // for array mode or list index
    while (true) {
        // Exit condition depends on iteration mode
        bool shouldExit;
        if (local_64 == 0) {
            shouldExit = (*local_8 == nullptr);
        } else {
            shouldExit = (currentIndex == local_54);
        }
        if (shouldExit) break;

        // Pointer to current element: for list mode, it's the node pointer; for array mode, it's &local_50
        void* currentElement = (local_64 == 0) ? (void*)*local_8 : (void*)&local_50;

        // Check type field at offset 6
        if (*(short*)((intptr_t)currentElement + 6) == 0x25e3) {
            // Type matches: read 2-byte value at offset 4 (some ID or offset)
            puVar1 = (void*)(uint)(*(unsigned short*)((char*)currentElement + 4));
        } else {
            // Type mismatch: read pointer at offset 4
            puVar1 = *(void**)((char*)currentElement + 4);
        }

        // If puVar1 is null, store the "next" field (offset 8) into this+0x370
        if (puVar1 == nullptr) {
            void* elementForStore = (local_64 == 0) ? (void*)*local_8 : (void*)&local_50;
            *(void**)(this + 0x370) = *(void**)((char*)elementForStore + 8);
        }

        // Advance iteration
        if (local_64 == 0) {
            // Linked list mode: nodes have relative offset at offset 0
            if ((int)currentIndex < 0) {
                // Negative index case: follow relative offset (possible sentinel)
                local_8 = (void**)((intptr_t)local_8 + *(int*)local_8);
                FUN_0043b140(); // some helper
                currentIndex = local_58;
            } else if ((int)currentIndex < (int)(local_54 - 1)) {
                // Normal case: go to next node
                local_8 = (void**)((intptr_t)local_8 + *(int*)local_8);
                local_58 = currentIndex + 1;
                currentIndex = local_58;
            } else {
                // End of list: set to sentinel address
                local_8 = (void**)&DAT_01163cf8; // sentinel
                local_8 = (void**)&DAT_01163cf8;
            }
        } else {
            // Array+bitmask mode: iterate over array using bitmask
            local_58 = currentIndex + 1;
            currentIndex = local_58;
            if (local_58 != local_54) {
                local_4c = (short)local_58;
                // Check if this index is excluded by bitmask
                if ((*((unsigned char*)((local_58 >> 3) + local_60) & (1 << (local_58 & 7))) == 0)
                {
                    // Bit not set: include this element
                    local_50 = local_5c;           // pointer to current array element
                    local_48 = *local_5c;          // first word of element
                    local_5c = local_5c + 1;       // advance array pointer
                } else {
                    // Bit set: skip this element
                    local_50 = nullptr;
                    local_48 = 0;
                }
            }
        }
    }
}