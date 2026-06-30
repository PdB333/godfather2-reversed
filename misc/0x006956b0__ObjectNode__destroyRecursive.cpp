// FUNC_NAME: ObjectNode::destroyRecursive

struct ObjectNode {
    ObjectNode* m_pNext;       // +0x00: pointer to next sibling
    int pad[1];                // +0x04: padding (may be unused)
    ObjectNode* m_pChild;      // +0x08: pointer to first child
    void* m_pData;             // +0x0C: data passed to callback
    int pad2[2];               // +0x10: padding
    void (*m_fnCallback)(void*); // +0x18: callback function (called with m_pData)
    char m_bProcessed;         // +0x25: flag; if non-zero, skip processing
    // other fields likely present but not needed
};

// Recursively destroys the entire tree rooted at this node.
// Processes children first, then calls the node's callback, then deallocates.
// Skips nodes with m_bProcessed != 0.
// __thiscall: ecx = this (first param)
void __thiscall ObjectNode::destroyRecursive(ObjectNode* this) {
    char cFlag;
    ObjectNode* pNext;

    cFlag = this->m_bProcessed;
    while (cFlag == '\0') {
        // Process children first
        if (this->m_pChild) {
            ObjectNode::destroyRecursive(this->m_pChild);
        }
        pNext = this->m_pNext;
        // If data exists, call the callback with it
        if (this->m_pData != 0) {
            this->m_fnCallback(this->m_pData);
        }
        // Deallocate current node (likely memory manager op)
        FUN_009c8eb0(this);
        // Move to next sibling
        this = pNext;
        cFlag = this->m_bProcessed;
    }
}