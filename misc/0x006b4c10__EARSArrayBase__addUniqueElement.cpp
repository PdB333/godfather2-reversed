// FUNC_NAME: EARSArrayBase::addUniqueElement
void __thiscall EARSArrayBase::addUniqueElement(int element)
{
    uint index;

    // Check if element already exists in array
    if (this->m_nCount != 0) {
        int* pArray = this->m_pArray;
        for (index = 0; index < this->m_nCount; index++) {
            if (pArray[index] == element) {
                // Element already present, nothing to add
                return;
            }
        }
    }

    // Potentially set a global debug callback
    int* globalPtr = FUN_00791300();  // Some global singleton
    if (globalPtr != NULL && *(int*)(globalPtr + 0x158) == 0) {
        *(void**)(globalPtr + 0x158) = (void*)0x006b2cc0;  // Set function pointer
    }

    // Ensure capacity
    int capacity = this->m_nCapacity;
    if (this->m_nCount == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        FUN_006b1e10(capacity);  // Reallocate array to new capacity
    }

    // Append element to end
    int* insertPos = this->m_pArray + this->m_nCount;
    this->m_nCount++;
    if (insertPos != NULL) {
        *insertPos = element;
    }

    // Notify of change
    FUN_006b2f70();
}