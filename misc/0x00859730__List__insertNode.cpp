// FUNC_NAME: List::insertNode
void __thiscall List::insertNode(Node** ppHead, Node** ppTail)
{
    Node* pOldTail = *ppTail;                    // +0x0: head? Actually *ppTail is the tail node
    Node* pNodeToInsert = pOldTail->field_c;     // +0x0c: pointer to node to insert (maybe from a free list?)
    Node* pPrevTail = pOldTail->field_4;         // +0x04: previous tail (or something)

    // Detach pNodeToInsert from its current position (if any)
    pOldTail->field_c = pNodeToInsert->field_8;  // +0x08: next pointer in secondary list?
    if (pNodeToInsert->field_8 != nullptr) {
        pNodeToInsert->field_8->field_4 = pOldTail;
    }
    pNodeToInsert->field_8 = pOldTail;           // Link pNodeToInsert to old tail
    pOldTail->field_4 = pNodeToInsert;           // Old tail's prev points to new node

    // Update ordering value (sequence number?) for old tail
    Node* pTemp = pOldTail;
    int val1 = (pTemp->field_c != nullptr) ? *(int*)pTemp->field_c : -1;
    int val2 = (pTemp->field_8 != nullptr) ? *(int*)pTemp->field_8 : -1;
    pTemp->field_0 = (val1 > val2 ? val1 : val2) + 1;

    // Update ordering value for new node
    int val3 = (*ppTail != nullptr) ? *(int*)(*ppTail) : -1;  // *ppTail is still old tail here
    int val4 = (pNodeToInsert->field_c != nullptr) ? *(int*)pNodeToInsert->field_c : -1;
    pNodeToInsert->field_0 = (val3 > val4 ? val3 : val4) + 1;

    // Set new node's prev to the previous tail (or null)
    pNodeToInsert->field_4 = pPrevTail;

    // Update list pointers
    if (pPrevTail != nullptr) {
        if (pPrevTail->field_8 == pOldTail) {
            pPrevTail->field_8 = pNodeToInsert;
        } else {
            pPrevTail->field_c = pNodeToInsert;
        }
        *ppTail = pNodeToInsert;
    } else {
        *ppHead = pNodeToInsert;
        *ppTail = pNodeToInsert;
    }
}