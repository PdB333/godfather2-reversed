// FUNC_NAME: ManagedComponent::attachNode
// Address: 0x00745270
// Role: Attaches this object to a manager's linked list node (intrusive list via pointer at +0x5c).
// Checks +0x68 flag; obtains a node pointer from a global manager (offset 0x48 into manager object).
// If current node differs, unlinks old node and links to new one, updating forward/back pointers.

extern int* getManager();           // FUN_009b2900 – returns pointer to global manager
extern void unlinkFromList(int** nodePtr); // FUN_004daf90 – removes node from list

void __thiscall ManagedComponent::attachNode()
{
    // +0x68: indicates if this object is active/registered
    if (this->m_isActive == 0)
        return;

    // +0x5c: pointer to current list node (address of a node inside the manager)
    int** currentNodePtr = &this->m_nodePtr;

    // Get new node address from manager's internal member at offset 0x48
    int* manager = getManager();
    int* newNode = manager ? (int*)((char*)manager + 0x48) : 0;

    // Only update if the node actually changed
    if (*currentNodePtr != newNode)
    {
        // Remove old node if present
        if (*currentNodePtr != 0)
        {
            unlinkFromList(currentNodePtr);
        }

        // Store new node pointer
        *currentNodePtr = newNode;

        if (newNode != 0)
        {
            // +0x60: save the previous back link from the new node
            this->m_nodePrev = (int*)(*(int*)(newNode + 4));

            // Set the new node's back link to point to this object's node pointer
            *(int**)(newNode + 4) = currentNodePtr;
        }
    }
}