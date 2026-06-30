// FUNC_NAME: NodeManager::updateAllNodeData
void __thiscall NodeManager::updateAllNodeData(void)
{
    Node* pNode;
    
    // Get the first node's next pointer (skip head node)
    if (this->m_pHead == 0) {
        pNode = 0;
    }
    else {
        // head node stores a pointer to the next node at +0x30
        pNode = this->m_pHead->pNext;  // +0x30
    }
    
    while (true) {
        if (pNode == 0) {
            return;
        }
        // Copy 16 bytes from offset +0x18 to +0x08 (e.g., target to current)
        // First 8 bytes (offset +0x18 -> +0x08)
        *(unsigned long long*)(pNode + 0x08) = *(unsigned long long*)(pNode + 0x18);
        // Next 8 bytes (offset +0x20 -> +0x10)
        *(unsigned long long*)(pNode + 0x10) = *(unsigned long long*)(pNode + 0x20);
        
        // Redundant check (compiler artifact)
        if (pNode == 0) break;
        
        // Move to next node via +0x30
        pNode = pNode->pNext;  // +0x30
    }
    
    return;
}