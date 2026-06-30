// FUNC_NAME: GhostConnection::releaseGhostIndex
class GhostConnection {
public:
    // +0x34: Pointer to array of ghost entries (12 bytes each)
    // +0x38: Maximum number of ghost entries (uint32_t)
    void releaseGhostIndex(uint32_t* pIndex);
};

void GhostConnection::releaseGhostIndex(uint32_t* pIndex)
{
    // Validate index
    if (*pIndex < *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x38))
    {
        // Get pointer to the ghost entry structure at this index
        uint8_t* entryBase = *reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(this) + 0x34);
        uint8_t* entry = entryBase + (*pIndex * 12);

        // Clear the first two fields of the entry (each 4 bytes)
        *reinterpret_cast<uint32_t*>(entry + 0) = 0;               // Field1
        *reinterpret_cast<uint32_t*>(entry + 4) = 0xfe16702f;      // Magic sentinel (free)
    }

    // Mark the index as invalid
    *pIndex = 0xFFFFFFFF;
}