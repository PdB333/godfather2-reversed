// FUNC_NAME: PositionFollower::updatePosition
// Function at 0x00755fa0 - Updates position of a follower attachment based on target ID and flags.
// Offsets: this+0x58 = flags (byte), this+0x64 = followTargetID (int), this+0x6c = output position (Vector3*)
// When bit 0x20 of flags is set, uses a different calculation path involving two calls to getObjectFromPool and one to ComputeFollowPosition.
// This function returns a pointer to the internal position vector.

#include <cstdint>

// Forward declarations of engine functions (inferred)
void* __fastcall getObjectFromPool();      // FUN_00471610 - returns some object pointer
void __fastcall ComputeFollowPosition();   // FUN_00755600 - possibly updates internal state

struct Vector3 {
    float x, y, z;
};

class PositionFollower {
public:
    // +0x58: flags byte
    uint8_t flags;
    // padding to align?
    // +0x64: target ID (0 means no target, 0x48 may be a special value)
    int32_t followTargetID;
    // +0x6c: output position (12 bytes)
    Vector3 followPosition;

    // Returns pointer to the updated position
    Vector3* __fastcall updatePosition() {
        // Check if a valid target exists and it's not the special ID 0x48
        if (followTargetID != 0 && followTargetID != 0x48) {
            if (flags & 0x20) {
                // Alternate path: double call to get an object, then compute position
                getObjectFromPool();
                getObjectFromPool();
                ComputeFollowPosition();
            } else {
                // Standard path: get the target object and copy its position
                void* targetObject = getObjectFromPool();
                // Copy 12 bytes from targetObject+0x30 (position) + targetObject+0x38 (extra float)
                // The copy covers x, y, z from +0x30 and one more float from +0x38
                // In practice, this copies a 3D vector; using memcpy for clarity
                __builtin_memcpy(&followPosition, reinterpret_cast<const void*>(
                    reinterpret_cast<uintptr_t>(targetObject) + 0x30), 12);
            }
        }
        return &followPosition;
    }
};