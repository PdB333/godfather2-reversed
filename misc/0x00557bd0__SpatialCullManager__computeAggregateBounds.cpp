// FUNC_NAME: SpatialCullManager::computeAggregateBounds
// Address: 0x00557bd0
// Role: Iterates over a list of objects (stride 0x70) stored via a descriptor at this+0x30,
// queries each object's bounding box (8 floats) through a virtual function at vtable offset 0x1c,
// and computes the aggregate min/max AABB, storing it in the output array (8 floats).

// Assuming FLT_MAX is represented by globals DAT_00e2e50c (min init) and -FLT_MAX by DAT_00e44758 (max init).
// These constants are likely INFINITY and -INFINITY as typical for AABB accumulation.

#include <cstdint>

// Forward declarations
struct BoundsProviderVTable;
struct BoundsProvider {
    BoundsProviderVTable* vtable;
};

struct BoundsProviderVTable {
    // ... other methods
    void (*getBounds)(BoundsProvider* self, void* context1, void* context2, float* outBounds); // +0x1c
};

// The aggregate bounds class (name chosen for clarity)
class SpatialCullManager {
public:
    // Describes a dynamic array with base pointer and count
    struct ArrayDescriptor {
        uint8_t* data;    // base of array (element size 0x70)
        int32_t count;    // number of elements
    }* m_arrayDescriptor; // +0x30

    void computeAggregateBounds(void* context1, void* context2, float* outBounds);
};

void SpatialCullManager::computeAggregateBounds(void* context1, void* context2, float* outBounds) {
    // Get the array descriptor from this+0x30
    ArrayDescriptor* descriptor = *(ArrayDescriptor**)((uint8_t*)this + 0x30);
    uint8_t* basePtr = descriptor->data;                // first int of descriptor
    int32_t count = descriptor->count;                  // second int of descriptor

    // Initialize min to large positive, max to large negative
    float minX = *(float*)0x00e2e50c;   // likely FLT_MAX
    float minY = *(float*)0x00e2e50c;
    float minZ = *(float*)0x00e2e50c;
    float minW = *(float*)0x00e2e50c;   // 4th component (e.g. radius, time, or unused)
    float maxX = *(float*)0x00e44758;   // likely -FLT_MAX
    float maxY = *(float*)0x00e44758;
    float maxZ = *(float*)0x00e44758;
    float maxW = *(float*)0x00e44758;

    // Iterate over each element (stride 0x70)
    for (int32_t i = 0; i < count; ++i) {
        uint8_t* element = basePtr + i * 0x70;
        // Each element has a pointer to a BoundsProvider at offset +0x40
        BoundsProvider* provider = *(BoundsProvider**)(element + 0x40);
        if (provider != nullptr) {
            float bounds[8];  // [minX, minY, minZ, minW, maxX, maxY, maxZ, maxW]
            // Call virtual function at vtable offset 0x1c
            provider->vtable->getBounds(provider, context1, context2, bounds);

            // Update min values (first 4 floats)
            if (bounds[0] < minX) minX = bounds[0];
            if (bounds[1] < minY) minY = bounds[1];
            if (bounds[2] < minZ) minZ = bounds[2];
            if (bounds[3] < minW) minW = bounds[3];
            // Update max values (last 4 floats)
            if (bounds[4] > maxX) maxX = bounds[4];
            if (bounds[5] > maxY) maxY = bounds[5];
            if (bounds[6] > maxZ) maxZ = bounds[6];
            if (bounds[7] > maxW) maxW = bounds[7];
        }
    }

    // Store final aggregated AABB
    outBounds[0] = minX;
    outBounds[1] = minY;
    outBounds[2] = minZ;
    outBounds[3] = minW;
    outBounds[4] = maxX;
    outBounds[5] = maxY;
    outBounds[6] = maxZ;
    outBounds[7] = maxW;
}