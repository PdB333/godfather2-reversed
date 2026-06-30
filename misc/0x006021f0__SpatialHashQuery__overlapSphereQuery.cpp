// FUNC_NAME: SpatialHashQuery::overlapSphereQuery
// Address: 0x006021f0
// Role: Iterates over spatial hash structure to find objects within a sphere radius.
//        Uses a two-tier approach: if g_spatialQueryBucketIndex == 0xFFFF, iterates over all
//        buckets in a grid (g_spatialGridHeader); otherwise follows a linked list of nodes
//        starting from that index. For each node, checks if the given point is within
//        radius squared of the node's bounding box (AABB). Calls foundObjectCallback()
//        for each hit and supports early cancellation via a cancel flag at iterator+4.

struct SpatialNode {
    float minX, minY, minZ; // +0x00
    float maxX, maxY, maxZ; // +0x0C
    // unknown pad or data
    uint16_t nextIndex;     // +0x1C (7th float offset, stored as ushort)
}; // total 0x24 bytes

// External globals (likely set by spatial system)
extern uint16_t g_spatialQueryBucketIndex;     // 0x1a (if 0xFFFF, iterate grid)
extern uint32_t  g_spatialGridHeader;           // 0x20 (low word = bucketStart, high word = bucketCount)
extern uint16_t* g_bucketStartIndexArray;       // 0x44 (array of ushort indices for each grid cell)
extern SpatialNode* g_spatialNodeArray;         // 0x48 (base of all nodes)

// Forward declarations of external functions
bool FUN_00601d80(void* iterator);              // Check for cancellation / yield
void FUN_005fcce0();                            // Called for each overlapping object (e.g., add to list)
void FUN_005fc5f0(int val);                     // Setup or cleanup (called with 0)

int SpatialHashQuery_OverlapSphere(float* point, void* thisObj, void* iterator,
                                   float radiusSq, int filterFlags)
{
    // Outer loop processes in chunks; cancel flag is at iterator+4
    while (*(int*)(((char*)iterator) + 4) != 0)
    {
        // Exit early if filterFlags is 0 (skip all) and not -1 (skip none)
        if ((filterFlags != -1) && (filterFlags == 0))
            break;

        // Check for cancellation / yield control
        FUN_00601d80(iterator);

        if (g_spatialQueryBucketIndex == 0xFFFF)
        {
            // Iterate over a contiguous range of buckets defined by g_spatialGridHeader
            uint16_t bucketStart = (uint16_t)(g_spatialGridHeader & 0xFFFF);
            uint16_t bucketCount = (uint16_t)(g_spatialGridHeader >> 16);
            uint32_t idx = bucketStart;
            uint32_t endIdx = bucketStart + bucketCount;

            while (idx < endIdx)
            {
                // Each bucket holds an index into node array
                uint16_t nodeIndex = g_bucketStartIndexArray[idx];
                SpatialNode* node = &g_spatialNodeArray[nodeIndex];

                // Compute squared distance from point to AABB (approximate with point-AABB distance)
                float dx = 0.0f;
                float x = point[0];
                if (x < node->minX)
                    dx = x - node->minX;
                else if (x > node->maxX)
                    dx = x - node->maxX;
                float dy = 0.0f;
                float y = point[1];
                if (y < node->minY)
                    dy = y - node->minY;
                else if (y > node->maxY)
                    dy = y - node->maxY;
                float dz = 0.0f;
                float z = point[2];
                if (z < node->minZ)
                    dz = z - node->minZ;
                else if (z > node->maxZ)
                    dz = z - node->maxZ;
                float distSq = dx*dx + dy*dy + dz*dz;
                if (distSq <= radiusSq)
                {
                    FUN_005fcce0();
                }
                idx++;
                // Re-read bucketIndex in case it was modified? (not obvious)
            }
        }
        else
        {
            // Traverse a linked list of nodes starting from g_spatialQueryBucketIndex
            SpatialNode* node = &g_spatialNodeArray[g_spatialQueryBucketIndex];
            while (node != nullptr)
            {
                // Compute squared distance from point to AABB
                float dx = 0.0f;
                float x = point[0];
                if (x < node->minX)
                    dx = x - node->minX;
                else if (x > node->maxX)
                    dx = x - node->maxX;
                float dy = 0.0f;
                float y = point[1];
                if (y < node->minY)
                    dy = y - node->minY;
                else if (y > node->maxY)
                    dy = y - node->maxY;
                float dz = 0.0f;
                float z = point[2];
                if (z < node->minZ)
                    dz = z - node->minZ;
                else if (z > node->maxZ)
                    dz = z - node->maxZ;
                float distSq = dx*dx + dy*dy + dz*dz;
                if (distSq <= radiusSq)
                {
                    FUN_005fcce0();
                }

                // Move to next node; if nextIndex == 0xFFFF, end of list
                uint16_t next = node->nextIndex;
                if (next == 0xFFFF)
                    break;
                node = &g_spatialNodeArray[next];
            }
        }

        // Re-check cancellation flag for next iteration
    }

    // If cancellation flag still set, return 0 without finalizing
    if (*(int*)(((char*)iterator) + 4) != 0)
        return 0;

    // Finalize query
    FUN_005fc5f0(0);
    // Call a virtual callback on the query object (vtable+0x10)
    (*(void (**)())(*(void**)thisObj + 0x10))();
    return 0;
}