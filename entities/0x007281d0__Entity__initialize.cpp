// FUNC_NAME: Entity::initialize
// Address: 0x007281d0
// Role: Initialize entity state, sets initial byte flag, calls base init function, then sets a state flag bit

void Entity::initialize()
{
    // +0x150: Some boolean/byte flag (e.g., m_bInitialized or m_bActive)
    this->m_bInitialized = 0;

    // Call global or static initialization function (likely sets up some subsystem)
    // FUN_00726ca0 - assumed to be a base initialization routine
    someGlobalInitFunction();

    // +0x110: Flags field (e.g., m_flags or m_stateFlags)
    // OR with 0x1000000 (bit 24) to mark something (e.g., kFlag_NeedsUpdate or kFlag_Ready)
    this->m_flags |= 0x1000000;
}