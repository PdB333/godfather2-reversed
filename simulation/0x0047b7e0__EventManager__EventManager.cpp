// FUNC_NAME: EventManager::EventManager
void __thiscall EventManager::EventManager(EventManager *this)
{
    int listNode;
    EventManager **nodePtr;
    EventManager **nextPtr;
    char isInitialized;

    this->vtable = &EventManager_vtable; // +0x00
    this->subobjectVtable1 = &EventManager_vtable_0xf; // +0x3C
    this->subobjectVtable2 = &EventManager_vtable_0x12; // +0x48

    // Initialize three subobjects (likely arrays of callback slots)
    constructArray(&this->subarrayA); // +0x14, calls FUN_004086d0
    resetArray(&this->subarrayA);     // +0x14, calls FUN_00408310
    constructArray(&this->subarrayB); // +0x16
    resetArray(&this->subarrayB);
    constructArray(&this->subarrayC); // +0x18
    resetArray(&this->subarrayC);

    // Check if global singleton needs initialization
    isInitialized = isGlobalInitialized(&g_SomeGlobal); // FUN_00402080
    if (isInitialized != '\0') {
        constructArray(&g_SomeGlobal); // FUN_004086d0
    }

    // Remove stale node from linked list if present
    listNode = this->listNodePtr; // +0x78
    if (listNode != 0) {
        nodePtr = *(EventManager ***)(listNode + 4); // node->next
        if (nodePtr == &this->listNodePtr) {
            // Node is directly after the list head; remove it
            *(EventManager ***)(listNode + 4) = this->listNodeNext; // +0x7C
            registerWithGlobalList(); // FUN_0046c640
            return;
        }
        // Traverse circular list to find the node preceding the one being removed
        nextPtr = (EventManager **)nodePtr[1]; // node->next->next
        while (nextPtr != &this->listNodePtr) {
            nodePtr = (EventManager **)nodePtr[1];
            nextPtr = (EventManager **)nodePtr[1];
        }
        nodePtr[1] = this->listNodeNext; // update previous node's next
    }
    registerWithGlobalList(); // FUN_0046c640
}