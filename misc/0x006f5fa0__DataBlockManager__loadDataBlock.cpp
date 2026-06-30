// FUNC_NAME: DataBlockManager::loadDataBlock
// Function at 0x006f5fa0: Loads a data block from a global resource table, performs self-relative pointer fixup if version matches.
int* __thiscall DataBlockManager::loadDataBlock(void)
{
    // Get pointer to the resource data header (likely from a global registry)
    short* header = (short*)GetGlobalResource();            // 0x0049c9c0

    // Store the data pointer in member field at +0x0C
    this->dataPtr = (int*)header;

    // Check version field (first short == 3 indicates supported version)
    if (*header == 3)
    {
        // If the relative offset at offset 2 is non-zero, adjust it to an absolute pointer
        // (common EA engine technique: offsets relative to base of the block)
        int* relPtr = (int*)(header + 2);
        if (*relPtr != 0)
        {
            *relPtr = *relPtr + (int)header;
        }

        // Perform additional initialization of the data block
        InitializeDataBlock();                              // 0x006f5bd0

        // Return pointer to the loaded data
        return this->dataPtr;
    }

    // Unsupported version, return null
    return 0;
}