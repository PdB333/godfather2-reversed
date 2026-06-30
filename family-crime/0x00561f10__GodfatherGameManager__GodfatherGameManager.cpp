// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void GodfatherGameManager::GodfatherGameManager(void)
{
    // Initialize vtable pointer (offset 0x00)
    this->vtable = &g_VTable_00e3a428;

    // Set configuration values
    this->field_0x3C = 4;          // +0x3C
    this->field_0x40 = 2;          // +0x40
    this->field_0x44 = 0;          // +0x44
    this->field_0x60 = 0;          // +0x60
    this->field_0x80 = 0;          // +0x80
    this->field_0x84 = 0;          // +0x84
    this->field_0x88 = 0;          // +0x88

    // Set function pointers and data pointers
    this->field_0x90 = &g_Data_00dc3dd4;  // +0x90
    this->field_0x94 = g_Constant_00e2b1a4; // +0x94
    this->field_0x98 = g_Constant_00e2b1a4; // +0x98
    this->field_0x9C = g_Constant_00e446bc; // +0x9C
    this->field_0xA0 = g_Constant_00e446bc; // +0xA0
    this->field_0xA4 = g_Constant_00e446bc; // +0xA4
    this->field_0xA8 = 0;          // +0xA8
    this->field_0xAC = 0;          // +0xAC

    // Overwrite earlier assignment (likely intended)
    this->field_0x8C = &g_Func_00e3a038;  // +0x8C function pointer
    this->field_0x90 = &g_Data_00e3a054;  // +0x90 (replaces previous)

    // Additional fields
    this->field_0xC0 = 0;          // +0xC0
    this->field_0xB0 = 0;          // +0xB0
    this->field_0xB4 = 0;          // +0xB4
    this->field_0xB8 = 0;          // +0xB8
    this->field_0xBC = 0;          // +0xBC

    // More initialization
    this->field_0x14 = 0;          // +0x14
    this->field_0x18 = g_Constant_00e2b334; // +0x18
    this->field_0x24 = 0;          // +0x24
    this->field_0x28 = 0;          // +0x28
    this->field_0x2C = 0;          // +0x2C
    this->field_0x30 = 0;          // +0x30
    this->field_0x34 = 0;          // +0x34
    this->field_0x38 = 0;          // +0x38

    // Last set of fields (offsets from 0x10 to 0x20?)
    this->field_0x10 = g_Constant_00e39f98; // +0x10
    this->field_0x1C = g_Constant_00e2cd54; // +0x1C
    this->field_0x20 = g_Constant_00e2cd54; // +0x20

    return;
}