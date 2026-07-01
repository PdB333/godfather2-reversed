// FUNC_NAME: Core::Array::compactAfterRemoval
// Function address: 0x008f66c0
// EA EARS engine - Compacts an array of pointers by removing null entries and optionally resizing.
// param_1: this pointer to a struct with:
//   +0x00: data pointer (int* array of pointers)
//   +0x04: capacity (number of slots allocated)
//   +0x0C: targetSize (number of slots to keep after removal, i.e., capacity - numRemoved)
// The function compacts the array to remove null entries and then shrinks capacity to targetSize.
void __fastcall Core::Array::compactAfterRemoval(int* thisPtr)
{
    uint oldCapacity;
    int* data;
    uint compactedCount;
    uint newCapacity;
    int* scanPtr;
    int* srcPtr;
    uint destIdx;
    uint srcIdx;
    uint idx;

    // targetSize is stored at +0x0C; if zero, nothing to do
    if (thisPtr[3] != 0) {
        oldCapacity = thisPtr[1];                     // +0x04: allocated capacity
        data = (int*)*thisPtr;                        // +0x00: data pointer
        newCapacity = oldCapacity - thisPtr[3];       // desired new capacity after removal

        // Count consecutive non-null elements from start
        scanPtr = data;
        compactedCount = 0;
        while (*scanPtr != 0) {
            scanPtr++;
            compactedCount++;
        }

        // If there are non-null followed by null then trailing non-null, compact
        if (compactedCount < oldCapacity - 1) {
            srcIdx = compactedCount + 1;               // skip the first null
            if (srcIdx < oldCapacity) {
                srcPtr = data + srcIdx;
                do {
                    if (*srcPtr != 0) {
                        if (srcIdx < oldCapacity) {
                            goto startCompact;
                        }
                        break;
                    }
                    srcIdx++;
                    srcPtr++;
                } while (srcIdx < oldCapacity);
            }
            // If we found non-null elements after a null, move them left
            if ((compactedCount != 0) && (srcIdx < oldCapacity)) {
startCompact:
                destIdx = compactedCount * 4;          // byte offset for destination
                do {
                    int* base = (int*)*thisPtr;
                    if (base[srcIdx] != 0) {
                        *(int*)((int)base + destIdx) = base[srcIdx];
                        destIdx += 4;
                    }
                    srcIdx++;
                } while (srcIdx < (uint)thisPtr[1]);
            }
        }

        // Adjust capacity to newCapacity
        if ((uint)thisPtr[1] < newCapacity) {
            // Need to grow: call realloc
            FUN_008f6480(newCapacity);                  // likely a resize/realloc function
            thisPtr[1] = (int)newCapacity;
            thisPtr[3] = 0;
            return;
        }
        if (newCapacity < (uint)thisPtr[1]) {
            // Shrink capacity
            thisPtr[1] = (int)newCapacity;
        }
        thisPtr[3] = 0;
    }
}