// FUNC_NAME: SimManager::shutdown
void __thiscall SimManager::shutdown() {
    // Set vtable pointer to the standard SimManager vtable
    this->vtable = reinterpret_cast<void**>(0x00e39160);
    // Set secondary vtable/RTTI pointer
    this->secondaryVTable = reinterpret_cast<void**>(0x00e39170);

    // If the dynamic buffer flag is set and buffer size is non-zero, release the buffer
    if (this->bufferFlag != '\0' && this->bufferSize != 0) {
        releaseBuffer(&this->buffer, this->bufferSize);  // FUN_009ea940
        this->bufferSize = 0;
    }

    // Iterate through the first linked list (head at this->listHead, offset 0x10)
    int current = this->listHead;
    this->listHead = 0;  // Clear the head pointer
    while (current != 0) {
        int next = *(int*)(current + 0xb0);  // Each node has a next pointer at offset 0xb0
        destroyNode(current);  // FUN_009c8eb0 – likely deletes the node and its resources
        current = next;
    }

    // Iterate through the second linked list (head at this->listHead2, offset 0x11)
    int current2 = this->listHead2;
    unsigned int count2 = 0;
    if (this->list2Count != 0) {
        do {
            int next2 = *(int*)(current2 + 4);  // Next pointer at offset 4
            destroyNode(current2);              // FUN_009c8eb0
            count2++;
            current2 = next2;
        } while (count2 < (unsigned int)this->list2Count);
    }
    this->list2Count = 0;
    this->listHead2 = 0;

    // Destroy global static objects based on a flag in this->flags (offset 0x17)
    destroyStaticObject(&globalObjA);  // FUN_004086d0(&DAT_01206770)
    destroyStaticObject(&globalObjB);  // FUN_004086d0(&DAT_0120679c)

    // Clear bit 0 of the flags
    this->flags = this->flags & 0xfffffffe;

    if ((this->flags & 2) == 0) {
        // Path for bit 1 not set: destroy and delete global object C
        destroyStaticObject(&globalObjC);  // FUN_004086d0(&DAT_0121bf38)
        deleteStaticObject(&globalObjC);   // FUN_00408310(&DAT_0121bf38)
    } else {
        // Path for bit 1 set: destroy two other global objects
        destroyStaticObject(&globalObjD);  // FUN_004086d0(&DAT_012069c4)
        destroyStaticObject(&globalObjE);  // FUN_004086d0(&DAT_012069d4)
    }

    // If there is a pointer to a polymorphic object at this->someObj (offset 0x14), call its vfunc(1) as part of cleanup
    if (this->someObj != nullptr) {
        (*(void(__thiscall**)(int))(*this->someObj))(1);  // Assumes the vtable's first function takes an int
    }
    this->someObj = nullptr;

    // Final global shutdown routines
    shutdownSubsystemA();   // FUN_0053fb70
    shutdownSubsystemB();   // FUN_00ab50b0

    // Update the secondary vtable to its final value (sentry for destructor chaining)
    this->secondaryVTable = reinterpret_cast<void**>(0x00e39174);

    // Clear the global singleton pointer (the manager is no longer valid)
    g_simManager = 0;  // DAT_01223480

    // Last cleanup step
    finalShutdown();  // FUN_004083d0
}