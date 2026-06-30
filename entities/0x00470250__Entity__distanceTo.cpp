// FUNC_NAME: Entity::distanceTo
// Function at 0x00470250: compute Euclidean distance from this entity's position (stored at offsets 0x100, 0x104, 0x108) to a given 3D point.
// This is a __thiscall method.
float Entity::distanceTo(float* point) const
{
    // entity position stored at offsets 0x100 (x), 0x104 (y), 0x108 (z)
    float dx = point[0] - *(float*)((int)this + 0x100);
    float dy = point[1] - *(float*)((int)this + 0x104);
    float dz = point[2] - *(float*)((int)this + 0x108);
    return sqrt(dx * dx + dy * dy + dz * dz);
}