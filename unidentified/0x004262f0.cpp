// FUN_004262f0: SomeDataContainer::GetDataItem(unsigned int index) const
unsigned int SomeDataContainer::GetDataItem(unsigned int index) const {
    // Check if custom data is available (non-zero count/flag at +0x154)
    if (m_customDataCount != 0) {
        // Return from embedded array at +0x14
        return m_dataArray[index]; // Array of 32-bit values, embedded at +0x14
    }
    // Fallback: read default value from global singleton accessed via thread-local storage
    // FS segment offset 0x2c typically holds a pointer to a per-thread or global context block
    // Dereference it to get a pointer to the defaults structure, then add 0x24 for the default value.
    unsigned int* pGlobalDefaults = *(unsigned int**)__readfsdword(0x2c);
    return *(pGlobalDefaults + 0x24); // pGlobalDefaults[9] (since 0x24 / 4 = 9)
}