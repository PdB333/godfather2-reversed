// FUNC_NAME: EAPropertyManager::applyValueToMatchingNodes
int EAPropertyManager::applyValueToMatchingNodes(int obj, int value) {
    // obj is a pointer to a container object with structure:
    // +0x04: some pointer (maybe count or flag)
    // +0x08: pointer to node list head (list node at +0x1c has next pointer)
    // +0x0c: flag to allocate or skip

    int iVar4 = obj; // local copy of obj pointer
    undefined1* stringPtr = *(undefined1**)*in_EAX; // dereference this pointer
    if (stringPtr == (undefined1*)0x0) {
        stringPtr = &DAT_0120546e; // default string constant
    }
    int hash = FUN_004dafd0(stringPtr); // get hash/ID from string
    // Now hash stored in what was param_1 (obj) -- overlapped? Actually they assigned param_1 = hash, but iVar4 still holds obj pointer.

    if (*(int*)(obj + 0xc) != 0) {
        undefined4* slot = (undefined4*)FUN_005df050(&hash); // allocate slot for hash
        *slot = value;
    }

    int head = *(int*)(obj + 8); // pointer to head of list
    if (head != 0 && *(int*)(obj + 4) != 0) { // both pointers must be non-null
        int currentNode = **(int**)(head + 0x1c); // get first node from head's next? Actually dereference twice
        // current list node structure: +0x10 points to some entity with fields at +0x2b4 and +0x29c
        int listEnd = *(int*)(*(int*)(obj + 8) + 0x1c); // end marker (pointer to sentinel or last)

        do {
            int iterHead = *(int*)(obj + 8);
            if (head == 0 || head != iterHead) {
                FUN_00b97aea(); // assert failure
            }
            if (currentNode == listEnd) break;

            if (head == 0) {
                FUN_00b97aea(); // assert failure
            }
            if (currentNode == *(int*)(head + 0x1c)) { // if current equals the next pointer of head? (self-referential sentinel)
                FUN_00b97aea(); // assert failure
            }

            // Check if the entity's hash matches
            if (*(int*)(*(int*)(currentNode + 0x10) + 0x2b4) == hash) {
                if (currentNode == *(int*)(head + 0x1c)) {
                    FUN_00b97aea(); // assert failure
                }
                *(undefined4*)(*(int*)(currentNode + 0x10) + 0x29c) = value; // set property
            }
            FUN_005e09e0(); // advance iterator
        } while (true);
        return 1;
    }
    return 0;
}