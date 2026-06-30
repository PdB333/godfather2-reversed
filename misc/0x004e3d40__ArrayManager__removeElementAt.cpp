// FUNC_NAME: ArrayManager::removeElementAt
// Removes an element at index from the static array (element size 0xC0 bytes) and shifts remaining elements left.
// Global array: g_poolArray at 0x01218a30, element count at g_poolCount (0x01218d30)
void __fastcall ArrayManager::removeElementAt(void* this_ptr, uint index)
{
    // No use of this_ptr; the function operates on static data.
    // Check if index is within bounds
    if (index < g_poolCount)
    {
        // Shift elements left to fill the gap, but only if not last element
        if (index < g_poolCount - 1)
        {
            // Pointer to the element at index
            uint* pDest = reinterpret_cast<uint*>(&g_poolArray + index * 0x30); // 0xC0 bytes / 4 = 0x30 DWORDs
            do
            {
                // Source is the next element (pDest + 0x30 DWORDs = +0xC0 bytes)
                uint* pSrc = pDest + 0x30;
                // Copy 48 DWORDs (0xC0 bytes) from source to destination
                uint* pDestInner = pDest;
                uint* pSrcInner = pSrc;
                for (int i = 0x30; i != 0; --i)
                {
                    *pDestInner = *pSrcInner;
                    ++pDestInner;
                    ++pSrcInner;
                }
                // Move to next pair
                ++index;
                pDest += 0x30;
            } while (index < g_poolCount - 1);
        }
        // Decrement the count
        g_poolCount--;
    }
}