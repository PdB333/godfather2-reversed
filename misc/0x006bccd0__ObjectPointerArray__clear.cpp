// FUNC_NAME: ObjectPointerArray::clear
// Address: 0x006bccd0
// This function clears an array of object pointers, destroying each non-null element,
// then frees the array memory and resets the container structure.
// Structure layout:
//   +0x00: m_ppObjects (pointer to array of 8-byte slots, each slot holds a pointer to an object)
//   +0x04: m_count (number of slots in the array)
//   +0x08: m_capacity (or other field)

void __thiscall ObjectPointerArray::clear()
{
    int count = this->m_count;                      // param_1[1]
    while (count > 0)
    {
        count--;                                      // iVar1 = iVar1 + -1
        if (this->m_ppObjects[count] != NULL)         // *(int*)(*param_1 + iVar1*8) != 0
        {
            // Destroy the object at the given slot (address of slot passed)
            ::destroyObject(&this->m_ppObjects[count]); // FUN_004daf90
        }
    }
    this->m_count = 0;                                // param_1[1] = 0
    ::deallocateArray(this->m_ppObjects);             // FUN_009c8f10
    this->m_ppObjects = NULL;                         // *param_1 = 0
    this->m_capacity = 0;                             // param_1[2] = 0
}

// Note: The helper functions have been given descriptive names:
//   FUN_004daf90 -> ::destroyObject(void* pSlot)  // destroys object at the slot and nulls pointer
//   FUN_009c8f10 -> ::deallocateArray(void* pArray) // frees the array memory