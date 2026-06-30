// FUNC_NAME: SlotTable::removePair
// 
// Removal of an entry from a fixed-size slot table (max 32 slots, each 5 ints)
// by matching two key values passed in registers EDI and ESI.
// The table structure: [0] count, [1-3] header, [4..] array of slots.
// Each slot: key1, key2, data[3].

void __fastcall SlotTable::removePair(int thisPtr, int* table)
{
    int key1; // passed in EDI (not a parameter)
    int key2; // passed in ESI

    int i = 0;
    int* slotPtr = table + 5; // +5 skips header (count + 3 unknown fields + first slot's key1?)

    while (slotPtr[-1] != key1 || *slotPtr != key2) {
        i++;
        slotPtr += 5;
        if (i > 31) {
            return; // not found
        }
    }

    if (i != -1) {
        // Zero the key fields of the found slot (offset i*5+4 and i*5+5)
        table[i * 5 + 4] = 0;
        table[i * 5 + 5] = 0;
        // Decrement the total active slot count (stored at table[0])
        *table = *table - 1;
    }
}