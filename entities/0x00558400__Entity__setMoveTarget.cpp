// FUNC_NAME: Entity::setMoveTarget
// Address: 0x00558400
// Sets a 2D target position (two floats) for an entity's movement data.

void __thiscall Entity::setMoveTarget(float targetX, float targetY) {
    // Pointer to movement component at offset +0x1c
    MovementComponent* movComp = *(MovementComponent**)(this + 0x1c);
    TargetData* targetData = nullptr;
    if (movComp != nullptr) {
        // The movement component holds a pointer to target data at offset +0x10
        targetData = *(TargetData**)(movComp + 0x10);
    }
    if (targetData != nullptr) {
        // Set target X and Y at offsets +0x40 and +0x44
        *(float*)(targetData + 0x40) = targetX;
        *(float*)(targetData + 0x44) = targetY;
    }
}