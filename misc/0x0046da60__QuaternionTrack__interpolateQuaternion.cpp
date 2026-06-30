// FUNC_NAME: QuaternionTrack::interpolateQuaternion
// Address: 0x0046da60
// Role: Interpolates between two quaternion keyframes based on a time value, normalizes the result, and stores the final quaternion (with forced W component) into an output buffer.
// Game logic: This appears to be part of a keyframed quaternion animation system. The object (this) holds an array of keyframes (each 0x30 bytes) with a quaternion at offset 0 and a time at offset 0x24. The function interpolates between the current keyframe (index at +0x61) and the next, using a slerp-like approach (likely via FUN_0056db60), then normalizes the quaternion, transforms it via FUN_0056cef0, and writes the result to a target structure at unaff_ESI+0x30. The final W component is forced to DAT_00e2b1a4 (probably 1.0). If only one keyframe exists, the current keyframe's quaternion is used directly.

// Note: The decompiled code uses registers in_EAX (this) and unaff_ESI (output target). The exact layout is reconstructed from known EA EARS engine patterns.

struct Quaternion { float x, y, z, w; };

class QuaternionTrack {
public:
    // Offset table (relative to this):
    // +0x00: keyframe array (each element 0x30 bytes)
    // +0x60: uint8 keyframeCount
    // +0x61: uint8 currentIndex
    // Keyframe structure (0x30 bytes):
    //   +0x00: float quat[4] (16 bytes)
    //   +0x10: padding? (0x14 bytes)
    //   +0x24: int time

    static const float kEpsilonLengthSq = 0.0f; // DAT_00e2cbe0 (likely 0.0, preventing division by zero)
    static const float kForceW = 1.0f;           // DAT_00e2b1a4 (assumed 1.0, used to finalize W)

    void interpolateQuaternion(int time, Quaternion* outQuat) {
        uint8* keyframeCountPtr = reinterpret_cast<uint8*>(this) + 0x60;
        uint8* currentIdxPtr = reinterpret_cast<uint8*>(this) + 0x61;
        uint8 keyframeCount = *keyframeCountPtr;
        uint8 currentIdx = *currentIdxPtr;

        if (keyframeCount > 1) {
            // Interpolate between current and next keyframe
            int nextIdx = currentIdx + 1; // Note: potential wrap could be handled elsewhere
            float* quatCurrent = reinterpret_cast<float*>(this + currentIdx * 0x30);
            float* quatNext    = reinterpret_cast<float*>(this + nextIdx * 0x30);
            int*   timeCurrent = reinterpret_cast<int*>(this + currentIdx * 0x30 + 0x24);
            int*   timeNext    = reinterpret_cast<int*>(this + nextIdx * 0x30 + 0x24);

            int diff = *timeCurrent - *timeNext; // May be negative (next > current)
            if (diff != 0) {
                float t = static_cast<float>(time - *timeNext) / static_cast<float>(diff);
                // FUN_0056db60 performs SLERP or similar interpolation
                Quaternion interpQuat;
                FUN_0056db60(t, quatNext, quatCurrent, &interpQuat);

                // Normalize the interpolated quaternion
                float magSq = interpQuat.x * interpQuat.x +
                              interpQuat.y * interpQuat.y +
                              interpQuat.z * interpQuat.z +
                              interpQuat.w * interpQuat.w;
                if (magSq > kEpsilonLengthSq) {
                    float invMag = 1.0f / sqrtf(magSq);
                    interpQuat.x *= invMag;
                    interpQuat.y *= invMag;
                    interpQuat.z *= invMag;
                    interpQuat.w *= invMag;
                } else {
                    // If degenerate, set to zero (original code multiplies by 0.0)
                    interpQuat = {0.0f, 0.0f, 0.0f, 0.0f};
                }

                // FUN_0056cef0 likely converts the quaternion to the final representation
                Quaternion* converted = FUN_0056cef0(&interpQuat);
                *outQuat = *converted;
            }
        } else {
            // Only one keyframe: use current directly
            float* quatCurrent = reinterpret_cast<float*>(this + currentIdx * 0x30);
            Quaternion* converted = FUN_0056cef0(quatCurrent);
            *outQuat = *converted;
        }

        // Force the W component (offset +0x3c) to a fixed value (probably 1.0)
        // This overwrites whatever was computed.
        outQuat->w = kForceW;
    }
};