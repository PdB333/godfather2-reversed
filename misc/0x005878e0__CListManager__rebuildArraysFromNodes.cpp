//FUNC_NAME: CListManager::rebuildArraysFromNodes
void CListManager::rebuildArraysFromNodes()
{
    // Clear existing array1 if it exists
    if (m_pArray1 != nullptr)
    {
        // Call virtual destructor or free? The code calls (**(code **)(*(int *)*unaff_ESI + 4))(unaff_ESI[1],0);
        // This is likely a virtual function call on the class vtable to free the array.
        // Assuming a method like "freeArray" at vtable+4.
        (this->*reinterpret_cast<void (__thiscall CListManager::*)(void*, int)>(this->vtable[1]))(m_pArray1, 0);
    }

    // Initialize local counters
    int count1 = 0;
    int count2 = 0;
    int dummy = 0;

    // Allocate memory for arrays: size = m_nNodeCount * 8 (since each node contributes up to 2 ints per element? Actually m_nNodeCount * 8 bytes = m_nNodeCount * 2 ints)
    // The allocation function is called via vtable[0] (likely "allocate" or "malloc")
    int* pNewArray1 = reinterpret_cast<int*>( (this->*reinterpret_cast<void* (__thiscall CListManager::*)(int, void*)>(this->vtable[0]))(m_nNodeCount * 8, &dummy) );
    int* pNewArray2 = pNewArray1 + m_nNodeCount; // second array starts after first array's capacity

    m_pArray1 = pNewArray1;
    m_pArray2 = pNewArray2;

    // Iterate over linked list nodes
    ListNode* pNode = m_pHeadNode;
    while (pNode != nullptr)
    {
        int* pData = pNode->pData;       // +0x00
        int nSize = pNode->nSize;        // +0x04
        ListNode* pNext = pNode->pNext;  // +0x0C (offset 3 ints)

        for (int i = 0; i < nSize; i++)
        {
            int value = pData[i];
            if (value != 0)
            {
                *pNewArray1 = value;
                pNewArray1++;
                *pNewArray2 = value;
                pNewArray2++;
            }
        }
        pNode = pNext;
    }

    // Update count of elements in first array
    m_nCount = (pNewArray1 - m_pArray1); // number of ints copied

    // Sort both arrays using helper functions
    // The seed is derived from some register (unaff_EBP >> 8) << 8, likely a random seed or hash
    int seed = (reinterpret_cast<int>(this) >> 8) << 8; // approximation; actual source unknown
    sortArray(m_pArray1, pNewArray1, m_nCount, seed);   // FUN_00588160
    sortArray(m_pArray2, pNewArray2, (pNewArray2 - m_pArray2), seed); // FUN_00588250

    // Clear flag
    m_bFlag = false; // +0x10 (byte)
}