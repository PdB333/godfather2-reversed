// FUNC_NAME: EventHashTable::removeEntry
bool EventHashTable::removeEntry(int param_1)
{
    // unaff_ESI points to the 16-byte hash key
    // unaff_EDI is the 'this' pointer
    int* key = reinterpret_cast<int*>(unaff_ESI);

    // Check for sentinel keys (magic constants or all zeros)
    static const int magic0 = 0xBABDBDBA;  // -0x45245246
    static const int magic1 = 0xBEEFBBEF;  // -0x41104111
    static const int magic2 = 0xEAC15A55;  // -0x153EA5AB
    static const int magic3 = 0x91100911;  // -0x6EEFF6EF

    if ( (key[0] == magic0 && key[1] == magic1 && key[2] == magic2 && key[3] == magic3) ||
         (key[0] == 0 && key[1] == 0 && key[2] == 0 && key[3] == 0) )
    {
        return false;
    }

    // Generate a string representation from the current state
    int someId = getSomeId();  // FUN_00471610
    char buffer[76];
    formatHashString(buffer, someId);  // FUN_0044b4e0

    // Copy the key to local stack
    int localKey[4];
    localKey[0] = key[0];
    localKey[1] = key[1];
    localKey[2] = key[2];
    localKey[3] = key[3];

    // Virtual call: vtable entry at offset 0x58 (22nd method)
    int vtableResult = (this->vtable[0x58 / 4])(0);

    // Hash table lookup: returns pointer to list head
    int* listHead = hashTableLookup(&tempStackVar, localKey, buffer, vtableResult);  // FUN_004df330

    // Remove the head node from the list
    int removedNode = *listHead;
    if (removedNode != 0)
    {
        // Set the node's next pointer to point to the stack variable holding the node pointer
        *(int**)(removedNode + 8) = &removedNode;
        *listHead = 0;  // Clear head
    }

    if (tempStackVar != 0)
    {
        *(int*)(tempStackVar + 8) = 0;
    }

    bool bResult = (removedNode != 0);

    if (param_1 != 0)
    {
        cleanupNode(&removedNode);  // FUN_00414db0
    }

    if (removedNode != 0)
    {
        *(int*)(removedNode + 8) = 0;
        return bResult;
    }

    return bResult;
}