// FUNC_NAME: ObjectReferenceList::addReference
void __thiscall ObjectReferenceList::addReference(ReferenceNode* pSourceNode) {
    // Calculate the next slot index in the circular buffer (FIFO order)
    int nextSlotIndex = m_head + m_count;
    m_count++; // increment number of used slots
    // Wrap around if beyond capacity
    if (m_capacity <= nextSlotIndex) {
        nextSlotIndex -= m_capacity;
    }
    // Pointer to the slot that will store the reference
    ReferenceNode* pSlot = &m_pBuffer[nextSlotIndex];
    // If the slot happens to be the same as the source node (shouldn't happen), skip
    if (pSlot != pSourceNode) {
        void* newObject = pSourceNode->m_pObject; // object pointer from source node
        if (pSlot->m_pObject != newObject) {
            // Release old object reference if present
            if (pSlot->m_pObject != nullptr) {
                releaseObject(pSlot->m_pObject);
            }
            // Store new object pointer
            pSlot->m_pObject = newObject;
            // If object is valid, insert the slot into object's reference linked list
            // Object has a pointer to the head of its reference list at offset +0x04
            if (newObject != nullptr) {
                pSlot->m_pNext = *(ReferenceNode**)((char*)newObject + 4); // +0x04: object's reference list head
                *(ReferenceNode**)((char*)newObject + 4) = pSlot; // pSlot becomes new head
            }
        }
    }
}