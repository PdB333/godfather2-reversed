// FUNC_NAME: EntityManager::updateEntityActiveFlag
// Function at 0x005dc900: Updates an active flag on entities in a linked list, based on comparison with a current reference.
// Offsets: this+8 = pointer to list container; list container+0x1c = pointer to head node; node+0x10 = pointer to entity; entity+0x298 = active flag; entity+0x299 = override flag.

int __thiscall EntityManager::updateEntityActiveFlag(void* this, char param_2) {
    int result;

    // Get the current reference (entity ID or similar) – likely from internal state
    int currentRef = FUN_005dc670(in_EAX); // in_EAX may be this, but ambiguous; assume it returns a reference
    if (currentRef != 0) {
        // List container is at this+0x8
        int* listContainer = *(int**)((char*)this + 8);
        // Head of linked list is at listContainer+0x1c (double indirection to first node)
        int* headNode = *(int**)(listContainer + 0x1c);
        int* currentNode = headNode; // stores the first node pointer for iteration

        while (true) {
            // Re-evaluate the list's head each iteration (lists might be modified?)
            int* currentHead = *(int**)(listContainer + 0x1c);

            // Debug assertions: ensure list container is valid
            if (listContainer == 0 || listContainer != *(int**)((char*)this + 8)) {
                FUN_00b97aea(); // Assertion failure
            }
            if (currentNode == currentHead) break; // Reached the end (circle? Usually head sentinel)

            if (listContainer == 0) {
                FUN_00b97aea();
            }
            if (currentNode == *(int**)(listContainer + 0x1c)) {
                FUN_00b97aea();
            }

            // Get the actual entity from the node – offset +0x10
            int* entity = *(int**)(currentNode + 0x10);

            // Only update if entity doesn't match the current reference
            if (entity != (int*)currentRef) {
                if (param_2 == 0) {
                    // Clear active flag at +0x298
                    *(char*)(entity + 0xA6) = 0; // offset 0x298 = 0xA6*4? Actually char offset, so entity+0x298
                }
                else {
                    // Set active flag only if override flag at +0x299 is not set
                    if (*(char*)(entity + 0xA6 + 1) == 0) { // offset 0x299
                        *(char*)(entity + 0xA6) = 1; // offset 0x298
                    }
                }
            }

            // Move to next node – likely an iterator function
            FUN_005e09e0(); // Probably advances currentNode or something else
        }
        return 1;
    }
    return 0;
}