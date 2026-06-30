// FUNC_NAME: CIterator::advanceNext
void CIterator::advanceNext(void)
{
    // +0x00: m_pList - pointer to a structure containing a count and array of pointers
    void* pList = this->m_pList;
    // +0x04: m_nIndex - current iteration index
    // +0x08: m_nCurrent - current non-null element (or 0 if none)
    this->m_nIndex = 0;
    this->m_nCurrent = 0;
    
    if (pList != nullptr)
    {
        do
        {
            uint currentIndex = this->m_nIndex;
            // *(uint*)(pList + 0x04) is the element count
            if ( *(uint*)((uint)pList + 4) <= currentIndex )
                return;
            
            // *(uint*)(pList + 0x08) is an array of pointers (int sized)
            int element = *(int*)( *(int*)((uint)pList + 8) + currentIndex * 4 );
            this->m_nCurrent = element;
            this->m_nIndex = currentIndex + 1;
        } while ( element == 0 ); // Skip null entries
    }
}