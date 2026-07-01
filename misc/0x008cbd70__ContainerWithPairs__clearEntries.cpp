// FUNC_NAME: ContainerWithPairs::clearEntries
// Address: 0x008cbd70
// Role: Clears entries in an inline array of 8-byte pairs, resetting the count.
// Structure: The object contains an inline array of 500 pairs (each pair = two 32-bit ints)
//            at offset 0, and a count (int) at offset 0xFA0 (1000 * 4).
// Only the first (count-1) entries are zeroed; the last entry (if any) is left untouched,
// then count is set to 0. If count == 1, only the count is reset.

class ContainerWithPairs {
public:
    // Array of pairs occupying offsets 0 to 0xF9F (1000 ints = 500 pairs)
    // The count is at offset 0xFA0
    // +0xFA0: int m_entryCount

    void __fastcall clearEntries() {
        int count = *(reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xFA0));
        if (count != 0) {
            if (count == 1) {
                *(reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xFA0)) = 0;
                return;
            }
            int* base = reinterpret_cast<int*>(this);
            for (unsigned int i = 0; i < (count - 1); ++i) {
                base[i * 2] = 0;     // first int of pair
                base[i * 2 + 1] = 0; // second int of pair
            }
            *(reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0xFA0)) = 0;
        }
    }
};