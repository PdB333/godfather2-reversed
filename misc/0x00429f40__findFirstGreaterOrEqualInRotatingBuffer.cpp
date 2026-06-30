// FUNC_NAME: findFirstGreaterOrEqualInRotatingBuffer

// Global rotating search state
extern uint32_t g_rotatingSearchIndex;   // 0x012054b4
extern uint32_t g_rotatingArrayMask;     // 0x010c2678 (mask = arraySize - 1)
extern float    g_rotatingArray[];       // 0x010c2680 (circular float array, size = mask+1)

// Structure containing search parameters
struct SearchRequest {
    int     field_0;        // +0x00 (unused in this function)
    int     countPlus2;     // +0x04 (number of elements + 2, used for early exit)
    int     capacity;       // +0x08 (maximum number of elements to check)
    float   searchValue;    // +0x0C (value to search for)
};

// Performs a linear search in a circular sorted float array starting from the
// global rotating index. Finds the first element >= searchValue, then advances
// the global index past the found element.
// Returns the number of steps from the original start to the found element.
uint __fastcall findFirstGreaterOrEqualInRotatingBuffer(void* thisIgnored, SearchRequest* req)
{
    uint steps = 0;
    int limit = req->countPlus2;   // +0x04
    if ((uint)req->capacity < (uint)limit) {
        limit = req->capacity;     // clamp to capacity
    }

    uint32_t currentIndex = g_rotatingSearchIndex;

    // Unrolled loop processing 4 elements at a time
    if (limit > 3) {
        do {
            // Check first element
            float f0 = g_rotatingArray[g_rotatingArrayMask & currentIndex];
            if (req->searchValue <= f0) {
                g_rotatingSearchIndex = currentIndex + 1;
                return steps;
            }
            currentIndex += 2;

            // Check second element
            float f1 = g_rotatingArray[g_rotatingArrayMask & (currentIndex - 1)];
            if (req->searchValue <= f1) {
                g_rotatingSearchIndex = currentIndex;
                return steps + 1;
            }
            currentIndex += 1;

            // Check third element
            float f2 = g_rotatingArray[g_rotatingArrayMask & (currentIndex - 1)];
            if (req->searchValue <= f2) {
                g_rotatingSearchIndex = currentIndex;
                return steps + 2;
            }
            currentIndex += 1;

            // Check fourth element
            float f3 = g_rotatingArray[g_rotatingArrayMask & (currentIndex - 1)];
            if (req->searchValue <= f3) {
                g_rotatingSearchIndex = currentIndex;
                return steps + 3;
            }

            steps += 4;
            g_rotatingSearchIndex = currentIndex;
        } while (steps <= (uint)(limit - 4));
    }

    // Handle remaining 0-3 elements (tail loop)
    while (steps < (uint)limit) {
        uint32_t idx = g_rotatingArrayMask & g_rotatingSearchIndex;
        g_rotatingSearchIndex++;

        float f = g_rotatingArray[idx];
        if (req->searchValue <= f) {
            break;
        }
        steps++;
    }

    return steps;
}