// FUNC_NAME: CGameManager::CGameManager
// Function at 0x0090fb40 - Constructor for a game manager singleton
// Initializes base class, sets up multiple vtable pointers, zeros many fields, stores global pointer
// Object size at least 0x90 bytes

void * __fastcall CGameManager::CGameManager(CGameManager *this)
{
    // Call base class constructor (likely some common base)
    BaseClass::Constructor(this);

    // Set vtable pointer at offset 0x4C (third vtable)
    this->m_pVtable3 = &g_Vtable3;

    // Store this as global singleton
    g_pTheGameManager = this;

    // Set primary vtable at offset 0x00
    this->m_pVtableMain = &g_VtableMain;

    // Set secondary vtable at offset 0x10
    this->m_pVtableSecondary = &g_VtableSecondary;

    // Set vtable pointer at offset 0x4C (override previous? might be different member)
    // This appears to be a separate vtable for an interface or subclass
    this->m_pVtableThird = &g_VtableThird;

    // Zero-initialize a large block from offset 0x50 to 0x8D
    // Fields at offsets 0x50, 0x54, ... 0x88: 15 int-sized fields
    // Followed by two bytes at offsets 0x8C and 0x8D
    this->field_0x50 = 0;
    this->field_0x54 = 0;
    this->field_0x58 = 0;
    this->field_0x5C = 0;
    this->field_0x60 = 0;
    this->field_0x64 = 0;
    this->field_0x68 = 0;
    this->field_0x6C = 0;
    this->field_0x70 = 0;
    this->field_0x74 = 0;
    this->field_0x78 = 0;
    this->field_0x7C = 0;
    this->field_0x80 = 0;
    this->field_0x84 = 0;
    this->field_0x88 = 0;
    this->byte_0x8C = 0;
    this->byte_0x8D = 0;

    return this;
}