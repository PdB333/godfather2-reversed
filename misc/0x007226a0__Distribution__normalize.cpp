// FUNC_NAME: Distribution::normalize
// Address: 0x007226a0
// Role: Normalizes a weight array so that the sum equals a global target value (g_targetSum).
// The function processes variable-length float arrays (up to 9 elements, as offset 0x24 is the total field).
// Uses manual unrolling for performance (batches of 4 floats).

#include <cstdint>

// Global constant (typically 1.0f)
extern float g_targetSum; // _DAT_00d5780c

// Structure assumed: offset 0 = float weights[0..count-1], offset 0x24 = float total (only written when sum is zero)
void Distribution::normalize(float* weights, int count) {
    float sum = 0.0f;
    int i = 0;

    // Unrolled summation for count > 3
    if (count > 3) {
        int iter = (count - 4) / 4 + 1;
        float* p = weights + 2; // start at offset +8 bytes (2 floats from start)
        i = iter * 4;
        do {
            sum += p[-2] + p[-1] + p[0] + p[1];
            p += 4;
            --iter;
        } while (iter != 0);
    }

    // Remaining elements
    for (; i < count; ++i) {
        sum += weights[i];
    }

    // If sum is zero, set the total field to target and return (no normalization)
    if (sum == 0.0f) {
        // Offset 0x24 = float at weights[9] (if count <= 9)
        *reinterpret_cast<float*>(reinterpret_cast<char*>(weights) + 0x24) = g_targetSum;
        return;
    }

    // If sum equals target, no change needed
    if (sum != g_targetSum) {
        float scale = g_targetSum / sum;

        // Unrolled normalization for count > 3
        i = 0;
        if (count > 3) {
            int iter = (count - 4) / 4 + 1;
            float* p = weights + 2;
            i = iter * 4;
            do {
                p[-2] *= scale;
                p[-1] *= scale;
                p[0] *= scale;
                p[1] *= scale;
                p += 4;
                --iter;
            } while (iter != 0);
        }

        // Remaining elements
        for (; i < count; ++i) {
            weights[i] *= scale;
        }
    }
}