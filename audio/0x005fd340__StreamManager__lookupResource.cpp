// FUNC_NAME: StreamManager::lookupResource
void __thiscall StreamManager::lookupResource(ushort category, int resourceId, int* outResult)
// outResult[0] = pointer to resource entry (ResourceEntry*), outResult[1] = absolute offset (resourceDataOffset + baseOffset)
// Offsets relative to 'this': +0x50 : ResourceEntry* array (flat list of resource entries, each 8 bytes)
//                              +0x58 : RangeEntry* array (category ranges, each 8 bytes: startIndex, count)
//                              +0x60 : CategoryEntry* array (mapping from category ID to range index, each 8 bytes: unknown0, rangeIndex ushort)
//                              +0x68 : int baseOffset (added to computed offset)
{
    bool found = false;
    outResult[0] = 0;
    outResult[1] = 0;

    if (category == 0xffff) {
        return;
    }

    // Fetch category entry
    CategoryEntry* catEntry = (CategoryEntry*)(*(int*)(this + 0x60) + category * 8);
    ushort rangeIndex = catEntry->rangeIndex;                // +0x04, 2 bytes
    uint currentIndex = *(uint*)(*(int*)(this + 0x58) + rangeIndex * 8); // startIndex of range
    RangeEntry* rangeEntry = (RangeEntry*)(*(int*)(this + 0x58) + rangeIndex * 8);

    do {
        // Check if we've exceeded the range
        if ((uint)(rangeEntry->startIndex + rangeEntry->count) <= currentIndex) {
            return;
        }

        ResourceEntry* resEntry = (ResourceEntry*)(*(int*)(this + 0x50) + currentIndex * 8);
        if (resEntry->id == resourceId) {
            ushort resOffset = resEntry->someOffset;         // +0x04, 2 bytes
            int catUnknown = catEntry->unknown0;             // +0x00, 4 bytes
            int baseOffset = *(int*)(this + 0x68);           // +0x68
            found = true;
            outResult[0] = (int)resEntry;                    // pointer to resource entry
            outResult[1] = (uint)resOffset + baseOffset + catUnknown;
        }

        currentIndex++;
    } while (!found);
}