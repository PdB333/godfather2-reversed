// FUNC_NAME: SoundInstance::calculateGain
// Function at 0x006c3d70: computes final gain based on distance attenuation and a volume parameter.
class SoundInstance {
    // Unknown vtable at +0
    // +0x0e8: pointer to some spatial object (offset 0x48 inside it) with a virtual getPosition method at vtable+0x4c
    // +0x2c4: base volume or gain parameter
public:
    float calculateGain() const {
        // Get pointer to spatial parent from pointer at this+0xe8
        int* spatialBase = (this->spatialPtr != nullptr) ? (int*)(this->spatialPtr - 0x48) : nullptr;
        
        // Buffer to receive position
        float x, y, z;  // at local_1c, fStack_20, fStack_18 respectively
        
        // Call virtual getPosition (vtable offset 0x4c) on the spatial object
        (**(code**)(*spatialBase + 0x4c))(&x);
        
        // Compute distance from origin (or listener?) – magnitude of the position vector
        float dist = sqrtf(x*x + y*y + z*z);
        
        float gain;
        // Distance-based attenuation
        if (g_minDistance <= dist) {
            if (dist <= g_maxDistance) {
                // Linear interpolation between min and max values based on distance
                gain = mapDistanceToGain(dist, g_minDistance, g_maxDistance, g_minGain, g_maxGain);
            } else {
                gain = g_maxGain;
            }
        } else {
            gain = g_minGain;
        }
        
        // Final output = interpolated gain * globalScale1 + baseVolume * globalScale2
        return gain * g_globalScale1 + this->baseVolume * g_globalScale2;
    }
    
private:
    // Offsets (guessed)
    /* +0x00 */ void* vtable;
    /* ... */
    /* +0x0e8 */ void* spatialPtr;         // pointer to a spatial/transform node
    /* +0x2c4 */ float baseVolume;         // base volume parameter
};

// Global variables (from DAT_...)
extern float g_minDistance;   // DAT_0112a6ec
extern float g_maxDistance;   // _DAT_00e50e68
extern float g_minGain;       // DAT_00e50e64
extern float g_maxGain;       // DAT_00e50e60
extern float g_globalScale1;  // DAT_00d58cbc
extern float g_globalScale2;  // DAT_00d5efd0

// Helper function (FUN_006c91c0): linear interpolation from distance to gain
float mapDistanceToGain(float dist, float minDist, float maxDist, float minVal, float maxVal);