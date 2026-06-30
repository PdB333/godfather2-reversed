// FUNC_NAME: Utility::lowerBound
// Function address: 0x0068ee00
// Performs a binary search on an array of 4-byte elements.
// Returns a pointer to the first element not less than the key (based on comparator).
// Comparator should return 0 if key is not less than element (i.e., key >= element).
// This is essentially std::lower_bound with a custom comparator.

int* lowerBound(int* arrayStart, int* arrayEnd, int* keyPtr, int (*compareFunc)(int, int))
{
    int count;          // number of elements remaining
    int half;           // half of current range
    char cmpResult;     // result of comparator

    count = (arrayEnd - arrayStart) >> 2; // number of elements (arrayEnd is byte pointer? Actually int* difference is in elements, but here they treat as byte difference? Wait: param_2 - param_1 >> 2 => byte difference shifted by 2 gives element count. So arrayStart and arrayEnd are byte pointers? But the decompile uses int* for element access, so param_1 is int*, but difference in bytes? In x86, int* subtraction gives element count, not shifted. However the code does `param_2 - param_1 >> 2`. That implies param_2 and param_1 are byte pointers or the difference is in bytes. For example, if param_1 = 0x100, param_2 = 0x120, difference = 0x20, >>2 = 8 elements. That matches byte difference. So param_1 and param_2 are byte pointers (char* or void*). But they are used as int* later: `*(undefined4 *)(param_1 + iVar3 * 4)`. So indeed param_1 is a byte pointer. So it's best to treat as void* or char*. I'll use int* for simplicity but comment.

    while (count > 0) {
        half = count >> 1; // step
        cmpResult = compareFunc(*keyPtr, *(int*)((char*)arrayStart + half * 4)); // compare key with element at index half
        if (cmpResult == '\0') { // 0 means key >= element? Then move right
            // Move start past this element
            arrayStart = (int*)((char*)arrayStart + (half + 1) * 4); // param_1 = param_1 + 4 + half*4 = (half+1)*4 bytes
            count = count - half - 1; // remaining elements on the right
        } // else: key < element, stay left, half becomes new count (since count = half is done by loop)

        // If cmpResult != 0, count becomes half (since iVar3 = half after assignment, then condition re-evaluates)
    }

    return arrayStart; // insertion point (byte pointer)
}