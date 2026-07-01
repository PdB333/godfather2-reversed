// FUNC_NAME: SomeClass::constructor
void __thiscall SomeClass::constructor(SomeClass *this, int someValue)
{
    this->vtable = (void*)&PTR_FUN_00d76138; // vtable pointer at offset 0
    this->someField0x04 = someValue;          // offset +0x04
    this->field0x08 = 0;                      // offset +0x08
    this->field0x0C = 0;                      // offset +0x0C
    this->field0x10 = 0;                      // offset +0x10
    this->field0x14 = 0;                      // offset +0x14
    this->field0x18 = 0;                      // offset +0x18
    this->field0x1C = 0;                      // offset +0x1C
    this->field0x20 = 0;                      // offset +0x20
    *(uint8_t*)((uintptr_t)this + 0x24) = 0;  // byte at offset +0x24
    *(uint8_t*)((uintptr_t)this + 0x25) = 0;  // byte at offset +0x25
}
```