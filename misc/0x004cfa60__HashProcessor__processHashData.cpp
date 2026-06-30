// FUNC_NAME: HashProcessor::processHashData
void __thiscall HashProcessor::processHashData(int param2) {
    char discriminator;            // local_64 - discriminator for union/state
    int local_58;                  // part of union or result
    int local_54;                  // part of union or result
    int buffer[18];                // local_50 - buffer for hash data (18 ints)
    int* arrayPtr;                 // local_8 - pointer to alternative data

    // Initialize with magic constant 0xe794215b (likely a hash/CRC seed)
    FUN_0043aff0(param2, 0xe794215b);
    // Reset or finalize computation
    FUN_0043af00(0);

    bool condition;
    if (discriminator == '\0') {
        // Scalar result stored via pointer
        condition = (*arrayPtr == 0);
    } else {
        // Compare two integer parts
        condition = (local_58 == local_54);
    }

    if (!condition) {
        int* selectedArray;
        if (discriminator == '\0') {
            selectedArray = arrayPtr;
        } else {
            selectedArray = buffer;
        }
        // Write third element of selected array as byte to object offset 0x8c
        *(char*)(this + 0x8c) = (char)selectedArray[2];
    }
}