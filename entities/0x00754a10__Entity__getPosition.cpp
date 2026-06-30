// FUNC_NAME: Entity::getPosition
// Address: 0x00754a10
// Role: Returns the position of the entity, either from cached data or via virtual call to physics body.
void __thiscall Entity::getPosition(Vec3* outPos)
{
    // +0x54: m_pPhysicsBody (pointer to a physics component / transform)
    int* physicsBody = *(int**)(this + 0x54);

    if (physicsBody == nullptr)
    {
        // No physics body: zero out the output position
        outPos->x = 0.0f;
        outPos->y = 0.0f;
        outPos->z = 0.0f;
        return;
    }

    // +0x94: m_flags (bit 0 indicates direct position cache)
    if ((*(byte*)(this + 0x94) & 1) != 0)
    {
        // Direct position copy from physics body cache
        // physicsBody offsets: +0x424 (Vec3 position?), +0x42C (extra float?)
        // Actually reading 8 bytes (Vec2?) then 4 bytes -> treat as Vec3 (12 bytes)
        outPos->x = *(float*)(physicsBody + 0x109); // offset 0x424
        outPos->y = *(float*)((int)physicsBody + 0x428);
        outPos->z = *(float*)(physicsBody + 0x10b); // offset 0x42C
        return;
    }

    // Fallback: virtual call through physics body vtable at offset 0x4c
    // The called function fills outPos from the physics body's data
    (**(code**)(*physicsBody + 0x4c))();
}