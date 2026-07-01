// FUNC_NAME: ListLink::removeFromList
void __fastcall ListLink::removeFromList(ListLink* this) {
    // Stack-based sentinel for temporary list manipulation
    ListLink* localSentinel;
    ListLink* savedPrev;
    void* tempVtable;   // Placeholder for vtable pointer at +0x00
    uint8_t tempFlag;   // Destructor flag

    // Setup a temporary object – likely a dummy list node
    ListLink** stackMarker = &localSentinel;            // +0x08, unused but present
    localSentinel = reinterpret_cast<ListLink*>(&PTR_FUN_00d5ddf0); // vtable for temporary
    ListLink* dummy = nullptr;                          // local_14
    ListLink* prevCopy = nullptr;                       // local_10

    // Unlink this node from doubly-linked list if it has a successor
    if (this && this->next != nullptr) {
        prevCopy = this->prev;                          // +0x4c: previous node
        this->prev = reinterpret_cast<ListLink*>(&dummy); // point prev to local dummy
        dummy = reinterpret_cast<ListLink*>(this + 0x48); // dummy points to &(this->next)
    }

    // Call base destructor on a stack-temporary object
    tempVtable = reinterpret_cast<void*>(DAT_0112ade8); // static vtable for base
    tempFlag = 0;
    FUN_00408a00(&tempVtable, tempFlag);                 // scalar deleting destructor

    // If dummy was set, remove the node via the head pointer?
    if (dummy != nullptr) {
        FUN_004daf90(&dummy);                           // likely removes node from global list
    }
}