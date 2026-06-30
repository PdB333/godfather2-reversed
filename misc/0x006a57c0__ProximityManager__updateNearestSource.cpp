// FUNC_NAME: ProximityManager::updateNearestSource
void __fastcall ProximityManager::updateNearestSource()
{
    // Offset mapping (this):
    // +0x14: float listenerX
    // +0x18: float listenerY
    // +0x1c: float listenerZ
    // +0x24: SourceInfo sources[32] (each 40 bytes)
    // +0x520: int sourceCount
    // +0x524: SourceInfo* pBestSource (linked list head)
    // +0x528: SourceInfo* pBestSourcePrev (previous for list removal)
    // +0x52c: void* pBestSourceData
    // +0x530: int bestSourceNode
    // +0x534: int bestSourceID
    // +0x694: SourceInfo* pFocusedSource

    SourceInfo* pBest = *(SourceInfo**)(this + 0x524);
    int prevBestID = pBest ? (int)pBest - 0x48 : 0; // original last best source ID
    int newBestID = 0;
    void* newBestData = nullptr;
    int newBestNode = 0;

    // Check if there is a focused source (hard override)
    SourceInfo* pFocused = *(SourceInfo**)(this + 0x694);
    if (pFocused == nullptr || (int)pFocused == 0x48)
    {
        // No focused source: scan all sources, compute distances, find nearest
        // Clear old best source if it exists
        if (*pBest)
        {
            FUN_004daf90((int*)pBest);
            *pBest = 0;
        }

        SourceInfo* pSrc = (SourceInfo*)(this + 0x24);
        int count = *(int*)(this + 0x520);
        int idx = 0;
        int written = 0; // tracks how many sources have been processed (max count)

        // Process sources in groups of 8 (hand-unrolled)
        while (idx < 0x20 && written < count) // max 32 sources
        {
            // Group of 8 sources (each block processes one source)
            #define PROCESS_SOURCE(offset) \
                if (written < count) { \
                    SourceInfo* cur = (SourceInfo*)((int*)pSrc + offset); \
                    if (cur->active != 0 && cur->active != 0x48) { \
                        float dx = cur->posX - *(float*)(this + 0x14); \
                        float dy = cur->posY - *(float*)(this + 0x18); \
                        float dz = cur->posZ - *(float*)(this + 0x1c); \
                        cur->distanceWeighted = (dx*dx + dy*dy + dz*dz) * cur->weight; \
                        written++; \
                    } \
                }

            PROCESS_SOURCE(0)   // source 0
            if (written >= count) break;
            PROCESS_SOURCE(10)  // source 1 (10 ints offset)
            if (written >= count) break;
            PROCESS_SOURCE(20)  // source 2
            if (written >= count) break;
            PROCESS_SOURCE(30)  // source 3
            if (written >= count) break;
            PROCESS_SOURCE(40)  // source 4
            if (written >= count) break;
            PROCESS_SOURCE(50)  // source 5
            if (written >= count) break;
            PROCESS_SOURCE(60)  // source 6
            if (written >= count) break;
            PROCESS_SOURCE(70)  // source 7
            pSrc = (SourceInfo*)((int*)pSrc + 80); // advance to next group (8 sources)
            idx += 8;
        }

        // Scan all 32 slots to find the one with smallest distance*weight
        float bestDist = DAT_00e4474c; // large initial threshold
        SourceInfo* pCurrent = (SourceInfo*)(this + 0x24);
        for (int i = 0; i < 0x20; i++)
        {
            if (pCurrent->active != 0 && pCurrent->active != 0x48)
            {
                if (pCurrent->distanceWeighted < bestDist)
                {
                    // Update best source (linked list insertion)
                    if (pBest != pCurrent)
                    {
                        int srcID = pCurrent->active;
                        if (*pBest != srcID)
                        {
                            if (*pBest)
                                FUN_004daf90((int*)pBest);
                            *pBest = srcID;
                            if (srcID)
                            {
                                *(int*)(this + 0x528) = *(int*)(srcID + 4);
                                *(int*)(srcID + 4) = (int)(this + 0x524);
                            }
                        }
                    }
                    newBestData = pCurrent->data;
                    newBestNode = pCurrent->node;
                    newBestID = pCurrent->active;
                    bestDist = pCurrent->distanceWeighted;
                }
            }
            pCurrent++; // advance to next source (each source is 10 ints = 40 bytes)
        }
    }
    else
    {
        // Focused source exists: copy it as the best
        if (pBest != pFocused)
        {
            int srcID = (int)pFocused;
            if (*pBest != srcID)
            {
                if (*pBest)
                    FUN_004daf90((int*)pBest);
                *pBest = srcID;
                if (srcID)
                {
                    *(int*)(this + 0x528) = *(int*)(srcID + 4);
                    *(int*)(srcID + 4) = (int)(this + 0x524);
                }
            }
        }
    }

    // Determine the new best source ID (0 if none)
    int newBestSrcID = *pBest ? (int)*pBest - 0x48 : 0;
    // If the best source changed, update active state via FUN_006a40b0
    if (prevBestID != newBestSrcID)
    {
        if (prevBestID)
            FUN_006a40b0(0); // deactivate old
        if (*pBest && *pBest != 0x48)
            FUN_006a40b0(1); // activate new
    }

    // Update the stored best source data (node, data pointer, ID)
    if (newBestID != *(int*)(this + 0x534))
    {
        // Release previous best data
        if (*(void**)(this + 0x530))
        {
            undefined4 local = **(undefined4**)(this + 0x530);
            FUN_00408a00(&local, 0);
        }
        *(int*)(this + 0x530) = newBestNode;
        *(void**)(this + 0x52c) = newBestData;
        if (newBestData)
        {
            undefined4 local = *(undefined4*)newBestData;
            FUN_00408a00(&local, 0);
        }
        *(int*)(this + 0x534) = newBestID;
    }
}

// Structure definitions (hypothetical)
struct SourceInfo {
    int active;            // +0x00: 0 = inactive, 0x48 = sentinel
    int pad;               // +0x04: unused
    float posX;            // +0x08
    float posY;            // +0x0C
    float posZ;            // +0x10
    float weight;          // +0x14: multiplier for distance
    float distanceWeighted; // +0x18: computed = (dist^2) * weight
    void* data;           // +0x1C: pointer to associated data
    int node;             // +0x20: some node identifier
    int pad2;             // +0x24: alignment
};