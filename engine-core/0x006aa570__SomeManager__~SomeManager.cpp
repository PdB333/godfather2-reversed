// FUNC_NAME: SomeManager::~SomeManager
// Address: 0x006aa570
// Destructor for a class that manages a dynamic array of pointers to sub-objects.
// Layout: offset 0 = vtable, offset 12 = secondary vtable (or base pointer),
//         offset 16 = m_pArray (pointer to array of element pointers),
//         offset 20 = m_arraySize (count of elements).

void __fastcall SomeManager::~SomeManager(SomeManager* this) {
    // vtable pointer at offset 0 is set to a global RTTI/vtable
    this->vtable = &PTR_FUN_00d5d9b8;  // +0x00: first vtable pointer
    this->secondaryVtable = &PTR_LAB_00d5d9b4;  // +0x0C: secondary vtable pointer (or type info)

    // Iterate over the array of pointers and destroy each element
    Element** pCurrent = this->m_pArray;  // +0x10
    Element** pEnd = this->m_pArray + this->m_arraySize;  // +0x14: count
    while (pCurrent != pEnd) {
        // Call destructor for each element (FUN_006aa160)
        ElementDestructor(*pCurrent);
        ++pCurrent;
    }

    // Free the array buffer itself if it exists
    if (this->m_pArray != nullptr) {
        operatorDeleteArray(this->m_pArray);  // FUN_009c8f10
    }

    // Update secondary vtable to a sentinel/clean pointer
    this->secondaryVtable = &PTR_LAB_00d5d9ac;  // +0x0C

    // Global singleton flag cleared
    g_someSingletonFlag = 0;  // DAT_011299ac

    // Additional cleanup (e.g., notify manager)
    DecrementGlobalCounter();  // FUN_004083d0
}