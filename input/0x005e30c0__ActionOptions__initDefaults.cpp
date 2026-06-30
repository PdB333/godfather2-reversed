// FUNC_NAME: ActionOptions::initDefaults
// Function at 0x005e30c0 - initializes default state for ActionOptions object
void __thiscall ActionOptions::initDefaults(ActionOptions *this)
{
    // Set member flags (booleans) to defaults
    this->field_0x8 = 1;   // +0x8  likely m_bool1
    this->field_0xC = 0;   // +0xC
    this->field_0x10 = 0;  // +0x10
    this->field_0x14 = 0;  // +0x14
    this->field_0x18 = 1;  // +0x18 likely m_bool2
    this->field_0x1C = 0;  // +0x1C
    this->field_0x20 = 0;  // +0x20
    this->field_0x24 = 0;  // +0x24
    this->field_0x28 = 0;  // +0x28
    this->field_0x29 = 0;  // +0x29

    // Initialize vector/color from global constants
    this->m_defaultVector.x = DAT_00e2b1a4; // +0x2C
    this->m_defaultVector.y = DAT_00e2b04c; // +0x30
    this->m_defaultVector.z = DAT_00e2b050; // +0x34

    // Clear remaining fields
    this->field_0x38 = 0;  // +0x38
    this->field_0x3C = 0;  // +0x3C
    this->field_0x40 = 0;  // +0x40
    this->field_0x44 = 0;  // +0x44

    // Call secondary initialization
    FUN_005e3130();
}