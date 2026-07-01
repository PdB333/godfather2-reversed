// FUNC_NAME: TimelineSearch::findKeyframeIndex
// Function at 0x008a8780: Searches a sorted array of floats (likely timestamps) for the first element >= a given value.
// Uses global arrays: DAT_010c2680 (float array of size power-of-two), DAT_010c2678 (mask = size-1).
// Global state DAT_012054b4 maintains a current search index for incremental queries.
// The input structure (param_1) points to data: +0x4 = initial cursor offset (?), +0x8 = total element count, +0xC = search value (float).
// Returns the linear index (0-based) of the found element.

uint __fastcall TimelineSearch::findKeyframeIndex(SearchBounds* bounds)
{
    uint linearIndex;
    uint mask;
    uint searchStart;
    uint numElements = *(uint*)((int)bounds + 8); // +0x8: total number of elements in the array
    uint cursor = *(uint*)((int)bounds + 4) + 2;  // +0x4: initial offset (adjusted by +2)
    float searchValue = *(float*)((int)bounds + 0xC); // +0xC: the value to search for

    if (cursor > numElements) {
        cursor = numElements;
    }

    linearIndex = 0;

    // Use global state for the current position in the array
    uint currentPos = DAT_012054b4; // global cursor index (not masked yet)

    if (cursor > 3) {
        do {
            // Check up to 4 consecutive entries per iteration
            // Read array at index (mask & currentPos)
            float val0 = *(float*)(&DAT_010c2680 + (DAT_010c2678 & currentPos) * 4);
            if (searchValue < val0 || searchValue == val0) {
                DAT_012054b4 = currentPos + 1;
                return linearIndex;
            }

            float val1 = *(float*)(&DAT_010c2680 + (DAT_010c2678 & (currentPos + 1)) * 4);
            if (searchValue < val1 || searchValue == val1) {
                DAT_012054b4 = currentPos + 2;
                return linearIndex + 1;
            }

            float val2 = *(float*)(&DAT_010c2680 + (DAT_010c2678 & (currentPos + 2)) * 4);
            if (searchValue < val2 || searchValue == val2) {
                DAT_012054b4 = currentPos + 3;
                return linearIndex + 2;
            }

            currentPos += 4;
            float val3 = *(float*)(&DAT_010c2680 + (DAT_010c2678 & currentPos) * 4);
            if (searchValue < val3 || searchValue == val3) {
                DAT_012054b4 = currentPos + 1; // actually it sets to currentPos before increment? careful: original sets DAT_012054b4 = uVar2; (which is after +4) then returns
                // In original: DAT_012054b4 = uVar2; after the +4, so it points to next unread entry
                return linearIndex + 3;
            }

            linearIndex += 4;
            DAT_012054b4 = currentPos; // update global cursor
        } while (linearIndex < cursor - 3);
    }

    // Handle remaining entries (less than 4)
    if (linearIndex < cursor) {
        while (true) {
            uint maskedIndex = DAT_010c2678 & currentPos; // DAT_012054b4 has been set to currentPos before this loop
            float val = *(float*)(&DAT_010c2680 + maskedIndex * 4);
            DAT_012054b4 = currentPos + 1;
            if (searchValue < val || searchValue == val) {
                break; // found
            }
            linearIndex++;
            if (cursor <= linearIndex) {
                return linearIndex; // not found, return beyond end
            }
        }
    }

    return linearIndex;
}