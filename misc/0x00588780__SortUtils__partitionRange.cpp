// FUNC_NAME: SortUtils::partitionRange
// Address: 0x00588780
// Partitions an array of 4-byte elements between startPtr and endPtr (exclusive) using a global predicate (FUN_00587840).
// Elements satisfying the predicate are moved to the front. Uses swap (FUN_00588e00) for element exchange.

void partitionRange(uint8_t* startPtr, uint8_t* endPtr) {
    // Need at least two elements (8 bytes)
    if (startPtr == endPtr) return;
    uint8_t* secondPtr = startPtr + 4;
    if (secondPtr == endPtr) return;

    uint8_t* scanPtr = startPtr + 4;    // second element (left scan)
    uint8_t* forwardPtr = startPtr + 8; // third element (right scan)

    while (scanPtr != endPtr) {
        // Predicate: returns 0 if element should stay? Non-zero if move?
        if (!applyCondition()) {
            // Predicate false on current element – check the element two steps behind forwardPtr?
            if (applyCondition()) {
                uint8_t* current = forwardPtr - 8; // two elements back from forwardPtr
                do {
                    uint8_t* lastTrue = current;
                    applyCondition();
                    current = lastTrue - 4;
                } while (/* condition from last call */); // loop while predicate returns non-zero
                // After loop, lastTrue is the position where predicate last returned true
                if (lastTrue != scanPtr && scanPtr != forwardPtr) {
                    swapInt32((int*)lastTrue, (int*)forwardPtr);
                }
            }
        } else {
            // Predicate true on first element – swap start with forwardPtr
            if (startPtr != scanPtr && scanPtr != forwardPtr) {
                swapInt32((int*)startPtr, (int*)forwardPtr);
            }
        }
        scanPtr += 4;
        forwardPtr += 4;
    }
}