// FUNC_NAME: Entity::findDataBlockEntry
// Address: 0x00571b00
// Role: Looks up a component/entry ID from a data block manager based on a search key.
// Uses this->+0x70 (dataManager), +0x74 (dataIndex) to locate a data block,
// then calls helper functions to get an index into an array inside that block.

int __thiscall Entity::findDataBlockEntry(int searchKey)
{
    // Check object and manager validity
    if (this == nullptr) return -1;
    int* dataManager = *(int**)(this + 0x70);
    if (dataManager == nullptr) return -1;

    // Short index into the manager's entry table
    short dataIndex = *(short*)(this + 0x74);

    // The manager +0x1c points to an array of 0x18-byte entries; each entry has
    // a pointer at offset +0x14 that points to a data block structure
    int* entryArray = *(int**)(dataManager + 0x1c);
    int dataBlockPtr = *(int*)((char*)entryArray + 0x14 + dataIndex * 0x18);

    // Call helper functions to resolve an index from the search key
    int unknownResult = FUN_004dafd0(searchKey, dataBlockPtr);
    int elementIndex = FUN_005828a0(unknownResult);

    // Validate the index and retrieve the final ID
    if (elementIndex == -1) return -1;
    int result = *(int*)(dataBlockPtr + 0x10 + elementIndex * 0x14);
    if (result == -1) return -1;
    return result;
}