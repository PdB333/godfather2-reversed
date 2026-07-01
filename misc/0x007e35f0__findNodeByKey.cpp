// FUNC_NAME: findNodeByKey
void findNodeByKey(LinkedListHeader* container, int searchKey, Node** outNode)
{
    Node* currentNode = container->head; // *param_1 = head
    bool found = false;
    *outNode = currentNode;

    while (currentNode != nullptr && !found)
    {
        Node* current = *outNode; // alias for readability
        // The first field of a node is a pointer to its data block
        void* dataBlock = current->dataPtr; // offset 0

        int keyValue;
        if (dataBlock == nullptr)
        {
            keyValue = 0;
        }
        else
        {
            // The data block starts with an ID, and the actual key is at offset -0x48 from that ID?
            // This is unconventional; likely the data block is part of a larger structure.
            // For example: dataBlock points to a vtable or memory header, and the real object is at dataBlock - 0x48.
            // So we read the ID from the object's beginning.
            int* idPtr = (int*)dataBlock;
            if (*idPtr == 0)
                keyValue = 0;
            else
                keyValue = *idPtr - 0x48; // subtract header size to get the actual key (maybe object ID)
        }

        if (keyValue == searchKey)
        {
            found = true;
        }
        else
        {
            // Move to next node via the "next" pointer stored at offset +12 in the data block
            if (dataBlock == nullptr)
            {
                currentNode = nullptr;
            }
            else
            {
                NodesBlock* data = (NodesBlock*)dataBlock;
                currentNode = data->next; // offset 12
            }
            *outNode = currentNode;
        }

        currentNode = *outNode;
    }
}