// FUNC_NAME: TransformCache::findOrStoreTransform
// Address: 0x00593210
// Role: Caches an 8‑float transform (e.g., bone world matrix) keyed by a float key.
//       Uses two LRU caches of 12 entries each, selected by an internal slot ID.
//       Returns a hit (copies data out) or evicts the oldest entry and stores the new data.

// Note: Offsets are relative to the 'this' pointer (assumed in EDI).
// +0x78 : m_timestamp (used to track age)
// +0x140: m_cacheA[0] (12 entries, 12 floats each)
// +0x170: m_cacheA[4] (first 4 entries may be reserved or unused? cleared on switch)
// +0x1D0: m_cacheA[12] (end)
// +0x200: m_cacheB[0]
// +0x230: m_cacheB[4]
// +0x290: m_cacheB[12]
// +0x2C0: m_activeSlotId   (which cache slot is currently active for this ID)
// +0x2C4: m_previousSlotId
// +0x2C8: m_lastUsedSlotId (set to m_slotId each call)
// +0x2CC: m_hitCount
// +0x2D0: m_frameCount

void TransformCache::findOrStoreTransform(float *outTransform, float key)
{
    int slotId = m_slotId;                    // unaff_EDI[1]
    int frameCount;
    if ((frameCount & 0xff) < 10) {
        frameCount = *(int *)(slotId + 0x10); // seems unrelated; just replicate logic
    } else {
        frameCount = *(int *)(slotId + 0x24);
    }
    if (frameCount < 0) return;

    m_frameCount++;
    slotId = m_slotId;   // re‑read
    bool useCacheA = false;
    float *cacheStart = nullptr;

    if (slotId == m_activeSlotId) {
        cacheStart = m_cacheA;   // (float *)(this + 0x140)
        useCacheA = true;
    } else if (slotId == m_previousSlotId) {
        cacheStart = m_cacheB;   // (float *)(this + 0x200)
        useCacheA = true;
        goto foundCache;
    } else if (m_lastUsedSlotId == m_activeSlotId) {
        m_previousSlotId = slotId;
        // Clear cache B (entries 4..11)
        for (float *p = m_cacheB + 4; p <= m_cacheB + 12; p += 12) {
            p[1] = -1.0f;  // set key to invalid
            p[0] = 0.0f;   // timestamp to zero
        }
        slotId = m_slotId;
        goto foundCache;
    } else {
        m_activeSlotId = slotId;
        // Clear cache A (entries 4..11)
        for (float *p = m_cacheA + 4; p <= m_cacheA + 12; p += 12) {
            p[1] = -1.0f;
            p[0] = 0.0f;
        }
        slotId = m_slotId;
        useCacheA = false;
    }

foundCache:
    m_lastUsedSlotId = m_slotId;
    if (useCacheA) {
        float *end = m_cacheA + 12;  // local_2c = this + 0x1D0
        float *bestEntry = nullptr;
        float bestTimestamp = NAN;
        float bestKey = DAT_00e2e50c; // global constant (large float)

        for (float *entry = cacheStart; entry <= end; entry += 12) {
            float timestamp = entry[0];
            float entryKey = entry[1];
            if (entryKey == key) {
                // Cache hit
                m_hitCount++;
                entry[0] = m_timestamp;   // update timestamp
                outTransform[0] = entry[4];
                outTransform[1] = entry[5];
                outTransform[2] = entry[6];
                outTransform[3] = entry[7];
                outTransform[4] = entry[8];
                outTransform[5] = entry[9];
                outTransform[6] = entry[10];
                outTransform[7] = entry[11];
                return;
            }
            if (entry[1] == 0.0f) {
                continue;
            } else {
                // Find entry with smallest timestamp (LRU candidate)
                if (bestTimestamp >= timestamp) {
                    if (timestamp == bestTimestamp && (int)entryKey < (int)bestKey) {
                        bestEntry = entry;
                        bestKey = entryKey;
                    }
                } else {
                    bestEntry = entry;
                    bestKey = entryKey;
                    bestTimestamp = timestamp;
                }
            }
        }
    }

    // Eviction path: no hit found, evict the best candidate
    FUN_0056ec90(); // eviction callback (e.g., release resources)
    float *target = bestEntry;  // local_2c from the loop, or nullptr?
    // If no candidate, target may be uninitialized; original code uses pfVar7 which is the last best.
    target[0] = m_timestamp;         // set new timestamp
    target[1] = key;                 // set key
    target[4] = outTransform[0];
    target[5] = outTransform[1];
    target[6] = outTransform[2];
    target[7] = outTransform[3];
    target[8] = outTransform[4];
    target[9] = outTransform[5];
    target[10] = outTransform[6];
    target[11] = outTransform[7];
}