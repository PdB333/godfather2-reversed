// FUNC_NAME: EntityDataManager::FindEntityByID
int __thiscall EntityDataManager::FindEntityByID(int thisPtr, int entityID)
{
    // thisPtr->listHead at offset 0x28: pointer to sentinel node in a circular linked list
    // Each list node has structure: [next, prev, data] (each 4 bytes)
    // The data pointer is at node[2] (offset 8 from node start)
    // Data objects have an ID field at offset 0x88
    int sentinel = *(int *)(thisPtr + 0x28);
    int currentNode = *(int *)sentinel; // start from first real node (skip sentinel)
    
    while (currentNode != sentinel)
    {
        int data = *(int *)(currentNode + 8); // data pointer
        if (*(int *)(data + 0x88) == entityID)
        {
            return data;
        }
        currentNode = *(int *)currentNode; // advance to next node
    }
    return 0; // not found
}