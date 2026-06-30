// FUNC_NAME: SpatialManager::OverlapSphere (or similar; static function using global manager)
// Function address: 0x00478f20
// Role: Iterates over all spatial objects, tests sphere overlap (if sphere provided), and calls a callback for each overlapping object.
//       Returns number of objects processed (stops early if callback returns false).
// Global gSpatialManager at 0x012233ac points to a SpatialManager struct:
// Offset +0x5c: int objectCount
// Offset +0x60: Object** objectArray (pointers to Object structs)
// Object struct:
// Offset +0x180: float posX
// Offset +0x184: float posY
// Offset +0x188: float posZ
// Offset +0x18c: float radius

typedef bool (*OverlapCallback)(void* object, int userData);

struct SpatialManagerVtable; // forward

struct SpatialManager {
    // ... vtable, etc.
    int objectCount;            // +0x5c
    void** objectArray;         // +0x60 (array of pointers to objects)
};

extern SpatialManager* gSpatialManager; // 0x012233ac

// Note: The sphere is defined as float[4] = {x, y, z, radius}. If sphere is null, no spatial filter.
int OverlapSphere(OverlapCallback callback, int userData, const float* sphere) {
    SpatialManager* mgr = gSpatialManager;
    if (mgr == nullptr) {
        return 0;
    }

    int processedCount = 0;
    float sphereRadiusSq = 0.0f;
    if (sphere != nullptr) {
        sphereRadiusSq = sphere[3] * sphere[3]; // sphere radius squared
    }

    int count = mgr->objectCount;
    if (count > 0) {
        void** objects = mgr->objectArray;
        for (int i = 0; i < count; ++i) {
            void* obj = objects[i];
            // Check sphere overlap if sphere is provided
            if (sphere == nullptr) {
                // No sphere filter -> always overlaps
            } else {
                float dx = sphere[0] - *(float*)((uintptr_t)obj + 0x180);
                float dy = sphere[1] - *(float*)((uintptr_t)obj + 0x184);
                float dz = sphere[2] - *(float*)((uintptr_t)obj + 0x188);
                float distSq = dx*dx + dy*dy + dz*dz;
                float objRadius = *(float*)((uintptr_t)obj + 0x18c);
                // Overlap if distance squared <= (objRadius^2 + sphereRadius^2)
                if (distSq > objRadius*objRadius + sphereRadiusSq) {
                    continue; // no overlap
                }
            }
            // Overlap found
            ++processedCount;
            bool continueIter = callback(obj, userData);
            if (!continueIter) {
                return processedCount; // stop iteration
            }
        }
    }
    return processedCount;
}