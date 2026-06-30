// FUNC_NAME: Entity::cullCheck

int __fastcall Entity::cullCheck(int this)
{
    float* playerPos;
    float dx, dy, dz;
    float distSq;

    // Check if either of two active flags (bit 0 at +0x54, +0x56) are clear
    if (((*(byte*)(this + 0x54) & 1) == 0) || ((*(byte*)(this + 0x56) & 1) == 0))
    {
        // If the entity is not marked for removal (dword at +0xd0 == 0), keep it
        if (*(int*)(this + 0xd0) == 0)
        {
            return 1;
        }
        // Only perform distance check if enough global time has passed since last check
        if (g_gameTime < *(float*)(this + 0x58))
        {
            return 0;
        }
        // Get player world position
        playerPos = getPlayerPosition();
        dx = playerPos[0] - *(float*)(this + 0xc0);  // +0xc0: position.x
        dy = playerPos[1] - *(float*)(this + 0xc4);  // +0xc4: position.y
        dz = playerPos[2] - *(float*)(this + 0xc8);  // +0xc8: position.z
        distSq = dx*dx + dy*dy + dz*dz;
        // If squared distance exceeds the stored threshold (+0x58), remove the entity
        if (*(float*)(this + 0x58) <= distSq)
        {
            removeEntity();
            return 1;
        }
    }
    return 0;
}