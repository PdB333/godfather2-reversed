// FUNC_NAME: InputSmoother::updateSmoothing

// Function address: 0x00788720
// Role: Computes a weighted average of input samples stored in a linked list, 
//       applies smoothing based on a global flag (simple average vs. time-weighted average).
//       Then checks time threshold for resetting sample index or logging.
// Struct offsets:
//   param_1+0x00: head pointer to linked list of InputSample nodes
//   param_1+0x10: accumulated smoothed X (float)
//   param_1+0x14: accumulated smoothed Y (float)
//   param_1+0x18: accumulated smoothed Z (float)
//   param_1+0x20: threshold time (float)
//   param_1+0x24: state float (e.g., current level)
//   param_1+0x30: sample index (int, -1 if idle)
// Node offsets:
//   node+0x00: next pointer
//   node+0x08: weight/time delta (float)
//   node+0x0C: sample X (float)
//   node+0x10: sample Y (float)
//   node+0x14: sample Z (float)

struct InputSample {
    InputSample* next;
    float weight;   // +0x08
    float sampleX;  // +0x0C
    float sampleY;  // +0x10
    float sampleZ;  // +0x14
};

// Global flags and data (external)
extern bool g_useWeightedSmoothing;     // DAT_00e527a8
extern float g_baseWeight;              // _DAT_00d5780c
extern float g_thresholdLow;            // _DAT_00d577a0
extern float g_highStateValue;          // DAT_01205228
extern float g_lowStateValue;           // DAT_00d5ccf8
extern uint32_t* g_gameManager;        // DAT_0112aa1c
extern bool g_allowReset;              // DAT_0112af90

// Forward declarations of called functions
float __fastcall getGameTime();                // FUN_00785780
void __fastcall resetSmoothing(void* this);   // FUN_007857b0
void __fastcall debugLog(int level);          // FUN_00788130
void __fastcall releaseSampleIndex(int idx);  // FUN_009450b0
float __fastcall getDeltaTime();              // FUN_00786660

void __fastcall InputSmoother::updateSmoothing(void* this) {
    InputSample* node;
    float sumWeights = 0.0f;
    float sumX = 0.0f, sumY = 0.0f, sumZ = 0.0f;
    bool useWeighted = !g_useWeightedSmoothing;  // invert because flag checked for zero

    // Clear accumulators
    ((float*)this)[4] = 0.0f;  // +0x10
    ((float*)this)[5] = 0.0f;  // +0x14
    ((float*)this)[6] = 0.0f;  // +0x18

    float baseWeight = g_baseWeight;

    if (useWeighted) {
        // Simple average: all samples equally weighted
        node = *(InputSample**)this;  // +0x00
        while (node) {
            sumX += node->sampleX;
            sumY += node->sampleY;
            sumZ += node->sampleZ;
            sumWeights += baseWeight;
            node = node->next;
        }
        if (sumWeights > 0.0f) {
            float invWeight = baseWeight / sumWeights;
            ((float*)this)[4] = sumX * invWeight;
            ((float*)this)[5] = sumY * invWeight;
            ((float*)this)[6] = sumZ * invWeight;
        }
    } else {
        // Weighted average based on sample->weight (e.g., time delta or importance)
        float minWeight = g_baseWeight;  // actually from _DAT_00d5f6f0 (maybe different global)
        // But note: the code uses _DAT_00d5f6f0 for min, but in the decompiled it's fVar11 = DAT_00d5f6f0;
        // This should be a different global, let's assume it's g_minWeight.
        extern float g_minWeight;  // DAT_00d5f6f0

        // First pass: find min weight and total weight sum
        node = *(InputSample**)this;
        float totalWeight = 0.0f;
        while (node) {
            totalWeight += node->weight;
            if (node->weight < g_minWeight) {
                g_minWeight = node->weight;
            }
            node = node->next;
        }
        float adjustedSum = totalWeight - (totalWeight/*? actually number of nodes?*/) * g_minWeight;
        // Wait: the code uses: fVar8 = fVar8 - fVar10 * fVar11; where fVar10 is count? 
        // Actually the loop increments fVar10 with baseWeight each iteration, so fVar10 becomes count*baseWeight.
        // So fVar8 = sumWeights - fVar10 * minWeight
        // Let's get correct count from baseweight accumulation:
        // They use fVar10 = fVar10 + _DAT_00d5780c; so it accumulates baseWeight per node.
        // That means fVar10 = count * baseWeight.
        // So adjustedSum = totalWeight - (count*baseWeight) * minWeight

        // But we don't have count easily. Instead we can use totalWeight from baseWeight accumulation.
        // However, node->weight is not baseWeight; it's separate. So they compute sum of node[2] (which is weight field), 
        // and also accumulate baseWeight count. That's messy. For reconstruction, we'll follow the assembly spirit.
        // Actually looking at the decompiled: fVar8 = sum of node[2]; then fVar10 = count * baseWeight (accumulated baseWeight per node). 
        // So adjustedSum = sumWeights - fVar10 * minWeight.
        // So we need count*baseWeight*minWeight.

        // I'll replicate with a count variable.
        node = *(InputSample**)this;
        float sumWeightsNode = 0.0f;
        float sumBase = 0.0f;
        float minW = g_minWeight;
        int count = 0;
        while (node) {
            sumWeightsNode += node->weight;
            sumBase += baseWeight;
            if (node->weight < minW) {
                minW = node->weight;
            }
            node = node->next;
            count++;
        }
        float denom = sumWeightsNode - sumBase * minW;
        // Now second pass: compute weighted average
        node = *(InputSample**)this;
        while (node) {
            float w = (denom != 0.0f) ? ((node->weight - minW) / denom) : baseWeight;
            sumX += node->sampleX * w;
            sumY += node->sampleY * w;
            sumZ += node->sampleZ * w;
            node = node->next;
        }
        ((float*)this)[4] = sumX;
        ((float*)this)[5] = sumY;
        ((float*)this)[6] = sumZ;
    }

    // Time threshold check
    float gameTime = getGameTime();
    float threshold = ((float*)this)[8];  // +0x20
    if (threshold <= gameTime) {
        // Timeout: reset sample index if game manager allows
        if (*(int*)(g_gameManager + 0x2c88) != 0) {
            resetSmoothing(this);
        }
        if (((int*)this)[0xc] != -1) { // +0x30
            if (g_allowReset) {
                releaseSampleIndex(((int*)this)[0xc]);
            }
            ((int*)this)[0xc] = -1;
        }
    } else {
        debugLog(1);
    }

    // Another condition: adjust state value based on time and threshold
    float stateValue = ((float*)this)[9]; // +0x24
    float lowThreshold = g_thresholdLow; // _DAT_00d577a0
    if (stateValue <= lowThreshold) {
        float delta = getDeltaTime();
        if (delta <= threshold) {
            uint32_t flags = *(uint32_t*)(g_gameManager + 0x2c6c);
            if ((flags >> 6) & 1) {
                // bit 6 set: use low state value
                ((float*)this)[9] = g_lowStateValue; // DAT_00d5ccf8
            } else {
                ((float*)this)[9] = g_highStateValue; // DAT_01205228
            }
        }
    }
}