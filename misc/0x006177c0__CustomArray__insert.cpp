// FUNC_NAME: CustomArray::insert
int* CustomArray::insert(int index)
{
    // Structure layout:
    // +0x00: m_pData (pointer to array of 8-byte elements)
    // +0x04: m_nSize (number of elements)
    // +0x08: m_nCapacity (allocated capacity)

    int* pThis = param_1;
    int nSize = pThis[1];  // m_nSize
    int nCap = pThis[2];   // m_nCapacity

    // Grow if full
    if (nSize == nCap)
    {
        if (nCap == 0)
            nCap = 1;
        else
            nCap <<= 1;
        FUN_00617ba0(pThis, nCap);  // reallocate
    }

    // Pointer to new slot (after current last element)
    int* pNewSlot = (int*)(pThis[0] + nSize * 8);
    int* pBase = (int*)pThis[0];

    if (index != nSize)
    {
        // Insert not at end: first copy the last element's first half to the new slot
        // and zero out the second half (ref-counted pointer)
        if (pNewSlot != nullptr)
        {
            pNewSlot[0] = pNewSlot[-2];  // copy first half from element at nSize-1
            pNewSlot[1] = 0;             // set ref counted pointer to null
            FUN_006164e0(&pNewSlot[1]);  // initialize ref counted pointer (e.g., set to 0)
        }

        // Shift elements from index to size-1 one position up
        for (int i = nSize; --i > index; )
        {
            int* pCur = (int*)(pBase + i * 8);
            // Copy element from i-1 to i (first half only, ref adjust for second half)
            pCur[0] = *(int*)(pBase + (i - 1) * 8);
            int iPrevSecond = pCur[-1];  // second half of element at i-1
            int iCurSecond = pCur[1];    // second half of current element at i

            if (iCurSecond != iPrevSecond)
            {
                // Release old second half
                if (iCurSecond != 0)
                {
                    // Decrement refcount at offset +8, delete if zero
                    short* pRef = (short*)(iCurSecond + 8);
                    (*pRef)--;
                    if (*pRef == 0)
                    {
                        FUN_00616dc0(iCurSecond);
                        // Call virtual destructor (vtable+4)
                        (**(void (__thiscall**)(void*, int))g_pHeapManager)((void*)iCurSecond, 0);
                    }
                    pCur[1] = 0;
                }
                // Acquire new second half
                if (iPrevSecond != 0)
                {
                    short* pRef = (short*)(iPrevSecond + 8);
                    (*pRef)++;
                    pCur[1] = iPrevSecond;
                }
            }
        }

        // Now insert into the now-vacant slot at index
        int* pInsert = pBase + index * 8;
        int nOldSecond = pInsert[1];
        if (nOldSecond != 0)
        {
            // Release old second half
            short* pRef = (short*)(nOldSecond + 8);
            (*pRef)--;
            if (*pRef == 0)
            {
                FUN_00616dc0(nOldSecond);
                (**(void (__thiscall**)(void*, int))g_pHeapManager)((void*)nOldSecond, 0);
            }
            pInsert[1] = 0;
        }
        // Zero out second half of new element (caller will fill)
        pInsert[1] = 0;
        pThis[1] = nSize + 1;  // increment size
        return pInsert;
    }
    else
    {
        // Insert at end: just set second half to null and return slot
        if (pNewSlot != nullptr)
        {
            pNewSlot[1] = 0;
            FUN_006164e0(&pNewSlot[1]);  // initialize (set to 0)
        }
        pThis[1] = nSize + 1;
        return pNewSlot;
    }
}