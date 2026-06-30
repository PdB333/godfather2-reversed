// FUNC_NAME: TripleSortedArray::isGreaterOrEqual

// Function at 0x00497a60: Checks if a given triple (passed via EDI, param_1, param_2) is >= the triple found by lower_bound search in a sorted array.
// Returns 1 if greater or equal, 0 if strictly less than the stored element (or if element not found? Wait, if not found, returns 0 too).
// Actually, if the lower_bound points to end (not found), the function returns 0 immediately. So only returns 1 when an element exists and triple is >= it.

class TripleSortedArray {
public:
    // +0x1c: pointer to array of uint[3] elements (sorted)
    uint* m_pData;
    // +0x20: number of elements in the array
    uint m_nCount;
};

// External function that performs a lower_bound search on an array of triples (size 12 bytes each).
// Takes array base and a pointer to a triple to compare against (passed via stack? unknown).
// Returns pointer to the first element not less than the given triple.
uint* LowerBoundTriple(uint* pArray, uint* pKey);  // placeholder; actual FUN_00499300

// Note: This function uses a __thiscall convention, but the third parameter (edi) is passed in register.
// In the original x86 code, EDI holds the first component of the triple, param_1 (stack) second, param_2 (stack) third.
uint __thiscall TripleSortedArray::isGreaterOrEqual(uint param_1, uint param_2)
{
    // this->m_pData at +0x1c, this->m_nCount at +0x20
    uint* pArray = this->m_pData;
    uint count = this->m_nCount;

    // The key to search is formed from EDI, param_1, param_2. Ghidra shows unaff_EDI as a register variable.
    // We'll denote it as ediKey. In actual code, the caller sets EDI before calling.
    // This function only has two explicit stack parameters.
    uint ediKey; // This is actually read from EDI, not a parameter. We'll treat it as a hidden parameter.

    // Stack variable used by LowerBoundTriple as a pointer to the key? The decompilation shows &stack0xfffffff4.
    // We'll assume it's a local triple array of size 3.
    uint localKey[3] = { ediKey, param_1, param_2 };

    uint* pFound = LowerBoundTriple(pArray, localKey);

    // End marker: pArray + count * 3 (since each element is 3 uint = 12 bytes)
    uint* pEnd = pArray + count * 3;

    if (pFound != pEnd)
    {
        // Compare triple (ediKey, param_1, param_2) with the found element
        bool bLess = false;
        if (ediKey < pFound[0])
        {
            bLess = true;
        }
        else if (ediKey == pFound[0])
        {
            if (param_1 < pFound[1])
            {
                bLess = true;
            }
            else if (param_1 == pFound[1])
            {
                if (param_2 < pFound[2])
                {
                    bLess = true;
                }
            }
        }

        if (!bLess)
        {
            // Triple is >= found element
            return 1;
        }
    }

    // Not found or triple is less
    return 0;
}