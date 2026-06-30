// FUNC_NAME: DebugPool::initializeFreeList
// Address: 0x00450d30
// Initializes an array of 1024 24-byte entries at offset +4 with sentinel debug values.
void __thiscall DebugPool::initializeFreeList(void)
{
    // The table is located at this+4, each entry is 24 bytes (6 uint32).
    // Only the first 4 fields are initialized; the remaining 8 bytes are left uninitialized.
    uint32_t *entry = reinterpret_cast<uint32_t *>(reinterpret_cast<char *>(this) + 4);
    int count = 0x400; // 1024 entries

    do {
        entry[0] = 0xbadbadba;  // Magic marker for unused entry
        entry[1] = 0xbeefbeef;  // Another debug constant
        entry[2] = 0xeac15a55;  // EA engine identifier? 
        entry[3] = 0x91100911;  // Possibly a unique tag
        entry += 6;             // Advance to next entry (6 uint32 = 24 bytes)
        count--;
    } while (count >= 0);

    // Note: The two trailing uint32 per entry (offset +16 and +20) are not zeroed.
    // This is intentional – they remain as-is from previous memory state.
}