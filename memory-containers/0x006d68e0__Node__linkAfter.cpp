// FUNC_NAME: Node::linkAfter
// Function at 0x006d68e0: Inserts this node after the node at offset 0x48 of the given object, or detaches if object is null.
// Node structure: +0x00: m_pPrev (pointer to previous node), +0x04: m_pNext (pointer to next node)
// The object is expected to have a Node at offset 0x48.

extern void removeNodeFromList(int* pNode);

int* __thiscall Node::linkAfter(void* pObject) {
    int* pNode = (pObject != 0) ? (int*)((int)pObject + 0x48) : 0;
    if (m_pPrev != pNode) {
        if (m_pPrev != 0) {
            removeNodeFromList(this);
        }
        m_pPrev = pNode;
        if (pNode != 0) {
            m_pNext = (int*)*((int*)pNode + 1); // pNode->m_pNext
            *((int**)pNode + 1) = this;        // pNode->m_pNext = this
        }
    }
    return this;
}