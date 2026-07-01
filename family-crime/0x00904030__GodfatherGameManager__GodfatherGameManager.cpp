// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Function address: 0x00904030
// Identifier: Constructor for a core game manager class with multiple vtables and sub-objects.

// EA EARS engine class – suspected GodfatherGameManager based on offsets and initialization pattern.

void __fastcall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager *this)
{
    // Set primary vtable (base class)
    *(void **)this = (void *)&PTR_FUN_00d81fd0;          // +0x00 vtable[0]

    // Set secondary and tertiary vtables (multiple inheritance)
    this->field_0x3C = (void *)&PTR_LAB_00d81fc0;        // +0x3C (offset 0x0F*4)
    this->field_0x48 = (void *)&PTR_LAB_00d81fbc;        // +0x48 (offset 0x12*4)

    // Initialize global/static resource at DAT_012069c4
    FUN_004086d0(&DAT_012069c4);                         // likely initGlobalResource

    // Initialize and set up five sub-objects (embedded at known offsets)
    // Each sub-object appears to be small (8 bytes?) and is initialized in pairs.
    FUN_004086d0(&this->subObject1);                     // +0x80 (offset 0x20*4)
    FUN_00408310(&this->subObject1);                     // +0x80 secondary init

    FUN_004086d0(&this->subObject2);                     // +0x88 (offset 0x22*4)
    FUN_00408310(&this->subObject2);                     // +0x88

    FUN_004086d0(&this->subObject3);                     // +0x90 (offset 0x24*4)
    FUN_00408310(&this->subObject3);                     // +0x90

    FUN_004086d0(&this->subObject4);                     // +0x98 (offset 0x26*4)
    FUN_00408310(&this->subObject4);                     // +0x98

    FUN_004086d0(&this->subObject5);                     // +0xA0 (offset 0x28*4)
    FUN_00408310(&this->subObject5);                     // +0xA0

    // Release existing dynamically allocated objects if they are non-null
    if (this->ptr_0x78 != NULL)                          // +0x78 (offset 0x1E*4)
    {
        FUN_004daf90(this->ptr_0x78);                    // likely releaseObject
    }
    if (this->ptr_0x70 != NULL)                          // +0x70 (offset 0x1C*4)
    {
        FUN_004daf90(this->ptr_0x70);                    // releaseObject
    }

    // Finalize construction (e.g., register with engine, start subsystems)
    FUN_0046c640();
    return;
}