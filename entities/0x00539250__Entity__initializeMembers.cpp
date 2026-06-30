// FUNC_NAME: Entity::initializeMembers
void __fastcall Entity::initializeMembers(Entity *this)
{
    // Call base class initializer (likely EARSObject or similar)
    UnknownBaseClass::initialize(); // FUN_00612e00

    // Zero out various member fields
    // Offsets are based on the class layout
    *(int *)((char *)this + 0x10) = 0;  // +0x10: likely m_positionX or m_velocityX
    *(int *)((char *)this + 0x14) = 0;  // +0x14: likely m_positionY or m_velocityY
    *(int *)((char *)this + 0xa4) = 0;  // +0xA4: e.g., m_health, m_flags, or m_state
    *(int *)((char *)this + 0xe0) = 0;  // +0xE0: e.g., m_animState, m_teamID
    *(int *)((char *)this + 0x120) = 0; // +0x120: e.g., m_inventoryIndex, m_networkSeq
    *(int *)((char *)this + 0x124) = 0; // +0x124: e.g., m_inventoryCount, m_networkAck
    *(int *)((char *)this + 0x180) = 0; // +0x180: e.g., m_aiState, m_combatMode
    *(int *)((char *)this + 0x184) = 0; // +0x184: e.g., m_aiSubstate, m_combatTarget
    *(int *)((char *)this + 0x1c0) = 0; // +0x1C0: e.g., m_physicsState, m_collisionFlags
    *(int *)((char *)this + 0x230) = 0; // +0x230: e.g., m_pendingAction, m_decisionTimer
    *(int *)((char *)this + 0x250) = 0; // +0x250: e.g., m_vehicleComponent, m_currentGadget
    *(int *)((char *)this + 0x134) = 0; // +0x134: e.g., m_damageState, m_coverState
    *(int *)((char *)this + 0x138) = 0; // +0x138: e.g., m_damageTimer, m_coverTimer
}