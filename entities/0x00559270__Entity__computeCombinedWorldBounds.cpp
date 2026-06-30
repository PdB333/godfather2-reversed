// FUNC_NAME: Entity::computeCombinedWorldBounds
// Function address: 0x00559270
// Computes the combined axis-aligned bounding box (AABB) of all child objects.
// The bounding box is 8 floats: minX, minY, minZ, minW, maxX, maxY, maxZ, maxW.
// If useLocalSpace is true, bounds are transformed into local space (via local_50 matrix).
// If there is a precomputed bounds override (this->boundsOverride), it returns that instead.

#include <cfloat>

// Forward declarations of helper functions (names inferred from context)
void getTransformMatrix(int* obj, float* outMatrix); // FUN_00557660
void computeBoundsFromMatrix(float* matrix, int param3, float* outBounds); // FUN_00557bd0
bool isPlayerControlled(); // FUN_00556e60
bool isSomething(); // FUN_00556e10
const char* getObjectTypeName(int obj); // FUN_00ab06f0
void transformBounds(float* matrix, float* bounds); // FUN_00aa2c40

// Global constants (likely FLT_MAX and -FLT_MAX)
extern float g_fltMax; // DAT_00e2e50c
extern float g_negFltMax; // DAT_00e44758

// Structure for dynamic array of children (offset 0x04 in this)
struct ChildArray {
    int* base;   // +0x00
    int count;   // +0x04
};

// Structure for a child element (size 0x70)
struct ChildElement {
    char pad0[0x40];
    int* objectPtr; // +0x40
    // ... rest of 0x70 bytes
};

// Structure for the object itself (this)
struct Entity {
    int* vtable; // +0x00
    ChildArray* children; // +0x04 (pointer to ChildArray)
    // ... other fields
    int* boundsOverride; // +0x1c (offset 7*4 = 0x1c)
    // +0xd0 is used for matrix in getTransformMatrix
};

void Entity::computeCombinedWorldBounds(float* outBounds, int param3, bool useLocalSpace)
{
    float localMatrix[19]; // 76 bytes, likely a 4x4 matrix + extra
    getTransformMatrix(this + 0xd0, localMatrix); // get world matrix or something

    // If there is a precomputed bounds override, use it directly
    if (this->boundsOverride != nullptr && *(int*)(this->boundsOverride + 0x10) != 0) {
        float* source;
        if (useLocalSpace) {
            source = localMatrix;
        } else {
            source = &DAT_011397d0; // global identity or default bounds
        }
        computeBoundsFromMatrix(source, param3, outBounds);
        return;
    }

    // Initialize min/max accumulators
    float minX = g_fltMax;
    float minY = g_fltMax;
    float minZ = g_fltMax;
    float minW = 0.0f;
    float maxX = g_negFltMax;
    float maxY = g_negFltMax;
    float maxZ = g_negFltMax;
    float maxW = 0.0f;

    bool playerControlled = isPlayerControlled();
    if (playerControlled) {
        // Iterate over children (player-controlled path)
        ChildArray* arr = this->children;
        int* base = arr->base;
        int count = arr->count;
        int* end = base + count * 0x70;
        for (int* child = base; child < end; child += 0x70) {
            int* obj = *(int**)(child + 0x40);
            if (obj == nullptr) {
                // Check again (maybe due to lazy evaluation)
                obj = *(int**)(child + 0x40);
                if (obj != nullptr) {
                    // Call vtable method at offset 0x1c to get bounding box
                    typedef void (*GetBoundsFunc)(int* obj, int param3, float* outBounds);
                    GetBoundsFunc getBounds = (GetBoundsFunc)(*(int**)(*(int*)(obj + 0x10)))[0x1c / 4];
                    getBounds(*(int**)(obj + 0x18), param3, &fStack_70); // fStack_70 is a local array of 8 floats

                    if (!useLocalSpace) {
                        // Direct comparison for world space
                        if (fStack_70 <= minX) minX = fStack_70;
                        if (fStack_6c <= minY) minY = fStack_6c;
                        if (fStack_68 <= minZ) minZ = fStack_68;
                        if (fStack_64 <= minW) minW = fStack_64;
                        if (maxX <= fStack_60) maxX = fStack_60;
                        if (maxY <= fStack_5c) maxY = fStack_5c;
                        if (maxZ <= fStack_58) maxZ = fStack_58;
                        if (maxW <= fStack_54) maxW = fStack_54;
                    } else {
                        // Transform bounds into local space
                        transformBounds(localMatrix, &fStack_70);
                        transformBounds(localMatrix, &fStack_60);
                        // Then compare min/max
                        if (fStack_70 <= minX) minX = fStack_70;
                        if (fStack_6c <= minY) minY = fStack_6c;
                        if (fStack_68 <= minZ) minZ = fStack_68;
                        if (fStack_64 <= minW) minW = fStack_64;
                        if (fStack_60 <= minX) minX = fStack_60; // note: also compare max to min?
                        if (fStack_5c <= minY) minY = fStack_5c;
                        if (fStack_58 <= minZ) minZ = fStack_58;
                        if (fStack_54 <= minW) minW = fStack_54;
                        if (maxX <= fStack_70) maxX = fStack_70;
                        if (maxY <= fStack_6c) maxY = fStack_6c;
                        if (maxZ <= fStack_68) maxZ = fStack_68;
                        if (maxW <= fStack_64) maxW = fStack_64;
                        if (maxX <= fStack_60) maxX = fStack_60;
                        if (maxY <= fStack_5c) maxY = fStack_5c;
                        if (maxZ <= fStack_58) maxZ = fStack_58;
                        if (maxW <= fStack_54) maxW = fStack_54;
                    }
                    // Update maxW if needed
                    if (fStack_54 >= maxW || fStack_54 == maxW) {
                        maxW = fStack_54;
                    }
                }
            } else {
                // Object is non-null, check type name to skip certain objects
                int* vtable = *(int**)(*DAT_0113dfc8 + 0x14)(); // get some global
                int typeId = (**(code**)(*vtable + 0x10))(obj);
                const char* typeName = getObjectTypeName(&uStack_71, typeId);
                if (*typeName != '\0') {
                    // Skip this object? Actually goto the null check path
                    goto LAB_005594de;
                }
            }
        }
    } else {
        // Non-player-controlled path (similar but without the type check skip)
        ChildArray* arr = this->children;
        int* base = arr->base;
        int count = arr->count;
        int* end = base + count * 0x70;
        for (int* child = base; child < end; child += 0x70) {
            int* obj = *(int**)(child + 0x40);
            if (obj == nullptr) {
                // Same as above
                obj = *(int**)(child + 0x40);
                if (obj != nullptr) {
                    typedef void (*GetBoundsFunc)(int* obj, int param3, float* outBounds);
                    GetBoundsFunc getBounds = (GetBoundsFunc)(*(int**)(*(int*)(obj + 0x10)))[0x1c / 4];
                    getBounds(*(int**)(obj + 0x18), param3, &fStack_70);

                    if (useLocalSpace) {
                        transformBounds(localMatrix, &fStack_70);
                        transformBounds(localMatrix, &fStack_60);
                    }
                    // Compare min/max
                    if (fStack_70 <= minX) minX = fStack_70;
                    if (fStack_6c <= minY) minY = fStack_6c;
                    if (fStack_68 <= minZ) minZ = fStack_68;
                    if (fStack_64 <= minW) minW = fStack_64;
                    if (maxX <= fStack_60) maxX = fStack_60;
                    if (maxY <= fStack_5c) maxY = fStack_5c;
                    if (maxZ <= fStack_58) maxZ = fStack_58;
                    if (maxW <= fStack_54) maxW = fStack_54;
                }
            } else {
                // Type check skip (same as above)
                int* vtable = *(int**)(*DAT_0113dfc8 + 0x14)();
                int typeId = (**(code**)(*vtable + 0x10))(obj);
                const char* typeName = getObjectTypeName(&uStack_71, typeId);
                if (*typeName != '\0') {
                    goto LAB_00559377;
                }
            }
        }
    }

    // Write final combined bounds
    outBounds[0] = minX;
    outBounds[1] = minY;
    outBounds[2] = minZ;
    outBounds[3] = minW;
    outBounds[4] = maxX;
    outBounds[5] = maxY;
    outBounds[6] = maxZ;
    outBounds[7] = maxW;
}