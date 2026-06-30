// FUNC_NAME: EARSNode::destroyNode
// Function at 0x00498200 - Node cleanup/destructor that frees owned data and recursively destroys first child
// Assumes node structure:
// +0x00: m_pFirstChild (EARSNode*)
// +0x04: m_pData (void* - owned pointer to free)
// +0x10: m_pName (char* - owned pointer to free)
// +0x14: m_pExtra (void* - owned pointer, only in parent? freed directly)
// Base class cleanup is performed first via FUN_004982b0.
// FUN_009c8f10 is assumed to be operator delete(void*)
// FUN_009c8eb0 is assumed to be a custom node destructor (calls operator delete after cleanup)

void __thiscall EARSNode::destroyNode(void) {
    void** thisPtr = reinterpret_cast<void**>(this);

    // Base class destructor / initial cleanup
    baseDestroy();  // FUN_004982b0

    // Free the extra allocated data owned by this node (offset 0x14)
    operatorDelete(thisPtr[5]);  // FUN_009c8f10(this->m_pExtra)

    // If there is a first child, clean up its owned data then destroy the child node
    EARSNode* child = reinterpret_cast<EARSNode*>(thisPtr[0]);  // this->m_pFirstChild
    if (child != nullptr) {
        // Free child's name/data at offset 0x10 and 0x4
        operatorDelete(child->m_pName);   // FUN_009c8f10(child->m_pName)
        if (child->m_pData != nullptr) {
            operatorDelete(child->m_pData);  // FUN_009c8f10(child->m_pData)
        }
        // Destroy the child node (will recursively clean up its own children, etc.)
        destroyChildNode(child);  // FUN_009c8eb0(child)
    }
}