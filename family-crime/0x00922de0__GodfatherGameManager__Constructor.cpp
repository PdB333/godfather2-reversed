// FUNC_NAME: GodfatherGameManager::Constructor
void __fastcall GodfatherGameManager::Constructor(GodfatherGameManager* this)
{
    // Set vtable pointer to derived class vtable (offset +0x00)
    this->vtable = &PTR_FUN_00d866a4;
    // Set base vtable pointer (offset +0x04) – likely for multiple inheritance
    this->baseVtable = &PTR_LAB_00d86694;

    // Call base class constructor with a class ID hash (0xC914145C)
    // This is typical of EARS engine component initialization
    BaseConstructor(0xc914145c);

    // After base construction, reassign vtable pointers to final vtables
    this->baseVtable = &PTR_LAB_00e30fe0;   // alternative base vtable
    this->vtable = &PTR_LAB_00d86690;       // final derived vtable

    // Reset a global initialization flag (DAT_0113001c == 0 indicates not yet started)
    g_SomeGlobalFlag = 0;
}