// FUNC_NAME: GameObject::getRotationQuaternion
// Address: 0x0055b9a0
// Role: Retrieves the rotation quaternion for this game object.
//       If the W component (at +0x7a0) is the sentinel value (DAT_00e2b05c),
//       it computes a default quaternion by calling computeDefaultRotation,
//       stores its W component, then returns.
//       Otherwise, it copies the stored XYZ (at +0x100, 0x104, 0x108) and W
//       into the output quaternion and normalizes it.

#include <cmath>

// Forward declarations of called functions
void __thiscall computeDefaultRotation(float *outQuat);
void normalizeQuaternion(float *quat);

// Global sentinel value for uninitialized rotation
extern const float SENTINEL_ROTATION_W = DAT_00e2b05c; // address 0x00e2b05c

class GameObject {
public:
    // Offsets relative to this pointer:
    // +0x100 : rotation quaternion X component (float)
    // +0x104 : rotation quaternion Y component (float)
    // +0x108 : rotation quaternion Z component (float)
    // +0x7a0 : rotation quaternion W component (float)

    void __thiscall getRotationQuaternion(float *outQuat) {
        float w = *(float *)(this + 0x7a0);
        if (w == SENTINEL_ROTATION_W) {
            // W not initialized – compute default rotation
            computeDefaultRotation(outQuat);
            // Store only the W component back; XYZ remain as is (presumably already correct)
            *(float *)(this + 0x7a0) = outQuat[3];
            return;
        }
        // Copy stored XYZ components
        outQuat[0] = *(float *)(this + 0x100);
        outQuat[1] = *(float *)(this + 0x104);
        outQuat[2] = *(float *)(this + 0x108);
        outQuat[3] = w;
        // Normalize the quaternion to ensure unit length
        normalizeQuaternion(outQuat);
    }
};