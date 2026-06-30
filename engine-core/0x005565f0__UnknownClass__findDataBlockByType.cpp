// FUNC_NAME: UnknownClass::findDataBlockByType
// Address: 0x005565f0
// Searches a list of type IDs (at +0x74, count at +0x78) for a specific ID (0x34133103).
// If found, returns the first dword of the associated data block (via getDataBlock).
// Otherwise returns the first dword of the default data block (ID 0x801).

int __fastcall findDataBlockByType(int this) {
    int count = *(int*)(this + 0x78); // +0x78: number of entries in type list
    int* typeList = *(int**)(this + 0x74); // +0x74: pointer to array of type IDs

    for (int i = 0; i < count; i++) {
        if (typeList[i] == 0x34133103) { // Specific type ID (e.g., a FourCC or hash)
            // Found the type, get its data block
            int* dataBlock = (int*)getDataBlock(/*local buffer*/0, 0x34133103);
            return *dataBlock; // Return first dword of the data block
        }
    }

    // Not found, use default data block (ID 0x801)
    int* defaultData = (int*)getDataBlock(/*local buffer*/0, 0x801);
    return *defaultData;
}