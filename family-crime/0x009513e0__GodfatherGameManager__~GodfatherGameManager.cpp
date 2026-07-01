// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __fastcall GodfatherGameManager::~GodfatherGameManager()
{
    // Set vtable pointers for destruction phase
    this->vtable0 = &PTR_FUN_00d8bd00;           // +0x00: primary vtable
    this->field_0x10 = &PTR_LAB_00d8bcdc;        // +0x10: secondary vtable
    this->field_0x50 = &PTR_LAB_00d8bcd8;        // +0x50: vtable for subobject
    this->field_0x54 = &PTR_LAB_00d8bcc0;        // +0x54: another vtable

    // Release sub-object pointers – these are likely owned components
    releaseObject(this->subObj_0x70);            // +0x70
    releaseObject(this->subObj_0x74);            // +0x74
    releaseObject(this->subObj_0x84);            // +0x84
    releaseObject(this->subObj_0x88);            // +0x88
    releaseObject(this->subObj_0x8C);            // +0x8C
    releaseObject(this->subObj_0x90);            // +0x90
    releaseObject(this->subObj_0x94);            // +0x94

    // Conditionally release optional sub-objects
    if (this->subObj_0x64 != 0) {               // +0x64
        releaseObject(this->subObj_0x64);
    }
    if (this->subObj_0x58 != 0) {               // +0x58
        releaseObject(this->subObj_0x58);
    }

    // Update vtable to indicate fully destroyed state
    this->field_0x50 = &PTR_LAB_00d8bcbc;        // +0x50 -> destroyed vtable

    // Clear global destruction flag
    g_gameDestroying = 0;                       // DAT_01130038

    // Perform final cleanup (e.g., shutdown subsystems)
    cleanupAfterDestruction();                   // FUN_00957d90
}