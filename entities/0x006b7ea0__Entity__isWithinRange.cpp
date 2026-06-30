// FUNC_NAME: Entity::isWithinRange
bool Entity::isWithinRange(const float* point, float multiplier, bool twoDimensional) const
{
    // Offsets: +0x50 = position.x, +0x54 = position.y, +0x58 = position.z, +0x5C = squaredRadius
    float dx, dy, dz, distSq;

    if (!twoDimensional) {
        // 3D distance check
        dx = *(float*)((uintptr_t)this + 0x50) - point[0];
        dy = *(float*)((uintptr_t)this + 0x54) - point[1];
        dz = *(float*)((uintptr_t)this + 0x58) - point[2];
        distSq = dx*dx + dy*dy + dz*dz;
    } else {
        // 2D distance check (ignore Y)
        dx = point[0] - *(float*)((uintptr_t)this + 0x50);
        dz = point[2] - *(float*)((uintptr_t)this + 0x58);
        distSq = dx*dx + dz*dz;
    }

    // Compare against squared radius scaled by multiplier
    float radiusSq = *(float*)((uintptr_t)this + 0x5C);
    return distSq < (radiusSq * multiplier);
}