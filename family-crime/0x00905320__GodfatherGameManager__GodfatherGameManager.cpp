// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void* __fastcall GodfatherGameManager::constructor(GodfatherGameManager* this)
{
    // Call base class constructor (EARSObject or similar)
    FUN_004c26c0(); // EARSObject::constructor(this)

    // Set primary vtable pointer (offset +0x00)
    this->vtable = (void**)(&PTR_FUN_00e2f504);

    // Initialize secondary interface pointer (offset +0x82*4 = 0x208)
    this->m_secondaryVtable = &PTR_LAB_00e2f52c; // Overwrites previous default from base

    // Store global singleton pointer
    g_pGodfatherGameManager = this;

    // Initialize member variables (offsets +0x83, +0x84, +0x85)
    this->m_member1 = 0; // offset +0x20C
    this->m_member2 = 0; // offset +0x210
    this->m_member3 = 0; // offset +0x214

    return this;
}