// FUNC_NAME: removeFromArray
void __fastcall removeFromArray(void* this, unsigned int index)
{
    // Global array of 12-byte elements (3 ints) at 0x01222328, count at 0x012224a8
    // Max capacity 32 elements (0x180 bytes)
    struct Element {
        int field0x00; // +0x00
        int field0x04; // +0x04
        int field0x08; // +0x08
    };
    static Element g_array[32];  // actually at 0x01222328
    static int g_count;          // actually at 0x012224a8

    if (index < (unsigned int)g_count) {
        if (index < g_count - 1) {
            // Shift elements left by one slot (12 bytes each)
            Element* src = &g_array[index + 1];
            Element* dst = &g_array[index];
            unsigned int numToMove = g_count - index - 1;
            do {
                *dst = *src; // 12-byte copy (8 + 4)
                src++;
                dst++;
                numToMove--;
            } while (numToMove != 0);
        }
        g_count--;
        // Clear the now-unused last element
        g_array[g_count].field0x00 = 0;
        g_array[g_count].field0x04 = 0;
        g_array[g_count].field0x08 = 0;
    }
    return;
}