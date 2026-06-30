// FUNC_NAME: EntitySpatialQuery::findNearestInRange
float __thiscall EntitySpatialQuery::findNearestInRange(int thisPtr, const float* position, int* outEntity, int filterType1, int filterType2, bool useOrMode)
{
    uint32_t count = *(uint32_t*)(thisPtr + 0x38);               // number of entries
    uint32_t index = 0;
    float bestDistSq = DAT_00d5ccf8;                             // large initial distance (e.g., FLT_MAX)
    int bestEntity = 0;

    // Pointer to the array of 8‑byte records: each record holds an entity pointer (at offset 0) and unknown data.
    int* recordPtr = (int*)(*(int*)(thisPtr + 0x34) + 0xc);      // +0x34: base of array, +0xc: start of first record?

    // Process records in batches of 4 (unrolled)
    if (count > 3) {
        int remaining = (count - 4) / 4 + 1;
        index = remaining * 4;
        do {
            // First record in batch: at recordPtr[-2] (i.e., offset -8 bytes)
            int entity0 = recordPtr[-2];
            int* meta0 = (int*)*(int*)(entity0 + 0xfc);          // +0xfc: pointer to metadata/type info
            if (meta0 != 0) {
                bool passType1 = false;
                if (filterType1 == 0 || filterType1 == *(int*)(meta0 + 0x14)) {
                    passType1 = true;
                } else if (!useOrMode) {
                    goto skip_entity0;
                }
                // Condition: either type2 matches, or (useOrMode && passType1)
                bool matches = (filterType2 == 0 || filterType2 == *(int*)(meta0 + 0x18)) || (useOrMode && passType1);
                if (matches) {
                    float dx = position[0] - *(float*)(entity0 + 0x10);
                    float dy = position[1] - *(float*)(entity0 + 0x14);
                    float dz = position[2] - *(float*)(entity0 + 0x18);
                    float distSq = dz*dz + dy*dy + dx*dx;
                    if (distSq < bestDistSq || bestEntity == 0) {
                        bestDistSq = distSq;
                        bestEntity = entity0;
                    }
                }
            }
skip_entity0:
            // Second record: recordPtr[0]
            int entity1 = recordPtr[0];
            int* meta1 = (int*)*(int*)(entity1 + 0xfc);
            if (meta1 != 0) {
                bool passType1 = false;
                if (filterType1 == 0 || filterType1 == *(int*)(meta1 + 0x14)) {
                    passType1 = true;
                } else if (!useOrMode) {
                    goto skip_entity1;
                }
                bool matches = (filterType2 == 0 || filterType2 == *(int*)(meta1 + 0x18)) || (useOrMode && passType1);
                if (matches) {
                    float dx = position[0] - *(float*)(entity1 + 0x10);
                    float dy = position[1] - *(float*)(entity1 + 0x14);
                    float dz = position[2] - *(float*)(entity1 + 0x18);
                    float distSq = dz*dz + dy*dy + dx*dx;
                    if (distSq < bestDistSq || bestEntity == 0) {
                        bestDistSq = distSq;
                        bestEntity = entity1;
                    }
                }
            }
skip_entity1:
            // Third record: recordPtr[2]
            int entity2 = recordPtr[2];
            int* meta2 = (int*)*(int*)(entity2 + 0xfc);
            if (meta2 != 0) {
                bool passType1 = false;
                if (filterType1 == 0 || filterType1 == *(int*)(meta2 + 0x14)) {
                    passType1 = true;
                } else if (!useOrMode) {
                    goto skip_entity2;
                }
                bool matches = (filterType2 == 0 || filterType2 == *(int*)(meta2 + 0x18)) || (useOrMode && passType1);
                if (matches) {
                    float dx = position[0] - *(float*)(entity2 + 0x10);
                    float dy = position[1] - *(float*)(entity2 + 0x14);
                    float dz = position[2] - *(float*)(entity2 + 0x18);
                    float distSq = dz*dz + dy*dy + dx*dx;
                    if (distSq < bestDistSq || bestEntity == 0) {
                        bestDistSq = distSq;
                        bestEntity = entity2;
                    }
                }
            }
skip_entity2:
            // Fourth record: recordPtr[4]
            int entity3 = recordPtr[4];
            int* meta3 = (int*)*(int*)(entity3 + 0xfc);
            if (meta3 != 0) {
                bool passType1 = false;
                if (filterType1 == 0 || filterType1 == *(int*)(meta3 + 0x14)) {
                    passType1 = true;
                } else if (!useOrMode) {
                    goto skip_entity3;
                }
                bool matches = (filterType2 == 0 || filterType2 == *(int*)(meta3 + 0x18)) || (useOrMode && passType1);
                if (matches) {
                    float dx = position[0] - *(float*)(entity3 + 0x10);
                    float dy = position[1] - *(float*)(entity3 + 0x14);
                    float dz = position[2] - *(float*)(entity3 + 0x18);
                    float distSq = dz*dz + dy*dy + dx*dx;
                    if (distSq < bestDistSq || bestEntity == 0) {
                        bestDistSq = distSq;
                        bestEntity = entity3;
                    }
                }
            }
skip_entity3:
            recordPtr += 8;                                      // advance by 8 ints (32 bytes) – 4 records × 8 bytes per record
            --remaining;
        } while (remaining != 0);
    }

    // Process remaining records individually
    if (index < count) {
        recordPtr = (int*)(*(int*)(thisPtr + 0x34) + 4 + index * 8); // adjust pointer to start at the first unprocessed record
        int remaining = count - index;
        do {
            int entity = recordPtr[0];
            int* meta = (int*)*(int*)(entity + 0xfc);
            if (meta != 0) {
                bool passType1 = false;
                if (filterType1 == 0 || filterType1 == *(int*)(meta + 0x14)) {
                    passType1 = true;
                } else if (!useOrMode) {
                    goto skip_entity;
                }
                bool matches = (filterType2 == 0 || filterType2 == *(int*)(meta + 0x18)) || (useOrMode && passType1);
                if (matches) {
                    float dx = position[0] - *(float*)(entity + 0x10);
                    float dy = position[1] - *(float*)(entity + 0x14);
                    float dz = position[2] - *(float*)(entity + 0x18);
                    float distSq = dz*dz + dy*dy + dx*dx;
                    if (distSq < bestDistSq || bestEntity == 0) {
                        bestDistSq = distSq;
                        bestEntity = entity;
                    }
                }
            }
skip_entity:
            recordPtr += 2;                                      // advance 2 ints (8 bytes) to next record
            --remaining;
        } while (remaining != 0);
    }

    if (outEntity != nullptr) {
        *outEntity = bestEntity;
    }
    return bestDistSq;
}