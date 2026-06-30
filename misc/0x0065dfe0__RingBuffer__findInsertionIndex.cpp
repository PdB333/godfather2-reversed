// FUNC_NAME: RingBuffer::findInsertionIndex
// Based on decompilation at address 0x0065dfe0
// This function performs a linear probe into a float ring buffer using a rotating global index.
// It returns the first index where the stored value <= searchValue, advancing the global probe pointer.
// The buffer is assumed to be circular with size derived from constant mask.

// Global state for the probing mechanism
static unsigned int g_probeIndex = 0;             // DAT_012054b4 - rotating start index
static const unsigned int g_mask = 0x...;          // DAT_010c2678 - mask (constant, e.g. size-1)
static float* g_buffer = (float*)0x010c2680;       // DAT_010c2680 - float array

struct SearchParams {
    int    field_4;    // +0x04 - some limit or hint (used as base + 2)
    unsigned int field_8;    // +0x08 - count of elements to consider
    float  field_0C;   // +0x0C - value to search for (must be <= stored value)
};

// __fastcall: param_1 (ecx) unused, param_2 (edx) points to SearchParams
unsigned int __fastcall RingBuffer_findInsertionIndex(void* unused, SearchParams* params)
{
    unsigned int count = params->field_4 + 2;          // offset+2, maybe to account for unrolling padding
    if (params->field_8 < count) {
        count = params->field_8;                       // clamp to actual count
    }

    unsigned int startIdx = g_probeIndex;
    unsigned int resultIdx = 0;

    // Main loop unrolled 4 times
    if (count > 3) {
        do {
            // Check slot at (g_mask & startIdx)
            if (params->field_0C <= g_buffer[g_mask & startIdx]) {
                g_probeIndex = startIdx + 1;
                return resultIdx;
            }
            g_probeIndex = startIdx + 2;

            // Check slot at (g_mask & (startIdx+1))
            if (params->field_0C <= g_buffer[g_mask & (startIdx + 1)]) {
                return resultIdx + 1;
            }
            g_probeIndex = startIdx + 3;

            // Check slot at (g_mask & (startIdx+2))
            if (params->field_0C <= g_buffer[g_mask & (startIdx + 2)]) {
                return resultIdx + 2;
            }
            startIdx += 4;

            // Check slot at (g_mask & g_probeIndex)  (g_probeIndex = startIdx+3 before increment)
            if (params->field_0C <= g_buffer[g_mask & g_probeIndex]) {
                g_probeIndex = startIdx;   // actual start after increment
                return resultIdx + 3;
            }
            g_probeIndex = startIdx;
            resultIdx += 4;
        } while (resultIdx < count - 3);
    }

    // Handle remaining elements (0-3)
    if (resultIdx < count) {
        while (true) {
            unsigned int idx = g_mask & g_probeIndex;
            g_probeIndex = g_probeIndex + 1;
            if (params->field_0C <= g_buffer[idx]) {
                break;
            }
            resultIdx++;
            if (count <= resultIdx) {
                return resultIdx;
            }
        }
    }
    return resultIdx;
}