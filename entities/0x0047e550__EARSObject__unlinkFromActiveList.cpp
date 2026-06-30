// FUNC_NAME: EARSObject::unlinkFromActiveList
// Address: 0x0047e550

// This function initializes vtable pointers and removes the object from
// a global doubly-linked active list. It also frees any attached linked-list
// node if present. The global lock (DAT_0120e93c) is acquired/released.

void __fastcall EARSObject::unlinkFromActiveList(EARSObject* this)
{
    // Set vtable pointers for the object (multiple inheritance or interface)
    this->baseVtable = &PTR_FUN_00e33268;          // +0x00
    this->interfaceVtable1 = &PTR_LAB_00e33284;   // +0x3C (0xF*4)
    this->interfaceVtable2 = &PTR_LAB_00e33294;   // +0x48 (0x12*4)

    // Acquire global mutex / lock
    acquireGlobalLock(&DAT_0120e93c);

    // If the object owns a linked-list node, release and free it
    if (this->ownedLinkedListNode != nullptr)      // +0x6C (0x1B*4)
    {
        releaseLinkedListNode(this->ownedLinkedListNode);
        freeLinkedListNode(this->ownedLinkedListNode);
    }

    // The object is part of a circular doubly-linked list.
    // this->listSentinel (offset 0x18) points to the sentinel node of the list.
    // this->listSentinelNext (offset 0x19) holds the backup of the next pointer
    // (set externally before this call).
    node_t* sentinel = this->listSentinel;          // +0x60 (0x18*4)
    if (sentinel != nullptr)
    {
        node_t* current = sentinel->next;           // sentinel[1] (offset+4)
        if (current == &this->listSentinel)         // sentinel points to itself?
        {
            // Direct removal: update sentinel's next to the backup
            sentinel->next = this->listSentinelNext; // +0x64 (0x19*4)
            releaseGlobalLock(&DAT_0120e93c);
            return;
        }
        // Traverse the list to find the node whose next points to this->listSentinel
        node_t* nextNode = current->next;           // current[1]
        while (nextNode != &this->listSentinel)
        {
            current = current->next;
            nextNode = current->next;
        }
        // Remove sentinel from the list: update the predecessor's next pointer
        current->next = this->listSentinelNext;     // +0x64
    }

    releaseGlobalLock(&DAT_0120e93c);
}