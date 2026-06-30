// FUNC_NAME: ReputationManager::accumulateScores
float __thiscall ReputationManager::accumulateScores(ScoreBuffer* buffer, int* outCategoryCount) {
    *outCategoryCount = 0;

    int currentIndex = buffer->endIndex;
    int startIndex = buffer->startIndex;
    float* categoryKeyArray = &accumulatedScores[2]; // points to key field of first triple
    uint numCategories = 0;
    float* pKeyPtr = categoryKeyArray;

    while (currentIndex != startIndex) {
        ScoreEntry* entry = &buffer->entries[currentIndex];
        if (entry->id != 0) {
            float categoryKey = (float)(entry->id - 0x48);
            if (categoryKey != 0.0f) {
                bool found = false;
                uint i = 0;
                // Check existing categories (optimized loop for first 4)
                if (numCategories > 3) {
                    int blockCount = ((numCategories - 4) >> 2) + 1;
                    float* pCat = accumulatedScores; // base of triples
                    uint processed = blockCount * 4;
                    do {
                        if (pCat[-3] == categoryKey) {
                            pCat[-5] += (float)entry->score;
                            found = true;
                        }
                        if (*pCat == categoryKey) {
                            pCat[-2] += (float)entry->score;
                            found = true;
                        }
                        if (pCat[3] == categoryKey) {
                            pCat[1] += (float)entry->score;
                            found = true;
                        }
                        if (pCat[6] == categoryKey) {
                            pCat[4] += (float)entry->score;
                            found = true;
                        }
                        pCat += 12; // 4 triples * 3 floats
                        blockCount--;
                        pKeyPtr = categoryKeyArray;
                    } while (blockCount != 0);
                }
                // Check remaining categories
                if (processed < numCategories) {
                    float* pRem = &accumulatedScores[processed * 3];
                    int remaining = numCategories - processed;
                    do {
                        if (pRem[2] == categoryKey) {
                            *pRem += (float)entry->score;
                            found = true;
                        }
                        pRem += 3;
                        remaining--;
                        pKeyPtr = categoryKeyArray;
                    } while (remaining != 0);
                }
                // If not found, add new category
                if (!found) {
                    (*outCategoryCount)++;
                    pKeyPtr[-2] = (float)entry->score; // accumulated sum
                    *pKeyPtr = categoryKey; // key
                    pKeyPtr[-1] = (float)entry; // pointer to entry (for debugging?)
                    numCategories++;
                    pKeyPtr += 3;
                    categoryKeyArray = pKeyPtr;
                }
            }
        }
        // Move to next index, wrap around
        currentIndex++;
        if (currentIndex >= buffer->capacity) {
            currentIndex = 0;
        }
    }

    // Find category with maximum accumulated sum
    float bestKey = 0.0f;
    uint processed = 0;
    float bestSum = g_minScoreThreshold; // corresponds to DAT_00e44758

    if (numCategories > 3) {
        int blockCount = ((numCategories - 4) >> 2) + 1;
        float* pCat = &accumulatedScores[4]; // point to sum of first triple? Actually base at local_e0 equivalent
        processed = blockCount * 4;
        do {
            if (bestSum < pCat[-4]) {
                bestKey = pCat[-3];
                bestSum = pCat[-4];
            }
            if (bestSum < pCat[-1]) {
                bestKey = *pCat;
                bestSum = pCat[-1];
            }
            if (bestSum < pCat[2]) {
                bestKey = pCat[3];
                bestSum = pCat[2];
            }
            if (bestSum < pCat[5]) {
                bestKey = pCat[6];
                bestSum = pCat[5];
            }
            pCat += 12;
            blockCount--;
        } while (blockCount != 0);
    }
    if (processed < numCategories) {
        int remaining = numCategories - processed;
        float* pRem = &accumulatedScores[processed * 3];
        do {
            if (bestSum < *pRem) {
                bestKey = pRem[1];
                bestSum = *pRem;
            }
            pRem += 3;
            remaining--;
        } while (remaining != 0);
    }
    return bestKey;
}