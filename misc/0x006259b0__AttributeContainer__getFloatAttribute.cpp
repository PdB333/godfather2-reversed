//FUNC_NAME: AttributeContainer::getFloatAttribute
// Function at 0x006259b0: Retrieves a float value from an attribute array by 1-based index.
// Structure: this +0x8 = m_pEnd (pointer past last element), this +0xC = m_pData (pointer to array of 8-byte entries: {int type, int value}).
// Types: 3 = direct float, 4 = requires conversion via resolveType4.
float AttributeContainer::getFloatAttribute(int index) {
    int* pEntry;
    int local_c; // likely holds converted value for type 4
    int local_8;

    if (index < 1) {
        // Invalid index: use default pointer from helper
        pEntry = (int*)getDefaultPointer();
    } else {
        // Array is 1-based: entry at (index-1)*8 bytes from m_pData
        pEntry = (int*)(*(int*)(this + 0xC) - 8 + index * 8);
        if (pEntry <= *(int**)(this + 0x8)) {
            goto returnZero;
        }
    }

    if (pEntry != nullptr) {
        if (*pEntry == 3) {
            // Type 3: value is stored directly as float
            return (float)pEntry[1];
        }
        if (*pEntry == 4) {
            // Type 4: call conversion function; if successful, use modified index as float
            int result = resolveType4(&index);
            if (result != 0) {
                local_8 = index;          // store modified index
                pEntry = &local_c;        // point to local_c (likely decompilation artifact)
                goto returnAsFloat;       // returns local_8 as float via pEntry[1]
            }
        }
    }

returnZero:
    return 0.0f;

returnAsFloat:
    return (float)pEntry[1]; // pEntry[1] is local_8 (the modified index)
}