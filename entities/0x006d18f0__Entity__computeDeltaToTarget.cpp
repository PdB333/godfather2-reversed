// FUNC_NAME: Entity::computeDeltaToTarget
void __thiscall Entity::computeDeltaToTarget(int thisPtr, float* targetPosition) {
    char shouldUpdate = arePositionsValid((float*)(thisPtr + 0x10), targetPosition); // +0x10: currentPosition (vec4)
    if (shouldUpdate != '\0') {
        float deltaY = targetPosition[1];
        float deltaZ = targetPosition[2];
        float deltaW = targetPosition[3];
        *(float*)(thisPtr + 0x60) = targetPosition[0] - *(float*)(thisPtr + 0x10); // +0x60: velocity.x
        *(float*)(thisPtr + 0x64) = deltaY - *(float*)(thisPtr + 0x14); // +0x64: velocity.y
        *(float*)(thisPtr + 0x68) = deltaZ - *(float*)(thisPtr + 0x18); // +0x68: velocity.z
        *(float*)(thisPtr + 0x6c) = deltaW - *(float*)(thisPtr + 0x1c); // +0x6c: velocity.w
    }
}