// FUNC_NAME: Entity::isDead
bool __thiscall Entity::isDead(Entity* this) {
    bool bDead = false;
    // +0x10: likely m_pPhysicsComponent or m_pModel
    // +0x18: likely m_pGameComponent or m_pCollision
    // +0x3c: m_flags (bit0 = dead flag, bit1 = dying flag)
    if ( (*(int*)((int)this + 0x18) == 0 && *(int*)((int)this + 0x10) == 0) ||
         ((*(unsigned int*)((int)this + 0x3c) >> 1) & 1) ||
         (*(unsigned char*)((int)this + 0x3c) & 1) )
    {
        bDead = true;
    }
    return bDead;
}