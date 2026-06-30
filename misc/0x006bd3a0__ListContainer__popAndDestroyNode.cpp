// FUNC_NAME: ListContainer::popAndDestroyNode
// Address: 0x006bd3a0

void ListContainer::popAndDestroyNode()
{
    // Check if the list container is in a valid state (e.g., not empty or locked)
    int status = FUN_006bcfa0(this);
    if (status < 0)
    {
        // Pointer to the head node of the linked list stored at offset +0x48
        int* headNode = (this != nullptr) ? reinterpret_cast<int*>((int)this + 0x48) : nullptr;
        int* nextNode = nullptr;
        if (headNode != nullptr)
        {
            // Retrieve the next node pointer from offset +0x04 of the head node
            nextNode = reinterpret_cast<int*>(*(headNode + 1));
            // Replace the next pointer with the address of the local variable to detach this node
            // This is a sentinel trick to safely iterate or free the node
            *(int**)(headNode + 1) = &headNode;
        }

        // Process the detached node (e.g., invoke a destructor or cleanup)
        FUN_006bd130(&headNode);

        // If the node pointer is still valid after processing, free its memory
        if (headNode != nullptr)
        {
            FUN_004daf90(&headNode);
        }
    }
}