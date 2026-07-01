//FUNC_NAME: Entity::isOverlappingSphere
bool __thiscall Entity::isOverlappingSphere(Entity* other) const
{
    // Position offsets: +0x10 = x, +0x14 = y (unused), +0x18 = z
    float dx = *(float*)(this + 0x10) - *(float*)(other + 0x10);
    float dz = *(float*)(this + 0x18) - *(float*)(other + 0x18);
    // Bounding radius at +0x1c
    float radiusSum = *(float*)(other + 0x1c) + *(float*)(this + 0x1c);
    // 2D circle overlap test (ignoring y)
    return (dx * dx + dz * dz) < (radiusSum * radiusSum);
}