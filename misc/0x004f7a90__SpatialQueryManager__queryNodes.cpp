// FUNC_NAME: SpatialQueryManager::queryNodes
// Function at 0x004f7a90: Spatial query that filters a linked list of nodes by criteria (4 ints) and optional distance.
// The criteria pointer is expected to be in EDI register (custom calling convention).
// Parameters: criteria (EDI), result (EDX), maxResults (stack), range (XMM2), pos (stack)
// Returns: number of matching nodes stored in result.

struct SpatialNode {
    char unk00[0x10];
    uint8_t flags;           // +0x10 - bit 0: used flag? (checked if ==0)
    char unk11[7];
    int field18;             // +0x18 - criteria compare 0
    int field1C;             // +0x1C - criteria compare 1
    int field20;             // +0x20 - criteria compare 2
    int field24;             // +0x24 - criteria compare 3
    float radius;            // +0x28 - node radius for distance check
    char unk2C[0x44];
    float posX;              // +0x70
    float posY;              // +0x74
    float posZ;              // +0x78
    char unk7C[0x48];
    SpatialNode* next;       // +0xC4 - linked list next pointer
};

struct QueryCriteria {
    int field0;  // +0x00
    int field1;  // +0x04
    int field2;  // +0x08
    int field3;  // +0x0C
};

struct QueryResult {
    char unk00[0x10];
    SpatialNode* head;       // +0x10 - start of linked list
    SpatialNode* results[10];// +0x1C - output array (max 10)
    int count;               // +0x44 - number of stored results
};

static inline float squaredDist3D(const float* a, const SpatialNode* b) {
    float dx = a[0] - b->posX;
    float dy = a[1] - b->posY;
    float dz = a[2] - b->posZ;
    return dx*dx + dy*dy + dz*dz;
}

// Note: criteria comes from EDI, range from XMM2 in actual assembly
int __fastcall queryNodes(QueryCriteria* criteria, QueryResult* result, int maxResults, float range, const float* pos) {
    SpatialNode* node = result->head;
    if (maxResults <= 0 || maxResults > 10) {
        maxResults = 10;
    }
    result->count = 0;

    while (node != nullptr) {
        // Compare four criteria fields
        bool match = (criteria->field2 == node->field20) &&
                     (criteria->field3 == node->field24) &&
                     (criteria->field0 == node->field18) &&
                     (criteria->field1 == node->field1C) &&
                     ((node->flags & 1) == 0);  // object is not "used"
        
        if (match) {
            // Optional distance check: if pos is null or range is zero, skip check
            bool distOk = (pos == nullptr) || (range == 0.0f) ||
                          (squaredDist3D(pos, node) < (node->radius + range) * (node->radius + range));
            if (distOk) {
                if (result->count >= maxResults) {
                    return result->count;
                }
                result->results[result->count] = node;
                result->count++;
            }
        }
        node = node->next;
    }
    return result->count;
}