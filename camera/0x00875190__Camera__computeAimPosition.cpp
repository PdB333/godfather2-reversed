// FUNC_NAME: Camera::computeAimPosition
void __thiscall Camera::computeAimPosition(float *outPosition, float *direction)
{
    float scale;
    float localDirection[3];
    int transformPtr;

    transformPtr = getPlayerTransform(); // FUN_00471610 - returns pointer to player/camera transform
    // Copy position from transform (offset 0x30: x, y, z)
    outPosition[0] = *(float *)(transformPtr + 0x30);
    outPosition[1] = *(float *)(transformPtr + 0x34);
    outPosition[2] = *(float *)(transformPtr + 0x38);

    if (direction == (float *)0x0) {
        direction = localDirection;
    }
    computeDirection(direction); // FUN_008750c0 - fills direction with a unit vector (e.g., forward)

    // Scale factor from camera settings (this+0x360 -> settings struct, offset 0x104)
    scale = *(float *)(*(int *)(this + 0x360) + 0x104);
    outPosition[0] = direction[0] * scale + outPosition[0];
    outPosition[1] = direction[1] * scale + outPosition[1];
    outPosition[2] = direction[2] * scale + outPosition[2];
}