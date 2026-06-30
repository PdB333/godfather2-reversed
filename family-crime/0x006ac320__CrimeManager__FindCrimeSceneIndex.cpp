// FUNC_NAME: CrimeManager::FindCrimeSceneIndex
// Function at 0x006ac320: Searches a fixed-size table (up to 20 entries) for a 4-int key match.
// The table is stored as 4 blocks of 5 entries each (block size = 0xF0 bytes).
// Each entry is a 4-int (16 bytes) structure; entries within a block are spaced 0x30 bytes apart.
// Returns the linear index (0–19) of the matching entry, or 20 if not found.
int CrimeManager::FindCrimeSceneIndex(int *key) {
    // Table base offset relative to this: +0x10 (beginning of first block)
    // Block stride: 0xF0 bytes (60 ints)
    for (int blockIndex = 0; blockIndex < 4; ++blockIndex) {
        int *blockBase = (int *)((char *)this + 0x10 + blockIndex * 0xF0);
        // Each block contains 5 quadruple entries; entry stride: 0x30 bytes (12 ints)
        for (int entryIndex = 0; entryIndex < 5; ++entryIndex) {
            int *entry = blockBase + entryIndex * 12;
            if (entry[0] == key[0] &&
                entry[1] == key[1] &&
                entry[2] == key[2] &&
                entry[3] == key[3]) {
                return blockIndex * 5 + entryIndex;
            }
        }
    }
    // Not found: return total count (20)
    return 20;
}