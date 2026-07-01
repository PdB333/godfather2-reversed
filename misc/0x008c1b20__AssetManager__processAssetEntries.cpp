// FUNC_NAME: AssetManager::processAssetEntries
int __thiscall AssetManager::processAssetEntries(void* thisPtr, AssetEntry* pArray, int count, int baseOffset)
{
    AssetEntry* pEntry = pArray;
    int remaining = count;
    int dataOffset = baseOffset + count * 0x14; // baseOffset + count * 20
    int totalSize = dataOffset * 4; // return value: size in bytes

    if (count != 0) {
        do {
            int validationResult = validateEntry(pEntry);
            if (validationResult < 0) {
                // If validation fails, try alternative check if this is a specific asset type
                if (*(int*)((char*)thisPtr + 0x54) == 0x637b907) {
                    validationResult = alternativeValidateEntry(pEntry);
                }
                if (validationResult >= 0) {
                    goto processEntry;
                }
            }
            else {
processEntry:
                processEntryData(pEntry);
                processEntrySubData((AssetEntry*)((char*)pEntry + dataOffset), *(void**)((char*)pEntry + 0x3c));
            }
            // Advance to next entry
            int subDataSize = *(int*)((char*)pEntry + 0x3c);
            pEntry = (AssetEntry*)((char*)pEntry + 0x50);
            remaining--;
            dataOffset += subDataSize * 4;
        } while (remaining != 0);
    }
    return totalSize;
}