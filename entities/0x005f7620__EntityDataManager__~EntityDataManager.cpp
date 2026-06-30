// FUNC_NAME: EntityDataManager::~EntityDataManager
void __fastcall EntityDataManager::~EntityDataManager(void)
{
    int count;
    int *node;

    // Save list count before modification
    count = this->listCount1; // +0x50
    // Set vtable to derived class vtable (already set)
    this->vtable = &PTR_FUN_00e407bc;

    // Clear first linked list
    while (count != 0) {
        // Get head of list
        node = *(int **)this->listHead1; // +0x4C, first element pointer
        if (node == (int *)this->listHead1) {
            // List is empty but count > 0 – fatal error
            assertionError();
        }
        // Free the object stored at offset 8 in the list node
        freeListItem1(node[2]); // +8 from node
        // Re-read count (list nodes may have been altered)
        count = this->listCount1;
    }

    // Release object if present (offset 0x2C)
    if (this->objectA != 0) { // +0x2C
        // Call virtual release function (second vtable entry)
        (this->internalObject->vtable->release)(this->objectA, 0);
    }

    // Clear second linked list
    count = this->listCount2; // +0x70
    while (count != 0) {
        node = *(int **)this->listHead2; // +0x6C
        if (node == (int *)this->listHead2) {
            assertionError();
        }
        freeListItem2(node[2]); // +8 from node
        count = this->listCount2;
    }

    // Release more objects (offsets 0x28 and 0x30)
    if (this->objectB != 0) { // +0x28
        (this->internalObject->vtable->release)(this->objectB, 0);
    }
    if (this->objectC != 0) { // +0x30
        (this->internalObject->vtable->release)(this->objectC, 0);
    }

    // Call cleanup virtual (fourth vtable entry)
    (this->internalObject->vtable->cleanup)(); // +0x0C

    // Global cleanup calls
    cleanupGlobalList1(); // FUN_005f9220
    cleanupGlobalList2(); // FUN_005f9020

    // Free string buffer if present
    if (this->nameBuffer != 0) { // +0x04
        freeString(this->nameBuffer); // FUN_009c8f10
    }

    // Restore base class vtable
    this->vtable = &PTR_LAB_00e407c0;
    // Mark singleton as destroyed
    g_managerInstance = 0; // DAT_01223520
    return;
}