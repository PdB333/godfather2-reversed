// FUNC_NAME: UnknownClass::constructor
void __fastcall UnknownClass_ctor(int thisPtr)
{
    // Call base class constructor (FUN_0059b5e0)
    FUN_0059b5e0();
    // Initialize member fields at offsets 0x70–0x7C
    *(uint8_t*)(thisPtr + 0x70) = 0;  // m_bSomeFlag
    *(uint32_t*)(thisPtr + 0x74) = 0; // m_dwValue1
    *(uint32_t*)(thisPtr + 0x78) = 0; // m_dwValue2
    *(uint32_t*)(thisPtr + 0x7C) = 0; // m_dwValue3
}