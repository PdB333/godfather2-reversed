// FUNC_NAME: LinkOwner::setLink
// Function address: 0x00724e60
// Sets a link pointer to point to a node inside an object, maintaining a back-pointer for automatic cleanup.
// The this object holds: dword at +0 (some ID/value), pointer at +4 (m_pLink), and a pointer at +8 (m_pNodePrev) that stores the previous back-pointer of the node.
// Node structure at offset 0x48 of param_3: a field at +4 (backPtr) that points to the location holding the link in the parent.
// If param_3 is zero, the link becomes null. Otherwise, the node is at param_3 + 0x48.

class LinkOwner {
public:
    int       m_value;      // +0x00: value stored from param_2
    void*     m_pLink;      // +0x04: pointer to the linked node (or null)
    void*     m_pNodePrev;  // +0x08: previous back-pointer value (node->backPtr before overwrite)

    // This method is analogous to setting a "weak" or "owned" link.
    // It can be called with param_3 = 0 to clear the link.
    void __thiscall setLink(int value, void* pObject) {
        m_value = value;

        void* pNewNode = pObject ? reinterpret_cast<char*>(pObject) + 0x48 : nullptr;

        if (m_pLink != pNewNode) {
            // Release old link if it exists
            if (m_pLink) {
                releaseLink(m_pLink);  // call to FUN_004daf90 - likely decrements refcount or frees node
            }

            m_pLink = pNewNode;

            if (pNewNode) {
                // Save the node's current back-pointer (prev pointer to the parent's m_pLink location)
                m_pNodePrev = *reinterpret_cast<void**>(reinterpret_cast<char*>(pNewNode) + 4);
                // Update the node's back-pointer to point to our m_pLink location
                *reinterpret_cast<void**>(reinterpret_cast<char*>(pNewNode) + 4) = &m_pLink;
            }
        }
    }
};