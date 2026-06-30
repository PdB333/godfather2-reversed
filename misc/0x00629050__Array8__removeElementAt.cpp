// FUNC_NAME: Array8::removeElementAt
// Address: 0x00629050
// This function removes an element (8 bytes) from a dynamic array and returns 2 (success).
// Class structure: 
//   +0x00: maybe something else
//   +0x08: m_pEnd (pointer to one past last element)
//   +0x0c: m_pBase (pointer to first element)
// Elements are 8 bytes each.

int Array8::removeElementAt(int index) {
    int result;
    int* errCode;
    char* errStr;

    // Get error message and log it (seems like a debug assertion)
    result = someStringFunc();  // FUN_00625a70
    errCode = (int*)getLastError(); // FUN_00b9fd9f
    errStr = _strerror((char*)*errCode);
    debugPrint("cannot read %s: %s", result + 1, errStr); // FUN_00625d40

    // Compute address of element to remove
    int* pRemove;
    if (index < 0) {
        // If index negative? Actually param_1 < 1, maybe a safety path
        pRemove = (int*)getCurrentSize(); // FUN_00625430 - returns pointer?? unclear
    } else {
        // Address of element at index (0-based)
        pRemove = (int*)(m_pBase + index * 2); // each element is 2 ints (8 bytes)
    }

    // Shift elements left by one (remove the element at pRemove)
    int* pSrc = pRemove + 2; // next element
    while (pSrc < m_pEnd) {
        pRemove[0] = pSrc[0];
        pRemove[1] = pSrc[1];
        pSrc += 2;
        pRemove += 2;
    }

    // Decrease end pointer by 8 bytes (one element)
    m_pEnd = (int*)((char*)m_pEnd - 8);

    return 2;
}