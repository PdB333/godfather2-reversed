// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager

void __fastcall GodfatherGameManager::~GodfatherGameManager(GodfatherGameManager* this)
{
    // Set vtable to derived class vtable
    this->vtable = &PTR_FUN_00d69dd4;
    this->field_0x04 = &PTR_LAB_00d69dd0;

    // Call base class destructor
    baseDestructor(this);

    // Release global resources (called twice for two subsystems)
    releaseResource();
    releaseResource();

    // Free owned sub-objects if they exist
    if (this->m_pSubObjectB != nullptr) {
        deallocate(this->m_pSubObjectB); // offset +0x14
    }
    if (this->m_pSubObjectA != nullptr) {
        deallocate(this->m_pSubObjectA); // offset +0x08
    }

    // Update vtable to base class vtable (prevents double deletion)
    this->field_0x04 = &PTR_LAB_00d69dcc;

    // Mark system as shut down
    g_bInitialized = 0;
}