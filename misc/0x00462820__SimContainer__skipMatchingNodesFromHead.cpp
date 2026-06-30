// FUNC_NAME: SimContainer::skipMatchingNodesFromHead
void __fastcall SimContainer::skipMatchingNodesFromHead(int this, void *container)
{
    int listId = *(int *)(this + 8);                  // +0x08: ID used for comparison
    int *currentNode = *(int **)((char *)container + 0x28); // +0x28: head of linked list
    bool hadMatch = false;

    while (true)
    {
        while (true)
        {
            if (currentNode == nullptr)
            {
                return;
            }

            // Compare listId with the ID stored in the node's associated object
            // Node structure: *currentNode points to object +0x70 -> another object +0x08
            if (listId != *(int *)(*(int *)(*currentNode + 0x70) + 8))
            {
                break;
            }

            // Found a matching node – advance via removal/skip helper
            int nextNodeHolder;
            currentNode = (int *)*((int *)__cdecl getNextNodeAfterRemoval(&nextNodeHolder)); // FUN_004634b0
            hadMatch = true;
        }

        if (hadMatch)
        {
            break; // Stop after first non‑matching node following a match
        }

        currentNode = (int *)currentNode[1]; // +0x04: next pointer in linked list node
    }

    return;
}