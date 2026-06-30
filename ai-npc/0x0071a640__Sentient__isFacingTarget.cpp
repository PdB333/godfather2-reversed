// FUNC_NAME: Sentient::isFacingTarget
// Address: 0x0071a640
// This function determines if the current entity is facing its lock-on target.
// Returns 1 if facing, 2 if not facing (or random if no target).

#define _FACING_THRESHOLD (*reinterpret_cast<float*>(0x00d577a0))

int Sentient::isFacingTarget() {
    int targetObj = FUN_00717700(); // Likely getCurrentTargetObject()
    if (targetObj == 0) {
        uint randVal = _rand();
        // Randomly return 1 or 2 (50% each)
        return 2 - (randVal & 1);
    }

    // Delta vector from this to target
    float dx = *reinterpret_cast<float*>(targetObj + 0x10) - *reinterpret_cast<float*>(this + 0x44); // target.x - this.x
    float dy = *reinterpret_cast<float*>(targetObj + 0x14) - *reinterpret_cast<float*>(this + 0x48); // target.y - this.y
    float dz = *reinterpret_cast<float*>(targetObj + 0x18) - *reinterpret_cast<float*>(this + 0x4C); // target.z - this.z

    // Normalize delta direction
    Math::vector3Normalize(&dx, &dx); // In-place normalize (assumed)

    // Read this's forward direction (stored as 2 floats packed in 8 bytes at 0x20, plus third at 0x28)
    // This layout is unusual; may be a quaternion or packed vector.
    float forwardX = *reinterpret_cast<float*>(this + 0x20);
    float forwardY = *reinterpret_cast<float*>(this + 0x24); // second float from 8-byte block
    float forwardZ = *reinterpret_cast<float*>(this + 0x28);

    // Dot product of normalized delta with forward direction
    float dot = dx * forwardX + dy * forwardY + dz * forwardZ;

    if (_FACING_THRESHOLD < dot) {
        return 1; // Facing
    }
    return 2; // Not facing
}