// FUNC_NAME: NodeList_T::replaceHeadNode
void __thiscall NodeList_T::replaceHeadNode(int this, int* newNode)
{
    // +0x5c: m_pHead (pointer to first node)
    // +0x60: m_pNext (pointer to node's next, updated when head changes)
    // +0x64: m_headData (some value copied from newNode[2])
    int* pHeadField = (int*)(this + 0x5c);  // address of m_pHead

    // If newNode is actually the head pointer field itself, just update data
    if (pHeadField == newNode) {
        *(int*)(this + 0x64) = newNode[2];
        return;
    }

    int newNodeID = *newNode;   // first field of new node (e.g., key or identifier)
    int oldHead = *pHeadField;

    if (oldHead != newNodeID) {
        // Remove the old head if it exists
        if (oldHead != 0) {
            FUN_004daf90(pHeadField);  // likely deletes/releases the node
        }

        // Set new head
        *pHeadField = newNodeID;

        if (newNodeID != 0) {
            // Copy the new node's next pointer into m_pNext
            *(int*)(this + 0x60) = *(int*)(newNodeID + 4);
            // Make the new node's next point to the head pointer field (circular list sentinel)
            *(int**)(newNodeID + 4) = pHeadField;
        }

        // Update the data field
        *(int*)(this + 0x64) = newNode[2];
        return;
    }

    // Head already matches newNodeID, just update data
    *(int*)(this + 0x64) = newNode[2];
    return;
}