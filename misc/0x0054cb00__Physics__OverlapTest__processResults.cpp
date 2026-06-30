// FUNC_NAME: Physics::OverlapTest::processResults
void __thiscall Physics::OverlapTest::processResults(OverlapTest* this) {
    float* pItemData;
    float* pOtherData;
    float* pOtherEnd;
    uint32_t otherFlags;
    uint32_t currentFlags;
    int32_t otherCount;
    int32_t currentIndex;
    float dotProduct1, dotProduct2;
    int32_t i;
    int32_t count;
    float threshold; // DAT_0103b23c
    uint8_t tempBuffer[1548]; // 0x60C bytes, holds up to 32 items of 0x30 bytes each
    uint8_t* tempPtr;
    int32_t tempItemCount;

    if (*(int32_t*)(this + 0x14) >= 0x21) {
        return;
    }

    tempPtr = tempBuffer;
    tempItemCount = 0;
    // Initialize iterator for temp buffer
    // FUN_00551700 appears to be a constructor or reset function for the buffer iterator
    FUN_00551700(&tempPtr);

    *(int32_t*)(this + 0x14) = 0; // reset result count
    currentIndex = 0;
    threshold = DAT_0103b23c; // likely a collision tolerance

    if (tempItemCount <= 0) {
        goto cleanup;
    }

    do {
        // Inner loop: compare current item (at offset currentIndex*0x30) against all other items in temp buffer
        i = 0;
        if (tempItemCount > 0) {
            pItemData = (float*)(tempPtr + 0x14); // point to +0x14 of first item
            do {
                if (currentIndex != i) {
                    // Check flags: other item has bit 0x40000000 set, current does not
                    otherFlags = *(uint32_t*)(pItemData + 6); // offset +0x2c
                    currentFlags = *(uint32_t*)(tempPtr + currentIndex * 0x30 + 0x2c);
                    if (((otherFlags & 0xC0000000) == 0x40000000) &&
                        ((currentFlags & 0xC0000000) != 0x40000000)) {
                        // Compute dot product test (likely plane/segment intersection)
                        // pItemData points to +0x14 of other item
                        // Access fields: pItemData[-5] = x, pItemData[-4] = y, pItemData[-3] = z,
                        // pItemData[-1] = ???, pItemData[0] = ???, pItemData[1] = ???
                        // Subtract dot product of current item components
                        float* currentItem = (float*)(tempPtr + currentIndex * 0x30);
                        dotProduct1 = pItemData[-5] * pItemData[-1] +
                                      pItemData[-3] * pItemData[1] +
                                      pItemData[-4] * pItemData[0];
                        dotProduct2 = currentItem[2] * pItemData[1] +
                                      currentItem[1] * pItemData[0] +
                                      currentItem[0] * pItemData[-1];
                        if (threshold < dotProduct1 - dotProduct2) {
                            goto skipCopy;
                        }
                    }
                }
                i++;
                pItemData += 0xC; // advance to next item's +0x14
            } while (i < tempItemCount);
        }

        // Also check against the secondary list at this+0x1c0
        if (*(int32_t*)(this + 0x1c0) != 0) {
            int32_t otherListCount = *(int32_t*)(*(int32_t*)(this + 0x1c0) + 0x14);
            if (otherListCount > 0) {
                float* otherListData = *(float**)(*(int32_t*)(this + 0x1c0) + 0x10);
                pOtherData = otherListData + 5; // offset +0x14
                i = 0;
                do {
                    otherFlags = *(uint32_t*)(pOtherData + 6); // offset +0x2c
                    if (((otherFlags & 0xC0000000) == 0x40000000) &&
                        ((*(uint32_t*)(tempPtr + currentIndex * 0x30 + 0x2c) & 0xC0000000) != 0x40000000)) {
                        float* currentItem = (float*)(tempPtr + currentIndex * 0x30);
                        dotProduct1 = pOtherData[-3] * pOtherData[1] +
                                      pOtherData[-4] * pOtherData[0] +
                                      pOtherData[-1] * otherListData[0]; // note: *otherListData[0] instead of pOtherData[-5]?
                        dotProduct2 = currentItem[2] * pOtherData[1] +
                                      currentItem[1] * pOtherData[0] +
                                      currentItem[0] * pOtherData[-1];
                        if (threshold < dotProduct1 - dotProduct2) {
                            goto skipCopy;
                        }
                    }
                    i++;
                    otherListData += 0xC;
                    pOtherData += 0xC;
                } while (i < otherListCount);
            }
        }

        // If no overlap found, copy current item into result array
        {
            uint32_t resultCount = *(uint32_t*)(this + 0x14);
            uint32_t resultCapacity = *(uint32_t*)(this + 0x18) & 0x3FFFFFFF;
            if (resultCount == resultCapacity) {
                // grow result array (size 0x30 per item)
                FUN_00aa4190((int32_t*)(this + 0x10), 0x30);
                threshold = DAT_0103b23c;
            }
            uint32_t destOffset = resultCount * 0x30;
            float* dest = (float*)(*(int32_t*)(this + 0x10) + destOffset);
            float* src = (float*)(tempPtr + currentIndex * 0x30);
            *(int32_t*)(this + 0x14) = resultCount + 1;
            // Copy 12 floats (0x30 bytes)
            for (int j = 0; j < 12; j++) {
                dest[j] = src[j];
            }
        }

skipCopy:
        currentIndex++;
    } while (currentIndex < tempItemCount);

cleanup:
    if ((int32_t)local_618 >= 0) {
        uint32_t size = (local_618 & 0x3FFFFFFF) * 0x30;
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(tempBuffer, size, 0x17);
    }
    return;
}