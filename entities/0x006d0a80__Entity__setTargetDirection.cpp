// FUNC_NAME: Entity::setTargetDirection

// Reconstructed from 0x006d0a80 - Sets 2D velocity towards a target position
// Offsets:
// +0x30 : positionX (float)
// +0x38 : positionZ (float)
// +0x50 : velocityX (float)
// +0x54 : velocityY (float) - always set to 0
// +0x58 : velocityZ (float)
// +0x5c : unused/unknown - always set to 0
// Global _DAT_00d5780c : gMaxSpeed (float) - max movement speed for this entity

void __thiscall Entity::setTargetDirection(float *targetPos) {
    float fVar1;
    float fVar2;
    float distance;

    // Reset vertical velocity components
    this->velocityY = 0.0f;          // +0x54
    *(undefined4 *)(this + 0x5c) = 0;  // +0x5c also zeroed (likely third velocity component or flag)

    // Compute 2D delta (x, z) from current position to target
    fVar1 = targetPos[0] - this->positionX; // +0x30
    fVar2 = targetPos[2] - this->positionZ; // +0x38

    distance = SQRT(fVar2 * fVar2 + fVar1 * fVar1);

    if (distance > 0.0f) {
        // Normalize direction and scale by max speed
        float scale = gMaxSpeed / distance; // _DAT_00d5780c
        this->velocityX = scale * fVar1;    // +0x50
        this->velocityZ = scale * fVar2;    // +0x58
    }
}