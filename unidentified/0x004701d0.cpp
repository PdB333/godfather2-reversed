// FUN_004701d0: GameEntity::computeDirectionToTarget

void __thiscall GameEntity::computeDirectionToTarget(const float* targetPos, float param) {
    // Compute vector from this entity's position (offsets +0x100, +0x104, +0x108) to target
    float diffX = targetPos[0] - *(float*)((char*)this + 0x100);
    float diffY = targetPos[1] - *(float*)((char*)this + 0x104);
    float diffZ = targetPos[2] - *(float*)((char*)this + 0x108);

    // Call helper function to process the direction
    FUN_004700a0(&diffX, param);
}