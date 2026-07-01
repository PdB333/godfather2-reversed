// FUNC_NAME: ChaseCamera::updateTargetState
#include <cstdint>

// Global constants (likely from .data)
extern float g_cameraTimeDelta;   // _DAT_00d578c0
extern float g_frameRateDivisor;  // DAT_012067e8
extern float g_maxDelta;          // DAT_00e44598
extern uint32_t g_absMask;        // DAT_00e44680 (0x7FFFFFFF for absolute difference)

class ChaseCamera {
public:
    // Offset 0x60*4 = 0x180: enabled flag
    // Offset 0x129*4 = 0x4A4: flags byte (bit0: use local-space smoothing)
    // Offset 0x109*4 = 0x424: 3D vector (two floats packed as uint64 + float)
    struct { float x, y; } velocityXY; // 0x424-0x42B
    float velocityZ;                   // 0x42C

    void updateTargetState();
};

// Forward declarations of helper functions (from game)
bool getWorldTransform(float outDir[3], float outPos[3]); // FUN_0045e9e0
bool isTargetValid();                                     // FUN_00481660
float* getTargetData();                                   // FUN_00471610
void resetTargetTracking(const float targetPos[3]);       // FUN_0046f9c0
void disableCamera();                                     // FUN_0045ff80

void ChaseCamera::updateTargetState() {
    // If camera disabled (flag at +0x180), skip
    if (*(int*)((uint8_t*)this + 0x180) != 0) {
        disableCamera();
        return;
    }

    float dir[3];       // local_60/fStack_5c/fStack_58
    float pos[3];       // local_50/local_4c/local_48
    float mat[3][4];    // local_40/local_3c/local_38/local_30/local_2c/local_28 etc. (12 floats)
    // Actually the decompile uses arrays indexed [0..11] from pfVar2, so we treat as 3x4

    // Get current world transform (direction and position)
    bool gotTransform = getWorldTransform(dir, pos);
    if (!gotTransform) {
        return;
    }

    // Check if target is valid and if its transform changed significantly
    if (isTargetValid()) {
        float* targetData = getTargetData(); // returns pointer to 12 floats (3x4 matrix)
        // Compare each component with previously stored transform using absolute difference mask
        bool changed = false;
        changed = changed || (g_maxDelta < (float)((uint32_t)(targetData[4] - mat[0][1]) & g_absMask));
        changed = changed || (g_maxDelta < (float)((uint32_t)(targetData[5] - mat[0][2]) & g_absMask));
        changed = changed || (g_maxDelta < (float)((uint32_t)(targetData[6] - mat[1][0]) & g_absMask));
        changed = changed || (g_maxDelta < (float)((uint32_t)(targetData[0] - pos[0]) & g_absMask));
        changed = changed || (g_maxDelta < (float)((uint32_t)(targetData[1] - pos[1]) & g_absMask));
        changed = changed || (g_maxDelta < (float)((uint32_t)(targetData[2] - pos[2]) & g_absMask));
        changed = changed || (g_maxDelta < (float)((uint32_t)(targetData[8] - mat[2][0]) & g_absMask));
        changed = changed || (g_maxDelta < (float)((uint32_t)(targetData[9] - mat[2][1]) & g_absMask));
        changed = changed || (g_maxDelta < (float)((uint32_t)(targetData[10] - mat[2][2]) & g_absMask));

        if (changed) {
            resetTargetTracking(pos);
        }
    }

    float finalDir[3]; // local_70/fStack_6c/fStack_68
    finalDir[0] = dir[0];
    finalDir[1] = dir[1];
    finalDir[2] = dir[2];

    // Check flag at byte offset +0x4A4 bit0 (1 means no smoothing)
    uint8_t flags = *(uint8_t*)((uint8_t*)this + 0x4A4);
    if ((~flags & 1) != 0) {
        // Convert direction to local space via virtual call (vtable offset 0x1A8)
        float input[3] = { dir[0], dir[1], dir[2] };
        float output[3];
        typedef void (__thiscall* ConvertFunc)(ChaseCamera*, float*, float*);
        (*(ConvertFunc)(*(void**)this + 0x1A8))(this, input, output);
        finalDir[0] = output[0];
        finalDir[1] = output[1];
        finalDir[2] = output[2];
    }

    // Apply time step scaling
    float scale = g_cameraTimeDelta / g_frameRateDivisor;
    velocityXY.x = finalDir[0] * scale;
    velocityXY.y = finalDir[1] * scale;
    velocityZ   = finalDir[2] * scale;
}