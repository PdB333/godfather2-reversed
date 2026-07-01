//FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void __fastcall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this)
{
    // Set vtable pointer (offset +0x00)
    this->vtable = &PTR_FUN_00d840e0;
    // Set base class vtable or other pointer (offset +0x10)
    this->field_0x10 = &PTR_LAB_00d840b8;
    // Set another pointer (offset +0x4C)
    this->field_0x4C = &PTR_LAB_00d840a8;
    // Set another pointer (offset +0x58)
    this->field_0x58 = &PTR_LAB_00d840a4;

    // Initialize global static data (e.g., singleton state)
    FUN_004086d0(&DAT_01130460);

    // If some counter (offset +0x5C) is positive, perform additional init
    if (0 < (int)this->field_0x5C) {
        FUN_0040eaf0(1);
    }

    // Overwrite the pointer at offset +0x58 with a different vtable
    this->field_0x58 = &PTR_LAB_00d840a0;

    // Reset global flag
    DAT_0112981c = 0;

    // Continue initialization
    FUN_004083d0();
    FUN_005c16e0();
}