// FUNC_NAME: UpdateManager::updateAll
// Function at 0x004599d0: Iterates over a linked list of update nodes and calls processNode on each.
// The list head is stored at this+0x70 (m_updateList).
// Each node: pointer to next (offset 0x00), data pointer (offset 0x08).

void __thiscall UpdateManager::updateAll(void)
{
    UpdateNode *pNode;

    // Walk the linked list starting at m_updateList (this+0x70)
    for (pNode = this->m_updateList; pNode != nullptr; pNode = pNode->next)
    {
        // Call processNode on the object stored at node+0x08
        this->processNode(pNode->object);
    }
}