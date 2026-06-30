// FUNC_NAME: GodfatherGameManager::initialize

void* GodfatherGameManager::initialize() {
    // Call base class initialization
    FUN_006126d0();
    
    // Zero initialize all members
    m_member1 = 0;    // +0x120? Actually address 0x0121a310
    m_member2 = 0;    // +0x124
    m_member3 = 0;    // +0x128
    m_vtable = &gVtable;  // +0x0 (set to vtable pointer)
    m_member4 = 0;    // +0xC0
    m_member5 = 0;    // +0xC4
    m_member6 = 0;    // +0xC8
    m_member7 = 0;    // +0xCC
    m_member8 = 0;    // +0x100
    m_member9 = 0;    // +0x104
    m_member10 = 0;   // +0x108
    m_member11 = 0;   // +0x10C
    m_member12 = 0;   // +0x110
    m_member13 = 0;   // +0x114
    m_member14 = 0;   // +0x118
    // Return pointer to the object (vtable slot)
    return &m_vtable;
}