// FUNC_NAME: AssetManager::getData
// Address: 0x00558a70
// Role: Retrieves a pointer from an asset table by ID, after adjusting for a base offset.

unsigned int __thiscall AssetManager::getData(int assetID)
{
    // Adjust assetID by subtracting the base ID stored in the base table
    int* baseTable = *(int**)(this + 4);                 // +0x04: m_pBaseTable
    int baseID = *(int*)(baseTable + 1);                 // +0x04 from baseTable: m_baseID
    assetID -= baseID;

    if (assetID < 0) {
        return 0xFFFFFFFF;                               // Invalid ID
    }

    int* dataArrayBase;
    if (*(int*)(this + 0x1c) != 0) {                     // +0x1c: m_pOverrideTable
        int* overrideTable = *(int**)(this + 0x1c);
        int* ptr1 = *(int**)(overrideTable + 0x10);      // +0x10 from overrideTable
        int* ptr2 = *(int**)(ptr1 + 0x30);               // +0x30 from ptr1
        dataArrayBase = *(int**)(ptr2);                   // Dereference to get base pointer
    } else {
        dataArrayBase = *(int**)0x30;                    // piRam00000030 (global pointer)
    }

    // Each entry in the data array is 0x70 bytes.
    // At offset 0x40 from the base, we have the start of the entry array.
    // Each entry contains a pointer at offset 0, and we read the value at offset 8 from that pointer.
    int* entry = (int*)((char*)dataArrayBase + 0x40 + assetID * 0x70);
    unsigned int result = *(unsigned int*)(*(int*)(entry) + 8);
    return result;
}