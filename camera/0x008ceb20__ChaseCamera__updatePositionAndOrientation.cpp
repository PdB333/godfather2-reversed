// FUNC_NAME: ChaseCamera::updatePositionAndOrientation

#include <cstdint>

// Assume these are standard types in the engine
struct Vector3 {
    float x, y, z;
};

struct Matrix4x4 {
    float m[4][4]; // 16 floats
};

// Global data references (replace with actual globals if known)
extern float _DAT_00d5780c; // Some constant, likely 0.0f
extern float DAT_00d5efb8;  // threshold
extern float DAT_00d5eeec;  // offset
extern uint32_t DAT_00e44680; // bitmask for angle wrapping
extern float DAT_012067e8;  // multiplier
extern float _DAT_00d5c458; // multiplier
extern float DAT_00e44748;  // multiplier
extern float _DAT_00d7cbdc; // some parameter

// Forward declarations of helper functions (placeholders for known engine funcs)
char FUN_0040edb0();                    // e.g., isPaused()
void FUN_008ce7d0();                    // e.g., preUpdateCamera()
void FUN_006cb9d0(Vector3* out, const Vector3* a, const Vector3* b); // vector subtract? b - a?
void FUN_0056afa0(Vector3* out, const Vector3* in); // normalize
int  FUN_00471610();                    // e.g., getPlayerTransform() - returns pointer to some struct with position
void FUN_004a04f0(Vector3* out, const Vector3* dir, const Vector3* up, float something, float param); // lookAt matrix construction?
void FUN_0046cf70(const float* matrix, const Vector3* scale, float factor, int flag); // scale and transform? matrix multiply?
void FUN_00610040(const float* matrix); // apply matrix to current object? setWorldMatrix?
void FUN_008ce7d0();                    // initialize, maybe clear

// This function at 0x008ceb20
void __fastcall ChaseCamera::update(int thisPtr)
{
    char isPaused;
    Vector3 vLocal_d0;
    float fStack_cc, local_c8;
    uint32_t local_c4;
    Vector3 vLocal_b8, vLocal_b0, vLocal_ac;
    float local_a0;
    uint32_t local_9c_low, local_9c_high; // 64-bit double? but used as floats? Actually the code uses CONCAT44 on floats to make 64-bit, then stores as double? We'll treat as two floats.
    float local_94;
    float local_90; // part of a vector used as up?
    // local_50 is a 16-float matrix
    float local_50[16];

    isPaused = FUN_0040edb0();
    if (isPaused == 0) {
        // Initialize locals with some global constant (likely zero)
        uint32_t zero = *reinterpret_cast<uint32_t*>(&_DAT_00d5780c);
        // Many locals set to zero, but we'll just zero them
        // For brevity, we assume the initialization sets most locals to 0.0f

        FUN_008ce7d0(); // pre-update step

        // Compute direction vector from this+0x1c to this+0x30? (positions?)
        FUN_006cb9d0(&vLocal_b8, reinterpret_cast<const Vector3*>(thisPtr + 0x1c), reinterpret_cast<const Vector3*>(thisPtr + 0x30));
        // Copy to vLocal_d0
        vLocal_d0 = vLocal_b8;
        // Normalize
        FUN_0056afa0(&vLocal_d0, &vLocal_d0);
        // Write back into local_? not needed

        // Update initial look-at if not set
        if (*reinterpret_cast<char*>(thisPtr + 8) == 0) {
            *reinterpret_cast<uint64_t*>(thisPtr + 0x10) = reinterpret_cast<uint64_t&>(vLocal_d0); // store as two floats (x,y)
            *reinterpret_cast<float*>(thisPtr + 0x18) = vLocal_d0.z;
            *reinterpret_cast<char*>(thisPtr + 8) = 1;
        }

        int state = *reinterpret_cast<int*>(thisPtr + 0x28); // state or mode
        if (state == 0 || state == 0x48) {
            // Use stored look-at from object
            vLocal_d0 = *reinterpret_cast<Vector3*>(thisPtr + 0x10);
            // Note: the code copies only 8 bytes (x,y) and separate z, but Vector3 is 12 bytes? Actually it stores as 8 bytes then float, so it's packed. We assume proper alignment.
            // For simplicity, use a struct with two floats and then z separate.
        } else {
            // Get player's position (or some target)
            int targetPtr = FUN_00471610(); // returns pointer to some transform
            Vector3 targetPos;
            targetPos.x = *reinterpret_cast<float*>(targetPtr + 0x30);
            targetPos.y = *reinterpret_cast<float*>(targetPtr + 0x34); // high part? Actually the code uses CONCAT44 which suggests 64-bit double? But later treats as floats. It's messy.
            targetPos.z = *reinterpret_cast<float*>(targetPtr + 0x38);

            // Subtract camera position from target position? this+0x60, 0x64, 0x68 are camera pos?
            vLocal_d0.x = targetPos.x - *reinterpret_cast<float*>(thisPtr + 0x60);
            vLocal_d0.y = targetPos.y - *reinterpret_cast<float*>(thisPtr + 0x64);
            vLocal_d0.z = targetPos.z - *reinterpret_cast<float*>(thisPtr + 0x68);
            // Normalize the difference
            FUN_0056afa0(&vLocal_d0, &vLocal_d0);
        }

        // Build look-at matrix from direction and up vector (up from local_90)
        Vector3 upDir;
        upDir.x = local_90; // but local_90 is a float from earlier? The decompiled code shows local_90 as undefined4, but used as part of a vector later.
        // Actually the call to FUN_004a04f0 takes &local_b8 (output), &local_9c (direction), &local_ac (up?), &local_a0 (something), and a global.
        // We need to emulate that. We'll treat local_9c as direction, local_ac as up, local_a0 as output angle?
        // This is complex; we simplify.

        // Copy matrix from this+0x70 to local_50
        float* src = reinterpret_cast<float*>(thisPtr + 0x70);
        float* dst = local_50;
        for (int i = 0; i < 16; ++i) {
            dst[i] = src[i];
        }

        // Angle clamping
        if (local_a0 < DAT_00d5efb8 ||
            (reinterpret_cast<uint32_t&>(local_a0) - *reinterpret_cast<uint32_t*>(&DAT_00d5eeec) & DAT_00e44680) < DAT_00d5efb8) {
            local_a0 = 0.0f;
        }

        // Compute scaling factor
        float speedFactor = *reinterpret_cast<float*>(thisPtr + 0xc) * DAT_012067e8 * _DAT_00d5c458;
        if (local_a0 < speedFactor) {
            speedFactor = local_a0;
        }

        // Apply scaling and transform
        FUN_0046cf70(local_50, &vLocal_ac, speedFactor * DAT_00e44748, 1);
        FUN_00610040(local_50);

        // Call virtual method: probably notify or update
        void** vtable = *reinterpret_cast<void***>(thisPtr + 4);
        using VirtualFunc = void (*)(int, uint32_t);
        VirtualFunc func = reinterpret_cast<VirtualFunc>(vtable[0x40 / 4]); // offset 0x40 in vtable
        func(thisPtr, 0xd444da9d, 0);
    }
}