// FUNC_NAME: UtilityAISystem::evaluateAndSelectActions

#include <string.h> // for memset

// Global constants (likely from config/data)
// DAT_00e2b1a4: maximum interest weight threshold? 0.0 < value
// DAT_00e2d7fc: minimum weight to store? (fVar9)
// DAT_00e44598: total weight sum threshold for normalization
// DAT_00e2af44: global min threshold to clear selection
// DAT_00e2eff4: initial best score (local_84)

// Global arrays (likely part of AI scoring manager singleton)
// DAT_01219859: global enable flag (byte)
// DAT_01219858: number of active AI evaluation items (uint)
// DAT_01219688: array of ints (32 entries) - type/category for each item (-1 means inactive)
// DAT_01219708: array of floats (32 entries) - current "value" for ratio numerator 1
// DAT_01219788: array of floats (32 entries) - current "value" for ratio numerator 2
// DAT_01219398: array of 6-float blocks (32 entries) - evaluation parameters for each item:
//   struct EvalParams { float weightMultiplier;  // offset -4 (maybe)
//                       float typeWeight;        // offset -3
//                       float unknown;           // offset -2 (not used in this function)
//                       int    flags;            // offset -1 (bitmask, bit 28 = abort flag)
//                       float denominator1;      // offset 0
//                       float denominator2;      // offset 4
//                     } * 6 floats?
//                  Actually pfVar4 points to denominator1 (offset 0) of each item block.
//                  So pfVar4[-1] = flags, pfVar4[-2] = unknown, pfVar4[-3] = typeWeight, pfVar4[-4] = weightMultiplier
//                  Block size = 6 floats = 24 bytes.

// DAT_0121930c: array of uint (32 entries) - selected item indices (output)
// DAT_01219328: array of float (32 entries) - selected item scores (output)
// DAT_01219324: [float, float?] - first element is maxScore, second is ??? (CONCAT with local_84)
// DAT_01219344: count of selected items (uint)

// DAT_011a0f28: array of some object (size 0x38 per entry, up to 0x1000 entries) - for activation
// DAT_011a0f44: pointer to another object? (offset 0x1C from base)

// Callees: FUN_00606e60 (maybe set flag on object), FUN_006189c0 (re-evaluate something)

uint UtilityAISystem::evaluateAndSelectActions()
{
    int iVar1;
    byte enableFlag = *DAT_01219859;
    uint selectedCount = 0;

    // Reset output arrays
    *DAT_0121930c = 0;
    *DAT_01219314 = 0;
    *DAT_0121931c = 0;
    *DAT_01219324 = 0;
    *DAT_0121932c = 0;
    *DAT_01219334 = 0;
    *DAT_0121933c = 0;
    *DAT_01219344 = 0;

    // If globally disabled, clear state and return 0
    if (enableFlag == 0) {
        *((uint*)DAT_01219390) &= 0xefffffff;  // clear bit 28 in some global
        return 0;
    }

    uint numItems = *DAT_01219858;
    uint itemIdx = 0;
    float bestScore = *DAT_00e2eff4;  // initial best score (a very large/small value?)

    // First pass: find maximum score among all valid items
    float* paramPtr = (float*)DAT_01219398; // points to denominator1 of first item
    while (itemIdx < numItems && itemIdx <= 0x1f) { // up to 32 items (0x7f / 4 = 0x1f)
        int flags = *(int*)(paramPtr - 1);  // paramPtr[-1] = flags
        if (flags & 0x10000000) {  // check abort flag
            *DAT_01219344 = 0;
            return 0;
        }

        int categoryIndex = *(int*)(DAT_01219688 + itemIdx * 4);  // int array
        if (categoryIndex >= 0) {
            float denominator1 = *paramPtr;
            float current1 = *(float*)(DAT_01219708 + itemIdx * 4);
            float ratio1 = (denominator1 != 0.0f) ? (current1 / denominator1) : 0.0f;

            float denominator2 = *(paramPtr + 1);
            float current2 = *(float*)(DAT_01219788 + itemIdx * 4);
            float ratio2 = (denominator2 != 0.0f) ? (current2 / denominator2) : 0.0f;

            // Compute score = (maxInterest - ratio1) * weight * ratio2
            float weightMult = *(paramPtr - 4);  // weightMultiplier
            float score = (*DAT_00e2b1a4 - ratio1) * weightMult * ratio2;
            if (score > bestScore) {
                bestScore = score;
            }
        }
        itemIdx++;
        paramPtr += 6; // advance to next item's parameter block
    }

    // Second pass: accumulate scores into category buckets and compute total
    float categoryScores[32];
    memset(categoryScores, 0, sizeof(categoryScores));

    float totalScore = 0.0f;
    float minScore = *DAT_00e2d7fc;  // threshold to consider storing an option

    paramPtr = (float*)DAT_01219398;
    itemIdx = 0;
    uint processedItems = 0;
    while (processedItems < numItems && itemIdx <= 0x1f) {
        int categoryIndex = *(int*)(DAT_01219688 + itemIdx * 4);
        if (categoryIndex >= 0) {
            float denominator1 = *paramPtr;
            float current1 = *(float*)(DAT_01219708 + itemIdx * 4);
            float ratio1 = (denominator1 != 0.0f) ? (current1 / denominator1) : 0.0f;

            float denominator2 = *(paramPtr + 1);
            float current2 = *(float*)(DAT_01219788 + itemIdx * 4);
            float ratio2 = (denominator2 != 0.0f) ? (current2 / denominator2) : 0.0f;

            float weightMult = *(paramPtr - 4);
            float typeWeight = *(paramPtr - 3);
            float score = typeWeight * (*DAT_00e2b1a4 - ratio1) * weightMult * ratio2;
            totalScore += score;
            categoryScores[categoryIndex] += score;  // accumulate into category bucket
            processedItems++;
        }
        itemIdx++;
        paramPtr += 6;
    }

    // Normalize and filter if total score is above a threshold
    if (*DAT_00e44598 < totalScore) {
        float invTotal = *DAT_00e2b1a4 / totalScore;  // 1.0 / total? Actually DAT_00e2b1a4 may be 1.0
        // Reset selected count for new selection
        selectedCount = 0;
        if (enableFlag != 0) {
            float* bucketPtr = categoryScores;
            for (uint catIdx = 0; catIdx < 0x100 && catIdx <= 0xff; catIdx += 1) {
                if (*(int*)(DAT_0121982c + catIdx * 4) != 0) {  // some flag for category
                    float normalizedScore = *bucketPtr * invTotal;
                    *bucketPtr = normalizedScore;
                    if (normalizedScore > minScore) {
                        // Store the category ID and its score
                        uint categoryId = *(uint*)(DAT_01219828 + catIdx * 4);
                        *(uint*)(DAT_0121930c + selectedCount * 4) = categoryId;
                        if (normalizedScore < 0.0f) {
                            normalizedScore = 0.0f;
                        } else if (normalizedScore > *DAT_00e2b1a4) {
                            normalizedScore = *DAT_00e2b1a4;
                        }
                        *(float*)(DAT_01219328 + selectedCount * 4) = normalizedScore;
                        selectedCount++;
                    }
                }
                bucketPtr++;
            }
        }
        // Store the max score as part of a paired value (CONCAT)
        *(float*)DAT_01219324 = bestScore;  // first part
        // second part? Was stored via CONCAT44? Actually line: _DAT_01219324 = CONCAT44(DAT_01219328, local_84);
        // This is messy. Probably a bug in decompilation. We'll store bestScore at the start and the first selected score at the next word.
        // Assuming DAT_01219324 is a struct {float maxScore; float firstSelectedScore; } or similar.
        // For now, skip the CONCAT nonsense and just assign bestScore.
        *(uint*)DAT_01219324 = *(uint*)&bestScore; // low part
    }

    // If no score exceeds the absolute threshold, clear selection
    if (*(float*)DAT_01219324 < *DAT_00e2af44) {
        *DAT_01219344 = 0;
        selectedCount = 0;
    }

    uint finalCount = *DAT_01219344;
    if (finalCount != 0) {
        for (uint selIdx = 0; selIdx < finalCount; selIdx++) {
            uint elementId = *(uint*)(DAT_0121930c + selIdx * 4);
            if (elementId != 0xffffffff && elementId < 0x1000) {
                uint baseOffset = elementId * 0x38;  // 0x38 bytes per object
                byte* obj = (byte*)(DAT_011a0f28 + baseOffset);
                if (obj != (byte*)0x0 && obj[0] < 4) {  // some state enum
                    void* ptr = *(void**)(DAT_011a0f44 + baseOffset);  // pointer at offset 0x1C (0x44-0x28=0x1C)
                    if (ptr != 0) {
                        FUN_00606e60(ptr, 0x200000);  // set a flag (0x200000)
                    }
                    *(uint*)(DAT_011a0f34 + baseOffset) = (*(uint*)(DAT_011a0f34 + baseOffset) & 0xfcac8fff) | 0x200000;
                    FUN_006189c0();  // re-evaluate or queue update
                }
            }
        }
    }

    return finalCount;
}