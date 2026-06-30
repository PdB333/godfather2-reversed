// FUNC_NAME: WeightedRandomSelector::selectRandomItem
int WeightedRandomSelector::selectRandomItem(void)
{
    float weight;
    int* pData;
    bool bWithinRange;
    int i;
    int keyField2;
    int keyField3;
    int collectedCount;
    int* pNode;
    float accumulatedWeight;
    float randomValue;
    int collectedItems[30]; // max 30 candidates

    accumulatedWeight = 0.0f;
    collectedCount = 0;
    randomValue = 0.0f;

    if (g_pItemListHead != 0) {
        keyField3 = this->field_0x0c; // +0x0C: third key field
        keyField2 = this->field_0x08; // +0x08: second key field
        pNode = g_pItemListHead;
        do {
            pData = *(int**)(pNode + 0x28); // pointer to data block at +0x28
            // Compare four key fields: this[0], this[4], this[8], this[12] with data[0..3]
            if ((((keyField2 == pData[2]) && (keyField3 == pData[3])) && (this->field_0x00 == *pData)) &&
               ((this->field_0x04 == pData[1] && (weight = (float)pData[4], 0.0f < weight)))) {
                if (0x1d < collectedCount) break; // max 30 items
                collectedItems[collectedCount] = pNode;
                randomValue = weight + randomValue; // sum weights
                collectedCount = collectedCount + 1;
            }
            pNode = *(int*)(pNode + 0x24); // next node in linked list
        } while (pNode != 0);

        if (collectedCount != 0) {
            // Update RNG state (linear congruential generator)
            i = g_rngIndex - 1;
            int j = g_rngIndex + 2;
            if (i < 0) {
                i = 0x13; // wrap around (19)
            }
            else if (0x13 < j) {
                j = g_rngIndex - 0x12; // wrap around (19)
            }
            g_rngState[i] = g_rngState[i] + g_rngState[j];
            g_rngIndex = i;

            // Convert integer to float in [0,1) by extracting mantissa and subtracting 1.0
            // (g_rngState[i] & 0x7fffff | 0x3f800000) gives float in [1.0, 2.0)
            // Subtract 1.0f (DAT_00e2b1a4) to get [0.0, 1.0)
            float normalized = (float)(g_rngState[i] & 0x7fffff | 0x3f800000) - 1.0f;
            float scaledRandom = normalized * randomValue; // random value in [0, totalWeight)

            // Weighted selection
            accumulatedWeight = 0.0f;
            for (int idx = 0; idx < collectedCount; idx++) {
                bWithinRange = (accumulatedWeight <= scaledRandom);
                accumulatedWeight = accumulatedWeight + *(float*)(*(int*)(collectedItems[idx] + 0x28) + 0x10); // weight at data+0x10
                if (bWithinRange && (scaledRandom < accumulatedWeight)) {
                    return collectedItems[idx];
                }
            }
        }
    }
    return 0;
}