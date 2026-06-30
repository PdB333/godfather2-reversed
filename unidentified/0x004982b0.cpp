// FUN_NAME: EARSList::clearAll
void __fastcall EARSList::clearAll(EARSList* this)
{
    // this structure:
    // +0x00: m_pBucketData (pointer to bucket array structure)
    // +0x04: m_count (set to 0 after clear)
    // +0x08: m_capacity (number of bucket slots)
    // +0x10: m_totalNodes (decremented per freed node)

    // Bucket array structure at *this->m_pBucketData:
    // +0x10: m_pBuckets (array of ListNode* of size m_capacity)

    ListNode* pNext; // ecx
    ListNode* pCurrent = **(ListNode***)(this->m_pBucketData + 0x10); // head of first bucket

    while (pCurrent != 0) {
        pNext = **(ListNode***)(pCurrent + 0x10); // next node (double indirection)
        FUN_009c8f10(*(ListNode**)(pCurrent + 0x10)); // free data at offset +0x10
        if (*(int*)(pCurrent + 4) != 0) {
            FUN_009c8f10(*(void**)(pCurrent + 4)); // free secondary data at +0x04
        }
        FUN_009c8eb0(pCurrent); // free node itself
        this->m_totalNodes--; // decrement total node count
        pCurrent = pNext;
    }

    // Zero out all bucket pointers
    for (uint i = 0; i <= (uint)this->m_capacity; i++) {
        *(int*)(* (int*)(this->m_pBucketData + 0x10) + i * 4) = 0;
    }
    this->m_count = 0;
}