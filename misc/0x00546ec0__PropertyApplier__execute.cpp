// FUNC_NAME: PropertyApplier::execute
void __thiscall PropertyApplier::execute(PropertyApplier *this, int *functionTable) {
    // 0x0043aff0 - iterator initialization function (takes this, constant)
    initIterator(this, 0x50ab9af2);

    void **iterator = this->mIterator;
    char useListMode; // local_64
    uint index; // local_58
    uint count; // local_54
    void *currentNode;
    ushort nodeSize;
    // ... other locals

    // The loop iterates over container nodes (list or indexed)
    while (true) {
        bool done;
        if (useListMode == 0) {
            done = (*iterator == nullptr);
        } else {
            done = (index == count);
        }
        if (done) break;

        void **nodePtr;
        if (useListMode == 0) {
            nodePtr = iterator;
        } else {
            nodePtr = &currentNode; // local_50
        }

        ushort typeId = *(ushort*)((char*)nodePtr + 6); // offset 6 in node structure
        void *value;
        if (typeId == 0x25e3) {
            value = (void*)(uint)*(ushort*)((char*)nodePtr + 4); // offset 4 is a ushort
        } else {
            value = *(void**)((char*)nodePtr + 4); // offset 4 as pointer
        }

        if (value == nullptr) {
            // Set float property at offset 8
            if (useListMode == 0) nodePtr = iterator;
            else nodePtr = &currentNode;
            float scale = *(float*)((char*)nodePtr + 8) * DAT_00e445c8; // global float constant
            *(float*)((char*)this + 8) = scale;
        } else if (value == (void*)1) {
            // Set all booleans in array at offset 0x10 to true
            if (useListMode == 0) nodePtr = iterator;
            else nodePtr = &currentNode;
            void *payload = *(void**)((char*)nodePtr + 8);
            uint count = (*(code **)(*functionTable + 0x228))(0); // get count
            for (uint i = 0; i < count; i++) {
                *(bool*)(i + *(int*)((char*)this + 0x10)) = (payload != nullptr);
            }
        } else if (value == (void*)2) {
            // Set booleans from count to max
            if (useListMode == 0) nodePtr = iterator;
            else nodePtr = &currentNode;
            void *payload = *(void**)((char*)nodePtr + 8);
            uint start = (*(code **)(*functionTable + 0x228))(0);
            uint end = (*(code **)(*functionTable + 0x220))(); // get max
            for (uint i = start; i < end; i++) {
                *(bool*)(i + *(int*)((char*)this + 0x10)) = (payload != nullptr);
            }
        }

        // Advance iterator
        if (useListMode == 0) {
            if ((int)index < 0) {
                // linked list: advance via pointer offset
                iterator = (void**)((char*)iterator + (int)*iterator);
                (*(code **)0x0043b140)(); // list advance helper
            } else if ((int)index < (int)(count - 1)) {
                index++;
                iterator = (void**)((char*)iterator + (int)*iterator);
            } else {
                iterator = (void**)&DAT_01163cf8; // sentinel
            }
        } else {
            index++;
            if (index != count) {
                // indexed: read next element via bitmask
                currentNode = *(void**)((char*)&currentNode + 4);
                // ... actually the code manipulates bitmask and stack
                // Simplified: advance to next set bit
                // Original used local_58, local_54, iStack_60, puStack_5c, uStack_4c, uStack_48
                // We'll assume a generic indexed traversal
            }
        }
    }
}