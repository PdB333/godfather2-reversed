// FUNC_NAME: Gun::invertOrientation
// Address: 0x00776980
// Toggles an inversion flag, swaps quaternion components (XY ↔ ZW), copies to target,
// updates a float field, and calls render manager to set a shader parameter "r_weapon".

#include <cstdint>

// External globals (from game data)
extern float DAT_01205224;       // some time or factor
extern float DAT_00e44578;       // adjustment value
extern float _DAT_00d5c458;      // another global float

// External functions
extern void FUN_005430c0(int target, float* quat); // likely updates target transform
extern void* FUN_00800a90();                        // returns render manager singleton

class Gun {
public:
    void __thiscall invertOrientation();

    // Offsets:
    // +0x5C: m_pTarget (int*) - pointer to another object
    // +0x70: m_nState (int) - state flag
    // +0x80: m_quatX, m_quatY, m_quatZ, m_quatW (float[4])
    // +0xA0: m_fltA0 (float) - some time-dependent value
    // +0xAC: m_nFlags (uint32) - bit field
    static_assert(sizeof(float) == 4, "float must be 4 bytes");
};

void __thiscall Gun::invertOrientation() {
    int* pTargetObj = *reinterpret_cast<int**>(this + 0x5C); // +0x5C

    // Toggle bit 1 of flags at +0xAC
    uint32_t& flags = *reinterpret_cast<uint32_t*>(this + 0xAC);
    if ((flags >> 1) & 1) {
        flags &= 0xFFFFFFFD; // clear bit 1
    } else {
        flags |= 2; // set bit 1
    }

    // Save old quaternion components X and Y
    float& quatX = *reinterpret_cast<float*>(this + 0x80);
    float& quatY = *reinterpret_cast<float*>(this + 0x84);
    float& quatZ = *reinterpret_cast<float*>(this + 0x88);
    float& quatW = *reinterpret_cast<float*>(this + 0x8C);

    float oldX = quatX;
    float oldY = quatY;

    // Swap: X ← Z, Y ← W, Z ← oldX, W ← oldY
    quatX = quatZ;
    quatY = quatW;
    quatZ = oldX;
    quatW = oldY;

    // Copy new quaternion to target object if valid
    if (pTargetObj) {
        *reinterpret_cast<float*>(pTargetObj + 0x860) = quatX; // +0x860
        *reinterpret_cast<float*>(pTargetObj + 0x864) = quatY; // +0x864
    }

    // Check state at +0x70
    int state = *reinterpret_cast<int*>(this + 0x70);
    if (state != 0 && state != 0x48) {
        FUN_005430c0(reinterpret_cast<int>(pTargetObj), reinterpret_cast<float*>(this + 0x80));
    }

    // Update float at +0xA0 with global values
    float fVar5 = DAT_01205224;
    if (DAT_01205224 < 0.0f) {
        fVar5 += DAT_00e44578;
    }
    *reinterpret_cast<float*>(this + 0xA0) = fVar5 + _DAT_00d5c458;

    // Call render manager to set shader parameter "r_weapon"
    int* pMgr = reinterpret_cast<int*>(FUN_00800a90()); // get render manager
    if (pMgr) {
        // vtable call at offset +0x7C (likely a pre-update method)
        (*(void(**)(void))(pMgr[0] + 0x7C))();
        // vtable call at offset +0x154: setShaderParameter(target, "r_weapon", 0)
        (*(void(**)(int, const char*, int))(pMgr[0] + 0x154))(*reinterpret_cast<int*>(this + 0x5C), "r_weapon", 0);
    }
}