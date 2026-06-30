// FUNC_NAME: processRangeWithHalfCount
// Function at 0x00651450: processes a range defined by two pointers (end in ESI, start in EDI)
// Computes half the count of 4-byte elements and initializes a stack buffer, then calls a processing function.
void processRangeWithHalfCount(void* endPtr, void* startPtr) {
    int count = ((int)endPtr - (int)startPtr) / 4;          // number of 4-byte entries in the range
    int halfCount = (count + 1) / 2;                       // ceiling of half the count (e.g., for splitting)
    int buffer[4];                                         // local stack buffer (4 ints)
    buffer[0] = 0;                                         // initialize three slots to zero
    buffer[1] = 0;
    buffer[2] = 0;
    buffer[3] = halfCount;                                 // store the computed half count
    FUN_00651530(buffer);                                  // process buffer (likely fills buffer[0] with a result pointer)
    if (buffer[0] != 0) {
        FUN_009c8eb0(buffer[0]);                           // handle non‑zero result (e.g., free memory)
    }
}