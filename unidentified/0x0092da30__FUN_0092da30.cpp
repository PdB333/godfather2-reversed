// FUNC_NAME: SomeClass::reset
// Address: 0x0092da30
// Resets the object: releases the resource pointed to by the first field, then zeroes all fields.

struct SomeClass {
    void* m_pResource; // +0x00
    int m_nSomeFlag;   // +0x04
    int m_nSomeOther;  // +0x08
};

void __fastcall SomeClass::reset(SomeClass* this)
{
    this->m_nSomeFlag = 0;
    // Release the resource (likely a global function at 0x009c8f10)
    FUN_009c8f10(this->m_pResource);
    this->m_pResource = 0;
    this->m_nSomeOther = 0;
}