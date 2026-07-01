// FUNC_NAME: AssetLookupTable::GetResource
// Address: 0x00772930
// Retrieves a pointer to a resource identified by two indices. The resource has a 0x10-byte header before the payload.
// Class structure (offsets relative to this):
// +0x14 m_primaryCount (int) - size of the primary index table
// +0x18 m_ppPrimaryTable (void*) - array of 8-byte entries, each containing a pointer to an array of ints (secondary index table)
// +0x1c m_pRemapTable (void*) - optional remap table; array of 12-byte structures, first dword is remapped index or -1
// +0x30 m_pResourceArray (int**) - array of pointers to resource headers (each header is 0x10 bytes)

int* AssetLookupTable::GetResource(int primaryIdx, unsigned short secondaryIdx) const
{
    // Get the resource pointer array
    int** resourceArray = *(int***)((char*)this + 0x30);
    if (resourceArray == nullptr) {
        return nullptr;
    }

    int indexInTable;
    // Check primary index validity
    int* primaryTable = *(int**)((char*)this + 0x18);
    int primaryCount = *(int*)((char*)this + 0x14);
    if (primaryTable == nullptr || primaryIdx >= primaryCount || primaryIdx < 0) {
        indexInTable = 0;
    } else {
        // Access secondary index table: each primary entry is 8 bytes (contains a pointer to the secondary array)
        int* secondaryArray = *(int**)((char*)primaryTable + primaryIdx * 8);
        // Get the value at the secondary index
        indexInTable = secondaryArray[secondaryIdx];
    }

    // Apply remapping if present
    int* remapTable = *(int**)((char*)this + 0x1c);
    if (remapTable != nullptr) {
        int remappedIndex = *(int*)((char*)remapTable + indexInTable * 0xc); // each remap entry is 12 bytes, first int is the remapped value
        if (remappedIndex != -1) {
            indexInTable = remappedIndex;
        }
    }

    // Return pointer to the resource data (after the 0x10-byte header)
    return resourceArray[indexInTable] + 0x10; // +0x10 to skip header
}