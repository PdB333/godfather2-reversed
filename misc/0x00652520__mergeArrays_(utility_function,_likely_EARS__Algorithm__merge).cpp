// FUNC_NAME: mergeArrays (utility function, likely EARS::Algorithm::merge)
// Address: 0x00652520
// Merges two sorted arrays (each element 4 bytes) into a third array using a comparator.
// Parameters:
//   this (ECX) - start of first range (firstStart)
//   firstEnd   - end of first range (stack param 1)
//   secondStart - start of second range (stack param 2)
//   secondEnd   - end of second range (stack param 3)
//   outStart    - beginning of output range (stack param 4)
//   comparator  - binary predicate returning char (0 = false, non-zero = true) (stack param 5)
// Returns pointer to end of output range.

typedef char (*Comparator)(uint32_t, uint32_t);

uint32_t* __thiscall mergeArrays(uint32_t* firstStart, uint32_t* firstEnd,
                                  uint32_t* secondStart, uint32_t* secondEnd,
                                  uint32_t* outStart, Comparator comparator)
{
    uint32_t* first = firstStart;
    uint32_t* second = secondStart;
    uint32_t* out = outStart;

    // Merge while both ranges have elements
    while (first != firstEnd && second != secondEnd)
    {
        char compResult = comparator(*second, *first);  // Compare second value with first value
        if (compResult == '\0')    // comparator says second is not less than first? (i.e., first <= second)
        {
            *out = *first;
            first++;
        }
        else
        {
            *out = *second;
            second++;
        }
        out++;
    }

    // Copy remaining elements from first range (if any)
    int remainingFirst = (int)(firstEnd - first);
    if (remainingFirst > 0)
    {
        _memmove_s(out, remainingFirst * 4, first, remainingFirst * 4);
    }

    // Copy remaining elements from second range (if any)
    int remainingSecond = (int)(secondEnd - second);
    if (remainingSecond > 0)
    {
        _memmove_s(out + remainingFirst, remainingSecond * 4, second, remainingSecond * 4);
    }

    return out + remainingFirst + remainingSecond;
}