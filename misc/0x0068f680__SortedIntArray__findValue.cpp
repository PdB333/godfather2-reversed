// FUNC_NAME: SortedIntArray::findValue
// Function at 0x0068f680: Searches a sorted array of 32-bit values (likely integers or pointers) 
// stored as contiguous memory in the class. Returns the value at the found index or 0 if not found.
// Class layout:
//   +0x00: vtable?
//   +0x04: int* m_pArray;     // pointer to first element
//   +0x08: int   m_count;     // number of elements
// SortedArray is assumed sorted in ascending order.

int __thiscall SortedIntArray::findValue(int this, int key) // param_1 = this, param_2 = key
{
    int* pStart = *(int**)(this + 4);            // m_pArray
    int count = *(int*)(this + 8);               // m_count
    int* pEnd = pStart + count;

    int* pResult = nullptr;            // local_18 (output iterator)
    int* pNext = nullptr;             // local_14 (secondary output from lower_bound, not used directly)
    // local_10, local_c, local_8, local_4 are temporary stack slots for key storage
    // The search function (FUN_0068f290) is a lower_bound variant:
    //   lower_bound(pResult, pStart, pEnd, &key, comparator, 0);
    // It sets pResult to the first element not less than key, and pNext to the next iteration point.
    FUN_0068f290(&pResult, pStart, pEnd, &key, &LAB_0068e390, 0); // comparator compares *item with key

    // Check if the result is within range and exactly matches the key.
    if (pResult != pEnd && pResult != pNext)  // pNext is used for secondary check? 
                                              // Actually pNext may be set by lower_bound to pResult+1 or something.
    {
        return *pResult;   // Found, return the value
    }
    return 0;              // Not found, return 0
}