// FUNC_NAME: CGameApp::CGameApp
void __thiscall CGameApp::CGameApp(CGameApp *this, int configParam1, int configParam2, int configParam3)
{
    // Global singleton pointer stored
    g_pGameApp = this;
    
    // Vtable setup (from constant pointer at 0x00e337b8)
    this->vtable = (void*)0x00e337b8;
    
    // Zero-initialize many fields
    this->field_4 = 0;      // +0x04
    this->field_1C = 0;     // +0x1C  (offset 7*4)
    this->field_20 = 0;     // +0x20  (offset 8*4)
    this->field_28 = 0;     // +0x28  (offset 10*4)
    this->field_40 = 0;     // +0x40  (offset 0x10*4)
    this->field_44 = 0;     // +0x44  (offset 0x11*4)
    this->field_4C = 0;     // +0x4C  (offset 0x13*4)
    this->field_64 = 0;     // +0x64  (offset 0x19*4)
    this->field_68 = 0;     // +0x68  (offset 0x1A*4)
    this->field_70 = 0;     // +0x70  (offset 0x1C*4)
    this->field_88 = 0;     // +0x88  (offset 0x22*4)
    this->field_8C = 0;     // +0x8C  (offset 0x23*4)
    this->field_94 = 0;     // +0x94  (offset 0x25*4)
    this->field_98 = 0;     // +0x98  (offset 0x26*4)
    this->field_9C = 0;     // +0x9C  (offset 0x27*4)
    this->field_A0 = 0;     // +0xA0  (offset 0x28*4)
    this->field_A4 = 0;     // +0xA4  (offset 0x29*4)
    this->field_A8 = 0;     // +0xA8  (offset 0x2A*4)
    this->field_AC = 0;     // +0xAC  (offset 0x2B*4)
    this->field_B0 = 0;     // +0xB0  (offset 0x2C*4)
    this->field_B4 = 0;     // +0xB4  (offset 0x2D*4)
    
    // Store constructor parameters at offset 0xB8, 0xBC, 0xC0
    this->configParamA = configParam1;   // +0xB8
    this->configParamB = configParam2;   // +0xBC
    this->configParamC = configParam3;   // +0xC0
}