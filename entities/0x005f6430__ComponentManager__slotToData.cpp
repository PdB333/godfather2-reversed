// FUNC_NAME: ComponentManager::slotToData
int* __fastcall ComponentManager::slotToData(int* thisPtr, int* slotPtr)
{
    // thisPtr points to a manager object
    // At offset 0: pointer to a vtable or base struct (m_baseStruct)
    // At m_baseStruct + 0x20: base array of slot structures (each 0x24 bytes)
    // At thisPtr[2] (offset 8): base array of data structures (each 0xc bytes)
    // slotPtr is a pointer to an element in the slot array (index = (slotPtr - base)/0x24)
    // Returns a pointer to the corresponding data structure in the data array.

    int* baseStruct = (int*)*thisPtr;
    int* slotBase = (int*)*(baseStruct + 0x20); // likely m_slotArrayBase
    int* dataBase = (int*)thisPtr[2];           // offset 0x8: m_dataArrayBase

    int index = ( (int)slotPtr - (int)slotBase ) / 0x24;
    return dataBase + index * (0xc / sizeof(int)); // 0xc = 12 bytes, 3 ints
}