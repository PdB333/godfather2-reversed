// FUNC_NAME: merge_sorted_arrays
// Address: 0x00652520
// This function merges two sorted ranges into a destination range.
// Parameters:
//   first1  - start of first sorted range (passed in EAX)
//   last1   - end of first sorted range (passed as param_1)
//   first2  - start of second sorted range (param_2)
//   last2   - end of second sorted range (param_3)
//   dest    - start of output range (param_4)
//   comp    - comparison callback, returns 0 if left >= right (param_5)
// Returns pointer to the end of the output range.

template<typename T>
T* merge_sorted_arrays(T* first1, T* last1, T* first2, T* last2, T* dest, int (*comp)(T, T))
{
    // Use original first1 (passed in EAX) as end condition.
    T* orig_first1 = first1;

    if (first1 != last1) // Check if first range is non-empty (in_EAX is actually last1)
    {
        do {
            if (first2 == last2)
                break;

            int cmpResult = comp(*first2, *orig_first1); // orig_first1 holds the current element from first range? Wait, need to correct: The decompiled code uses *param_1 and *param_2, but here param_1 is first1, param_2 is first2. The comparator takes param_2 first, then param_1. So: comp(*first2, *first1)

            if (cmpResult == 0) {
                *dest = *first1;  // first1 is smaller or equal
                first1++;
            } else {
                *dest = *first2;  // first2 is smaller
                first2++;
            }
            dest++;
        } while (first1 != last1); // Loop until first1 reaches last1
    }

    // Copy remaining elements from first range if any
    int remaining1 = (int)last1 - (int)first1 >> 2;
    if (remaining1 > 0) {
        memmove_s(dest, remaining1 * 4, first1, remaining1 * 4);
    }

    // Copy remaining elements from second range if any
    int remaining2 = (int)last2 - (int)first2 >> 2;
    if (remaining2 > 0) {
        memmove_s(dest + remaining1, remaining2 * 4, first2, remaining2 * 4);
    }

    // Return pointer to end of output
    return dest + remaining1 + remaining2;
}