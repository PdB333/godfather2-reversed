// FUNC_NAME: SpatialObject::isPointInRange
bool __thiscall SpatialObject::isPointInRange(float* point, float extraRadius)
{
    float dx = *(float *)(this + 0x10) - point[0];           // +0x10: x position
    float dz = *(float *)(this + 0x18) - point[2];           // +0x18: z position (y likely unused)
    float combinedRadius = *(float *)(this + 0x1c) + extraRadius; // +0x1c: base radius (e.g., collision or detection radius)
    return (dx * dx + dz * dz) < (combinedRadius * combinedRadius);
}