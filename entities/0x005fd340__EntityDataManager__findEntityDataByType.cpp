// FUNC_NAME: EntityDataManager::findEntityDataByType
void __thiscall EntityDataManager::findEntityDataByType(int this, ushort typeIndex, int entityType, int *outData)
{
    int *dataEntry;
    int *typeEntry;
    int *entityEntry;
    ushort dataIndex;
    int dataOffset;
    int typeBase;
    uint currentOffset;
    uint typeOffset;
    bool found;

    found = false;
    outData[0] = 0;
    outData[1] = 0;

    if (typeIndex != 0xffff) {
        // +0x60: pointer to type table (array of 8-byte entries)
        typeEntry = (int *)(*(int *)(this + 0x60) + (uint)typeIndex * 8);
        // typeEntry[1] is the offset into the data table (stored as ushort)
        typeOffset = (uint)*(ushort *)(typeEntry + 1);
        // +0x58: pointer to data table (array of 8-byte entries)
        typeBase = *(uint *)(*(int *)(this + 0x58) + typeOffset * 8);
        dataEntry = (int *)(*(int *)(this + 0x58) + typeOffset * 8);

        do {
            // Check if current entry's range (start + size) exceeds the base
            if ((uint)(*dataEntry + dataEntry[1]) <= typeBase) {
                return;
            }

            // +0x50: pointer to entity data table (array of 8-byte entries)
            entityEntry = (int *)(*(int *)(this + 0x50) + typeBase * 8);
            if (*entityEntry == entityType) {
                dataIndex = *(ushort *)(entityEntry + 1);
                // +0x68: base offset for data
                dataOffset = *(int *)(this + 0x68);
                found = true;
                // typeEntry[0] is the type's base offset
                int typeBaseOffset = *typeEntry;
                outData[0] = (int)entityEntry;
                outData[1] = (uint)dataIndex + dataOffset + typeBaseOffset;
            }
            typeBase = typeBase + 1;
        } while (!found);
    }
    return;
}