// FUNC_NAME: findFreeSlot
// Function address: 0x0043bb00
// Role: Searches a 128-slot hash table for an occupied entry, then computes a new index by combining the slot index with the count of trailing ones in the entry's value. If the resulting index is less than 0x1000 (4096), it returns true and stores the index.
// Global variables (likely within a singleton manager):
//   DAT_0110abd4  :  uint32_t  – an initial hash value
//   DAT_0120e710  :  uint32_t  – a shift amount (only low byte used, masked to 5 bits)
//   DAT_0120e714  :  uint32_t  – sentinel value for empty slots
//   DAT_0120e718  :  uint32_t[128] – slot table

bool findFreeSlot(uint32_t *outIndex)
{
    uint32_t startHash = g_initialHash >> (g_shiftAmount & 0x1F);
    uint32_t currentIdx = startHash;

    do {
        if (g_slotTable[currentIdx] != g_sentinelValue) {
            uint32_t entry = g_slotTable[currentIdx];
            int32_t numTrailingOnes = 0;
            // Count consecutive 1 bits from LSB
            for (; (entry & 1) != 0; entry >>= 1) {
                numTrailingOnes++;
            }
            uint32_t newIdx = (currentIdx << (g_shiftAmount & 0x1F)) + numTrailingOnes;
            if (newIdx < 0x1000) {
                *outIndex = newIdx;
                return true;
            }
            return false;
        }
        currentIdx++;
        if (currentIdx > 0x7F) {
            currentIdx = 0;
        }
    } while (currentIdx != startHash);

    return false;
}