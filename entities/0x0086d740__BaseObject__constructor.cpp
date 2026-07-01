// FUNC_NAME: BaseObject::constructor
// Address: 0x0086d740 - Initializes derived object, clears flags fields at +0x6c
void __fastcall BaseObject::constructor(BaseObject* this)
{
    // Call base class initializer (likely parent constructor)
    FUN_0086cc70();

    // Clear bits 5-7 (mask 0xffffff1f) of the flags field at offset +0x6c
    // These bits might represent state or type flags that should be reset.
    this->m_flags &= 0xffffff1f;
}