// FUNC_NAME: VisibilityManager::updateCulledSet
void __thiscall VisibilityManager::updateCulledSet(
    void* cameraTransform,          // param_2 - likely camera or projection matrix
    float* baseWorldOffset,         // param_3 - world-space offset (e.g. player position)
    int frustumParam1,              // param_4 - frustum parameter
    int frustumParam2,              // param_5
    int frustumParam3,              // param_6
    int frustumParam4,              // param_7 - bool flag for immediate update
    int frustumParam5,              // param_8
    int* prevVisibleList,           // param_9 - previous frame visible set (count at [1], data at [0])
    int* currentVisibleList)        // param_10 - current frame output set (count at [1], data at [0])
{
    // Node structure stored at this->+0x60 array (8 bytes each? actually pointer to object)
    // Object has fields: +0x0 ID, +0x47*4 flags (bit 27 indicates visible), +0x4c-0x4f previous LOD data
    struct ObjectNode {
        int id;               // +0x00
        int flags;            // +0x04 (bit 27: visibility candidate)
        float prevLodData[4]; // +0x4c - offset 0x4c (4 floats)
    };

    // Output entry (0x30 bytes)
    struct VisibleEntry {
        int id;                     // +0x00
        float lodData[4];           // +0x04 (4 floats)
        int padding;                // +0x14? Actually layout: id (4), then 4 floats (16) = 20, then more? From code: puVar10[4] = puVar3[0x4c]; => offset 0x30/4 = 12 ints. So: id, 4 floats, then 3 floats? Let's match: *puVar10 = *puVar3; (id), then puVar10[4]=puVar3[0x4c] (first LOD), puVar10[5]=puVar3[0x4d], etc. So offset 4: puVar10[1]? Wait: puVar10 is undefined4*, so puVar10[4] is 16 bytes after start. So layout: [0]=id, [1..3] maybe something else? Actually code: *puVar10 = *puVar3; // id
        // then puVar10[4] = puVar3[0x4c]; // LOD0
        // puVar10[5] = puVar3[0x4d]; // LOD1
        // puVar10[6] = puVar3[0x4e]; // LOD2
        // puVar10[7] = puVar3[0x4f]; // LOD3
        // puVar10[8] = 0; // padding
        // So entries [1..3] are not set? Actually they are skipped. This suggests the output entry has 12 ints: id at 0, then unknown 3 ints (offsets 4..12?), then 4 LOD floats at 16, then padding at 32. So we'll define accordingly.
    };

    // Constants
    float frameTime = *reinterpret_cast<float*>(0x00e57370); // DAT_00e57370
    float offsetX = *reinterpret_cast<float*>(0x00e56a60);   // DAT_00e56a60
    float offsetY = *reinterpret_cast<float*>(0x00e56a64);   // fRam00e56a64
    float offsetZ = *reinterpret_cast<float*>(0x00e56a68);   // DAT_00e56a68
    float offsetW = *reinterpret_cast<float*>(0x00e56a6c);   // fRam00e56a6c

    float local20[4];
    local20[0] = frameTime * offsetX + baseWorldOffset[0];
    local20[1] = frameTime * offsetY + baseWorldOffset[1];
    local20[2] = frameTime * offsetZ + baseWorldOffset[2];
    local20[3] = frameTime * offsetW + baseWorldOffset[3];

    // Transform world position to screen space (or some clip space)
    float screenPos[4];
    transformToScreen(cameraTransform, local20, screenPos); // FUN_0056b420

    double screenXDouble = static_cast<double>(screenPos[0]);
    getPriorityFactor(); // FUN_00b9a9fa - maybe random or time-based factor

    float priorityFactor = static_cast<float>(screenXDouble);
    if (priorityFactor < 0.0f) {
        priorityFactor += *reinterpret_cast<float*>(0x00d5d70c); // DAT_00d5d70c
    }
    priorityFactor *= *reinterpret_cast<float*>(0x00e44748); // DAT_00e44748

    // Previous visible count
    int prevCount = prevVisibleList[1];
    // Total object count in this container
    int totalCount = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 100); // +0x64

    // First iteration: if totalCount == 0, handle immediate update case
    while (true) {
        if (totalCount == 0) {
            // If immediate update requested (param_7 != 0)
            if (currentVisibleList[1] != 0) {
                currentVisibleList[1] = 0; // reset count
            }
            if (frustumParam4 != 0) {
                // Reinitialize the visible list from scratch
                reallocateArray(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 100)); // FUN_00941a80
                unsigned int objectIndex = 0;
                if (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 100) != 0) {
                    do {
                        ObjectNode* node = *reinterpret_cast<ObjectNode**>(
                            *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x60) + 4 + objectIndex * 8);
                        if ((node->flags >> 27) & 1) {
                            int currentCount = currentVisibleList[1];
                            if (currentCount == prevCount) { // prevCount is reused as capacity? Actually param_10[1] is compared to param_10[2]? Code: if (param_10[1] == iVar9) where iVar9 is param_10[2] - so second int of currentVisibleList is capacity
                                int capacity = currentVisibleList[2];
                                if (currentCount == capacity) {
                                    capacity = (capacity == 0) ? 1 : capacity * 2;
                                    currentVisibleList = reinterpret_cast<int*>(growArray(capacity)); // FUN_00941a80 - reallocates
                                }
                            }
                            // Add entry
                            VisibleEntry* entry = reinterpret_cast<VisibleEntry*>(currentVisibleList[0] + currentCount * 0x30);
                            currentVisibleList[1] = currentCount + 1;
                            entry->id = node->id;
                            entry->lodData[0] = node->prevLodData[0];
                            entry->lodData[1] = node->prevLodData[1];
                            entry->lodData[2] = node->prevLodData[2];
                            entry->lodData[3] = node->prevLodData[3];
                            // entry->padding = 0; (not needed)
                        }
                        objectIndex++;
                    } while (objectIndex < *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 100));
                }
            }
            return;
        }

        // For each object in the pool (iterating backwards)
        // prevCount is the number of entries in the previous visible list to consider
        if (prevCount != 0) {
            // Get the ID of the current object being tested
            unsigned int currentObjId = *reinterpret_cast<unsigned int*>(
                *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x60) - 4 + totalCount * 8);
            // Search in previous list for a matching ID (sorted by ID descending)
            VisibleEntry* prevEntry = reinterpret_cast<VisibleEntry*>(prevVisibleList[0] + (prevCount - 1) * 0x30);
            while (prevCount != 0) {
                if (prevEntry->id <= currentObjId) {
                    if (prevCount != 0) {
                        if (*reinterpret_cast<int*>(prevVisibleList[0] + (prevCount - 1) * 0x30) == currentObjId) {
                            // Found matching entry, get its LOD data
                            int lodDataWord = *reinterpret_cast<int*>(prevVisibleList[0] + (prevCount - 1) * 0x30 + 0x20); // offset 0x20? Actually code: *(undefined4 *)(iVar8 + -0x10) where iVar8 = iVar11 * 0x30 + *param_9, offset -0x10 gives +0x20 from start. So that's the first LOD data word? But we need to be consistent.
                            goto foundLodData;
                        }
                    }
                    break;
                }
                prevCount--;
                prevEntry = reinterpret_cast<VisibleEntry*>(reinterpret_cast<char*>(prevEntry) - 0x30);
            }
        }
        foundLodData:
        int prevLodData = 0; // default if not found
        // ... (actually the goto jumps to assignment)

        // Perform visibility test
        bool isVisible = frustumCullTest(
            cameraTransform, baseWorldOffset,
            frustumParam1, frustumParam2, frustumParam3,
            priorityFactor, someGlobal1, frustumParam4, frustumParam5,
            prevLodData); // FUN_0094b540

        if (!isVisible) {
            // Object not visible - remove from active set
            ObjectNode** nodePtr = reinterpret_cast<ObjectNode**>(
                *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x60) - 4 + totalCount * 8);
            // Remove object by calling releaseObject (FUN_00949f30)
            releaseObject();
            *nodePtr = reinterpret_cast<ObjectNode*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x5c)); // move to free list
            *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x38) -= 1; // used count decrement
            *reinterpret_cast<ObjectNode**>(reinterpret_cast<char*>(this) + 0x5c) = nodePtr; // free list head
            *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x34) += 1; // free count increment

            if (totalCount > 0) {
                sortArray(totalCount - 1); // FUN_00949430 - likely sort the node array
            }
        }
        totalCount--;
    }
}