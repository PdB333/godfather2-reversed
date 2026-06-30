// FUNC_NAME: Entity::setTransformAndEnable
void __thiscall Entity::setTransformAndEnable(Entity *this, float *position) {
    // +0xBC is likely m_bEnabled or m_bActive flag
    *(int32_t *)((uint8_t *)this + 0xBC) = 1;

    // Position is a float3 (x,y,z) passed as three values
    // DAT_00e2b1a4 is a global (e.g., a singleton pointer or time value)
    float x = position[0];
    float y = position[1];
    float z = position[2];
    float globalParam = *(float *)0x00e2b1a4;

    // Set position/transform of this entity (callee takes x,y,z, globalParam)
    FUN_00414aa0(x, y, z, globalParam);
}