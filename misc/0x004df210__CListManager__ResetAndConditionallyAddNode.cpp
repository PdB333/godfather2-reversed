// FUNC_NAME: CListManager::ResetAndConditionallyAddNode
// Address: 0x004df210
// Purpose: Resets a linked list (clears head), then if global state equals 7, creates a new node and inserts it at the head.
//          Node structure: offset +0: data? offset +8: pointer to the list head pointer (for intrusive removal).
//          Assumes 'this' is a class with a head pointer at offset 0.

void CListManager::ResetAndConditionallyAddNode(uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4)
{
    // param2 is unused
    (void)param2;

    // Clear the list head (offset +0 of this)
    this->head = nullptr;

    // Check global state flag
    if (g_globalState == 7) // DAT_01194540 == 7
    {
        // Perform global setup (likely initializes some internal state)
        GlobalPrepareFunc(); // FUN_0051d730

        // Create a new node using the provided parameters (param1, param3, param4)
        Node* newNode = CreateNodeFunc(param1, param3, param4); // FUN_0051c7c0

        // If a node was created, store a pointer to the list head pointer in the node's prevPtr field
        // This allows the node to be easily removed from the list by updating the pointer that points to it.
        if (newNode != nullptr)
        {
            newNode->prevPtr = &(this->head); // offset +8: stores address of head pointer
        }

        // Insert the new node at the head of the list
        this->head = newNode; // offset +0
    }
}