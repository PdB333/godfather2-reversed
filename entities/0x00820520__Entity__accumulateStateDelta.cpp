// FUNC_NAME: Entity::accumulateStateDelta
void __thiscall Entity::accumulateStateDelta(Entity* this, const Entity* src, float fScale)
{
    // this->m_scalar (offset 0x54)
    *(float*)((uint32_t)this + 0x54) = *(float*)((uint32_t)src + 0x54) * fScale + *(float*)((uint32_t)this + 0x54);

    // this->m_quaternion (offset 0x80, 4 floats)
    float fX = *(float*)((uint32_t)src + 0x84);
    float fY = *(float*)((uint32_t)src + 0x88);
    float fZ = *(float*)((uint32_t)src + 0x8C);
    *(float*)((uint32_t)this + 0x80) = *(float*)((uint32_t)src + 0x80) * fScale + *(float*)((uint32_t)this + 0x80);
    *(float*)((uint32_t)this + 0x84) = fX * fScale + *(float*)((uint32_t)this + 0x84);
    *(float*)((uint32_t)this + 0x88) = fY * fScale + *(float*)((uint32_t)this + 0x88);
    *(float*)((uint32_t)this + 0x8C) = fZ * fScale + *(float*)((uint32_t)this + 0x8C);

    // this->m_linearVelocity (offset 0x90, 4 floats)
    fX = *(float*)((uint32_t)src + 0x94);
    fY = *(float*)((uint32_t)src + 0x98);
    fZ = *(float*)((uint32_t)src + 0x9C);
    *(float*)((uint32_t)this + 0x90) = *(float*)((uint32_t)src + 0x90) * fScale + *(float*)((uint32_t)this + 0x90);
    *(float*)((uint32_t)this + 0x94) = fX * fScale + *(float*)((uint32_t)this + 0x94);
    *(float*)((uint32_t)this + 0x98) = fY * fScale + *(float*)((uint32_t)this + 0x98);
    *(float*)((uint32_t)this + 0x9C) = fZ * fScale + *(float*)((uint32_t)this + 0x9C);
}