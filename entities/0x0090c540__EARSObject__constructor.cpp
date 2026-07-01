// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(EARSObject* this)
{
    // vtable pointer at offset 0x00
    this->vtable = &EARSObject_vtable;          // PTR_FUN_00d833e0
    // second vtable pointer at offset 0x0C
    this->vtable2 = &EARSObject_vtable2_initial; // PTR_LAB_00d833dc

    // Call base class constructor (likely EARS::Framework::Object)
    // Parameters: pointer to this, flags 2 and 2
    EARSObject::initBase(&this, 2, 2);          // FUN_0068dd10

    // Check if a dynamically allocated member at offset 0x14 exists
    if (this->somePointer != 0)                 // param_1[5]
    {
        EARSObject::releaseMember(this->somePointer); // FUN_004daf90
    }

    // Update second vtable to a different implementation
    this->vtable2 = &EARSObject_vtable2_final;  // PTR_LAB_00d833d8

    // Clear global singleton flag
    g_earsObjectSingletonFlag = 0;              // DAT_011298f8

    // Perform post-construction initialization
    EARSObject::postConstructor();              // FUN_004083d0
}