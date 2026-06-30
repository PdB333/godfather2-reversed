// FUNC_NAME: OverlapManager::addOverlapIfIntersecting
// Function at 0x00428b30: Checks if two AABBs overlap beyond a threshold and registers the pair in a group's dynamic array.
// Uses a global manager (gOverlapManager) to find a group by object ID, then adds an 80-byte entry if volume exceeds threshold.

#include <cstdint>

// Global manager structure assumed to be at 0x012053cc
struct GroupOverlapData {
    int32_t id;                   // +0x00: Group identifier
    // Possibly more fields up to 0x5C? Actually total size 0x60 from stride
    float* overlapArray;          // +0x48: Pointer to dynamic array of 80-byte entries
    uint32_t count;               // +0x4C: Number of entries
    uint32_t capacity;            // +0x50: Capacity of array
    // ... rest of 0x60 bytes
};

// Global pointer to manager (size unknown, but contains array of 128 groups at offset 0x40)
extern uint8_t* gOverlapManager;   // DAT_012053cc

// Constants (from global data)
extern float gMinDistanceThreshold;  // DAT_00e2b1a4
extern float gAdjustmentFactor;      // DAT_00e2cd54
extern float gVolumeThreshold;       // DAT_00e2e644

uint32_t OverlapManager::addOverlapIfIntersecting(float* aabbMin, float* aabbMax) {
    uint32_t index = 0;
    
    // Find the group that matches this object's ID (from the hidden 'this' pointer, likely in ECX/EAX)
    // The object has an ID at offset +0xB4
    int32_t* idField = reinterpret_cast<int32_t*>(gOverlapManager + 0x40);
    while (*idField != *(reinterpret_cast<int32_t*>(thisObj) + 0x2D)) { // +0xB4 / 4 = 0x2D
        index++;
        idField += 6; // 0x18/sizeof(int) = 6
        if (index > 127) {
            return 0xFFFFFF00; // Not found, return failure
        }
    }
    
    // Get pointer to the group structure
    GroupOverlapData* group = reinterpret_cast<GroupOverlapData*>(gOverlapManager + index * 0x60);
    if (group == nullptr) {
        return 0;
    }
    
    // Check if this pair already exists in the group's overlap list
    uint32_t i = 0;
    if (group->count > 0) {
        int32_t* entryID = reinterpret_cast<int32_t*>(group->overlapArray);
        while (*entryID != reinterpret_cast<int32_t>(thisObj)) {
            i++;
            entryID += 20; // Each entry is 80 bytes (20 ints) -> skip to next entry's first int
            if (i >= group->count) {
                break;
            }
        }
        if (i < group->count) {
            // Already exists, return success (1)
            return 1;
        }
    }
    
    // Copy AABB min and max (both 4 floats)
    float adjustedMin[4] = { aabbMin[0], aabbMin[1], aabbMin[2], aabbMin[3] };
    float adjustedMax[4] = { aabbMax[0], aabbMax[1], aabbMax[2], aabbMax[3] };
    
    // Clamp separation to minimum distance by pushing both boxes apart
    float dx = adjustedMax[0] - adjustedMin[0];
    if (dx < gMinDistanceThreshold) {
        float adjust = (gMinDistanceThreshold - dx) * gAdjustmentFactor;
        adjustedMin[0] -= adjust;
        adjustedMax[0] += adjust;
    }
    float dy = adjustedMax[1] - adjustedMin[1];
    if (dy < gMinDistanceThreshold) {
        float adjust = (gMinDistanceThreshold - dy) * gAdjustmentFactor;
        adjustedMin[1] -= adjust;
        adjustedMax[1] += adjust;
    }
    float dz = adjustedMax[2] - adjustedMin[2];
    if (dz < gMinDistanceThreshold) {
        float adjust = (gMinDistanceThreshold - dz) * gAdjustmentFactor;
        adjustedMin[2] -= adjust;
        adjustedMax[2] += adjust;
    }
    
    // Compute overlap volume
    float volume = (adjustedMax[0] - adjustedMin[0]) * (adjustedMax[1] - adjustedMin[1]) * (adjustedMax[2] - adjustedMin[2]);
    if (volume > gVolumeThreshold) {
        // Resize array if needed
        if (group->count == group->capacity) {
            uint32_t newCapacity = (group->capacity == 0) ? 1 : group->capacity * 2;
            // FUN_00429eb0 is a resize function (e.g., realloc)
            FUN_00429eb0(&group->overlapArray, newCapacity);
            group->capacity = newCapacity;
        }
        
        // Copy the adjusted AABB (20 floats = 80 bytes) to the end of the array
        float* dest = group->overlapArray + group->count * 20;
        float* src = adjustedMin;
        for (int j = 0; j < 20; j++) {
            *dest++ = *src++;
        }
        group->count++;
    }
    
    // Return success (1); the original decompiled had an odd CONCAT31, likely just 1
    return 1;
}