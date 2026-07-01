// FUNC_NAME: ObjectPool::removeFromIndex
void __thiscall ObjectPool::removeFromIndex(uint startIdx)
{
    int count = this->m_count;
    if (startIdx < count - 1) {
        do {
            Node* pCurr = &this->m_pNodes[startIdx];
            Node* pNext = pCurr + 1; // next element (8 bytes apart)
            if (pCurr != pNext) {
                // iVar2 = pNext->m_pNext (next element's forward link)
                int nextNext = pNext->m_pNext;
                if (pCurr->m_pNext != nextNext) {
                    if (pCurr->m_pNext != 0) {
                        // free the object associated with pCurr
                        destroyObject(pCurr);
                    }
                    // bypass the next element by linking current directly to nextNext
                    pCurr->m_pNext = (Node*)nextNext;
                    if (nextNext != 0) {
                        // update back link of the new target to point to current
                        pCurr->m_pPrev = (Node*)nextNext->m_pPrev;
                        ( (Node*)nextNext )->m_pPrev = pCurr;
                    }
                }
            }
            ++startIdx;
        } while (startIdx < count - 1);
    }
    // reduce the count
    this->m_count = count - 1;
    // check the now-last element; if not null, free it
    Node* pLast = &this->m_pNodes[this->m_count];
    if (pLast->m_pNext != 0) {
        destroyObject(pLast);
    }
}