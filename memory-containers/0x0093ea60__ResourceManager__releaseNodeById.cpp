// FUNC_NAME: ResourceManager::releaseNodeById
void __thiscall ResourceManager::releaseNodeById(int id)
{
    // Node structure offsets:
    // +0x00 : Node* m_pNext
    // +0x08 : bool  m_bActive (or some flag)
    // +0x20 : int   m_id
    Node* pNode = *(Node**)(this + 0x48); // head of linked list

    if (pNode != nullptr)
    {
        // Traverse list searching for node with m_bActive == false and matching id
        while (pNode->m_bActive != false || pNode->m_id != id)
        {
            pNode = pNode->m_pNext;
            if (pNode == nullptr)
                return;
        }

        // Found the node; release it with a flag (1)
        processNode(pNode, 1);
    }
}