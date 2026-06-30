// FUNC_NAME: Destructible::destroy
undefined4 __thiscall Destructible::destroy(char *this) {
    int iVar1;
    undefined4 uVar2;
    DestructionCallback *callback_entry;

    // Check if destruction is already in progress
    if (*(char *)(this + 0x51c) == '\x01') {
        *(char *)(this + 0x51c) = '\0';
        // Invoke registered destruction callbacks from global list
        for (callback_entry = gDestructionCallbacks; callback_entry != (DestructionCallback *)0x0; callback_entry = callback_entry->next) {
            callback_entry->func(this, 0, callback_entry->userData);
        }
    }

    // Destroy sub-object if present (e.g., physics body or ragdoll)
    if (*(int *)(this + 0x4e8) != 0) {
        destroySubObject();
    }

    // If object is still active, deactivate and perform full cleanup
    if (*this != '\0') {
        *this = '\0'; // Mark as inactive
        iVar1 = checkSomething();
        if (iVar1 != 0) {
            doFullCleanup(this);
        }

        // Destroy all children in the first linked list (head at +0x49c, list pointer at +0x4a8)
        while (*(char **)(this + 0x4a8) != this + 0x49c) {
            destroyChild1();
            processChildList1();
            processChildrenList1(this);
        }

        // Destroy all children in the second linked list (head at +0x448, list pointer at +0x464)
        while (*(char **)(this + 0x464) != this + 0x448) {
            destroyChild2();
            cleanChildList2(this, 1);
        }

        // Store result from some function
        uVar2 = getSomething();
        *(undefined4 *)(this + 0x440) = uVar2;

        // Clear some flags
        *(char *)(this + 0x468) = '\0';
        *(char *)(this + 0x469) = '\0';
        *(char *)(this + 0x46a) = '\0';
        *(char *)(this + 0x46b) = '\0';
        *(char *)(this + 0x46c) = '\0';
    }

    // If sub-object still present, release it
    if (*(int *)(this + 0x4e8) != 0) {
        *(int *)(this + 0x4e8) = 0; // Clear pointer
        releaseSubObject();
        finalizeSubObject();
    }

    return 1;
}