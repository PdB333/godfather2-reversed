// FUNC_NAME: ChaseCamera::update
// Address: 0x006ce840
// Role: Update camera interpolation and orientation for a ChaseCamera (EARS engine).
// This function interpolates the camera position and look direction toward target values,
// constructs a view matrix, and handles special flags for debug/transition.

#include <cmath>

class ChaseCamera {
public:
    // Member offsets (relative to this pointer):
    // +0x00: vtable
    // +0x04 - +0xBF: other base data
    // +0xC0: m_modeA (int, 0=unknown, 0x48=inactive)
    // +0xC8 (200): m_modeB (int, 0=unknown, 0x48=inactive)
    // +0xD8: m_interpSpeed (float)
    // +0xDC: m_flags (uint, bit19: debug flag, bit11: force snap)
    // +0xE0 - +0x164: orientation/quaternion data for interpolation
    // +0x134: m_curPos (float3)
    // +0x140: m_curVel (float3, possibly velocity or up?)
    // +0x14C: m_targetPos (float3)
    // +0x158: m_targetVel (float3)
    // +0x20: m_worldPos (float3, output position)
    // +0x30: m_worldDir (float3, output look direction)
    // +0x40 - +0x48: output matrix (4x4? stored as 12 floats)
    // +0x44: part of matrix

    void __thiscall update(void* cameraParams);

private:
    // Helper functions likely defined elsewhere
    void initCameraParams(void* params);     // 0x006c85e0
    void computeOrientation(int a, int b, int c, int d, int e, int f, int g, int h); // 0x006cd8a0
    void applyDebugScale();                  // 0x006cc3f0
    void setDebugTimeScale(float scale);     // 0x00473bb0
    float getDeltaTime(void* params);        // 0x006cdb20, returns double
    void* getPlayerCharacter();              // 0x00471610, returns pointer to player object
    void buildViewMatrix(float* pos, float* dir, int zero, float* out1, float* out2, float* out3); // 0x00473bc0
    float vectorLengthSq(float* a, float* b); // from code, computed manually
    // 0x006ca5e0: normalise/slerp? used on vectors
    // 0x006cccc0: notify camera collision? or reset
};

void __thiscall ChaseCamera::update(void* cameraParams)
{
    // Globals (likely in .data)
    extern float DAT_00e445c8; // debug time scale factor
    extern float _DAT_00d5780c; // default interpolation factor (maybe 1.0??)
    extern int* DAT_012233a0;   // pointer to some global singleton (maybe game manager)
    extern float DAT_00d5f1a0;  // squared distance threshold for snapping
    extern float DAT_00d5efb8;  // distance threshold for interpolation

    initCameraParams(cameraParams); // 0x006c85e0

    // Early exit if camera modes are 0 or 0x48
    if (*(int*)(this + 0xC0) == 0) return;
    if (*(int*)(this + 0xC0) == 0x48) return;
    if (*(int*)(this + 0xC8) == 0) return;
    if (*(int*)(this + 0xC8) == 0x48) return;

    // Compute orientation quaternion? from offset fields
    computeOrientation(this + 0xE0, this + 0xEC, this + 0xF8,
                       this + 0x104, this + 0x110, this + 0x11C,
                       this + 0x128, this + 0x164); // 0x006cd8a0

    // If debug flag (bit 19) is set, apply debug time scale
    if ((*(uint*)(this + 0xDC) >> 19) & 1) {
        applyDebugScale();                   // 0x006cc3f0
        setDebugTimeScale(*(float*)(this + 0xD8) * DAT_00e445c8); // 0x00473bb0
        *(uint*)(this + 0xDC) &= 0xFFF7FFFF; // clear bit 19
    }

    // Get interpolation factor from delta time
    double dt = getDeltaTime(cameraParams); // 0x006cdb20
    float interpFactor = (float)dt;

    // If force snap flag (bit 11) is set, snap immediately
    if ((*(uint*)(this + 0xDC) >> 11) & 1) {
        *(uint*)(this + 0xDC) &= 0xFFFFF7FF; // clear bit 11
        interpFactor = _DAT_00d5780c; // use default factor (likely 1.0)
    }

    // Player object pointer for distance check
    void* playerObj = 0;
    if (**(int**)(DAT_012233a0 + 4) != 0) {
        playerObj = **(int**)(DAT_012233a0 + 4) - 0x1F30; // adjust offset
        if (playerObj != 0) {
            void* player = getPlayerCharacter(); // 0x00471610
            float dx = *(float*)(this + 0x134) - *(float*)(player + 0x30);
            float dy = *(float*)(this + 0x138) - *(float*)(player + 0x34);
            float dz = *(float*)(this + 0x13C) - *(float*)(player + 0x38);
            float distSq = dx*dx + dy*dy + dz*dz;
            if (distSq >= DAT_00d5f1a0 * DAT_00d5f1a0) { // actually comparison is squared vs squared? The decompiled compares squared dist to scalar (likely squared threshold)
                // Snap target directly
                *(float*)(this + 0x134) = *(float*)(this + 0x14C);
                *(float*)(this + 0x138) = *(float*)(this + 0x150);
                *(float*)(this + 0x13C) = *(float*)(this + 0x154);
                *(float*)(this + 0x140) = *(float*)(this + 0x158);
                *(float*)(this + 0x144) = *(float*)(this + 0x15C);
                *(float*)(this + 0x148) = *(float*)(this + 0x160);
            }
        }
    }

    // Position difference
    float dx1 = *(float*)(this + 0x13C) - *(float*)(this + 0x154);
    float dy1 = *(float*)(this + 0x138) - *(float*)(this + 0x150);
    float dz1 = *(float*)(this + 0x134) - *(float*)(this + 0x14C);
    // Velocity difference
    float dvx = *(float*)(this + 0x140) - *(float*)(this + 0x158);
    float dvy = *(float*)(this + 0x144) - *(float*)(this + 0x15C);
    float dvz = *(float*)(this + 0x148) - *(float*)(this + 0x160);

    float posDistSq = dx1*dx1 + dy1*dy1 + dz1*dz1;
    float velDistSq = dvx*dvx + dvy*dvy + dvz*dvz;

    if (DAT_00d5efb8 <= sqrt(posDistSq) || DAT_00d5efb8 <= sqrt(velDistSq)) {
        // Interpolate position
        *(float*)(this + 0x134) = (*(float*)(this + 0x134) - *(float*)(this + 0x14C)) * interpFactor + *(float*)(this + 0x14C);
        *(float*)(this + 0x138) = (*(float*)(this + 0x138) - *(float*)(this + 0x150)) * interpFactor + *(float*)(this + 0x150);
        *(float*)(this + 0x13C) = (*(float*)(this + 0x13C) - *(float*)(this + 0x154)) * interpFactor + *(float*)(this + 0x154);

        // Copy to world position
        float defaultVal = _DAT_00d5780c;
        *(float*)(this + 0x20) = *(float*)(this + 0x134);
        *(float*)(this + 0x24) = *(float*)(this + 0x138);
        *(float*)(this + 0x2C) = defaultVal; // w component?
        *(float*)(this + 0x28) = *(float*)(this + 0x13C);

        // Store previous positions
        *(float*)(this + 0x14C) = *(float*)(this + 0x134);
        *(float*)(this + 0x150) = *(float*)(this + 0x138);
        *(float*)(this + 0x154) = *(float*)(this + 0x13C);

        // Interpolate velocity/look direction
        float* velPtr = (float*)(this + 0x140);
        *velPtr = (*velPtr - *(float*)(this + 0x158)) * interpFactor + *(float*)(this + 0x158);
        *(float*)(this + 0x144) = (*(float*)(this + 0x144) - *(float*)(this + 0x15C)) * interpFactor + *(float*)(this + 0x15C);
        *(float*)(this + 0x148) = (*(float*)(this + 0x148) - *(float*)(this + 0x160)) * interpFactor + *(float*)(this + 0x160);

        // Copy to world direction
        *(float*)(this + 0x30) = *velPtr;
        *(float*)(this + 0x34) = *(float*)(this + 0x144);
        *(float*)(this + 0x38) = *(float*)(this + 0x148);
        *(float*)(this + 0x3C) = defaultVal; // w component?

        // Build view matrix
        buildViewMatrix(this + 0x20, this + 0x30, 0, this + 0x44, this + 0x40, this + 0x48); // 0x00473bc0

        // Store target velocity for next frame
        *(float*)(this + 0x158) = *velPtr;
        *(float*)(this + 0x15C) = *(float*)(this + 0x144);
        *(float*)(this + 0x160) = *(float*)(this + 0x148);
    }

    // Normalize/lookAt final orientation
    float localVec[3];
    localVec[0] = *(float*)(this + 0x20);
    localVec[1] = *(float*)(this + 0x24);
    localVec[2] = *(float*)(this + 0x28);
    float result = normaliseOrSlerp(velPtr, &localVec, &localVec); // 0x006ca5e0, modifies localVec
    *(float*)(this + 0x20) = localVec[0];
    *(float*)(this + 0x24) = localVec[1];
    *(float*)(this + 0x28) = localVec[2];
    *(float*)(this + 0x2C) = _DAT_00d5780c;

    // If interpolation factor < 1 and player has a certain flag, trigger something
    if (result < 1.0f && playerObj != 0 && (*(byte*)(playerObj + 0x8E4) & 1) != 0) {
        notifyCameraTransition(); // 0x006cccc0
    }
}