// FUNC_NAME: SimManager::ComputeBoundingSphere

// Function at 0x00995930
// Computes a bounding sphere for a collection of objects stored in this->m_objects.
// Output is a float[4] { centerX, centerY, centerZ, radius }.
// Returns 1 if there are objects, 0 if the list is empty.

#include <math.h>

// Global constant, likely 0.5f
extern float g_halfScale;  // _DAT_00d5c458

struct ObjectWrapper {
    struct { float data[7]; } m_transform;  // at +0xE0 (7 floats)
    float m_extra;                          // at +0xFC
    struct { float data[7]; } m_bounds;     // at +0x100
    float m_extra2;                         // at +0x11C
    void** vtable;                          // at +0x10
    // virtual function at vtable+0x1C (index 7) 
    // likely: void GetWorldBounds(float* transformData, int arg, float* outMinMax)
    // outMinMax is 8 floats: minX, minY, minZ, minW, maxX, maxY, maxZ, maxW
};

struct ObjectList {
    ObjectWrapper** m_objects;  // pointer to array of pointers (offset +0x8)
    int m_count;                // offset +0xC
};

int __thiscall SimManager::ComputeBoundingSphere(float* outSphere) {
    float minX, minY, minZ, minW;
    float maxX, maxY, maxZ, maxW;
    ObjectList* list = *(ObjectList**)(this + 0x20);
    
    // Initialize output to zero
    outSphere[0] = 0.0f;
    outSphere[1] = 0.0f;
    outSphere[2] = 0.0f;
    outSphere[3] = 0.0f;
    
    if (list == nullptr) {
        return 0;
    }
    
    int count = list->m_count;
    if (count <= 0) {
        return 0;
    }
    
    bool first = true;
    for (int i = 0; i < count; i++) {
        ObjectWrapper* obj = list->m_objects[i];
        
        // Read transform data from the object
        // The transform data at offset +0xE0 is passed to the virtual function
        float transformData[7];
        for (int j = 0; j < 7; j++) {
            transformData[j] = *(float*)((char*)obj + 0xE0 + j*4);
        }
        float extra = *(float*)((char*)obj + 0xFC); // unused in call but read
        
        // Prepare output buffer for bounding box (min/max in 4D)
        float minMax[8]; // minX, minY, minZ, minW, maxX, maxY, maxZ, maxW
        
        // Call virtual function to compute world-space bounds
        // vtable at +0x10, function at index 7 (+0x1C)
        void (**vtable)(void*, int, float*) = *(void(***)(void*, int, float*))(obj + 0x10);
        vtable[7](transformData, 0, minMax);
        
        // Read the remaining data (unused)
        float boundsData[7];
        for (int j = 0; j < 7; j++) {
            boundsData[j] = *(float*)((char*)obj + 0x100 + j*4);
        }
        float extra2 = *(float*)((char*)obj + 0x11C);
        
        float objMinX = minMax[0];
        float objMinY = minMax[1];
        float objMinZ = minMax[2];
        float objMinW = minMax[3];
        float objMaxX = minMax[4];
        float objMaxY = minMax[5];
        float objMaxZ = minMax[6];
        float objMaxW = minMax[7];
        
        if (first) {
            minX = objMinX;
            minY = objMinY;
            minZ = objMinZ;
            minW = objMinW;
            maxX = objMaxX;
            maxY = objMaxY;
            maxZ = objMaxZ;
            maxW = objMaxW;
            first = false;
        } else {
            // Update min for first 4 floats
            if (objMinX < minX) minX = objMinX;
            if (objMinY < minY) minY = objMinY;
            if (objMinZ < minZ) minZ = objMinZ;
            if (objMinW < minW) minW = objMinW;
            // Update max for next 4 floats
            if (objMaxX > maxX) maxX = objMaxX;
            if (objMaxY > maxY) maxY = objMaxY;
            if (objMaxZ > maxZ) maxZ = objMaxZ;
            if (objMaxW > maxW) maxW = objMaxW;
        }
    }
    
    // Compute center as midpoint of min/max for X, Y, Z (scaled by global factor)
    float centerX = (maxX + minX) * g_halfScale;   // likely 0.5f
    float centerY = (maxY + minY) * g_halfScale;
    float centerZ = (maxZ + minZ) * g_halfScale;
    
    // Compute half extents from center to max
    float dx = centerX - maxX;   // negative, but used squared
    float dy = centerY - maxY;
    float dz = centerZ - maxZ;
    
    outSphere[0] = centerX;
    outSphere[1] = centerY;
    outSphere[2] = centerZ;
    outSphere[3] = sqrtf(dx*dx + dy*dy + dz*dz);
    
    return 1;
}