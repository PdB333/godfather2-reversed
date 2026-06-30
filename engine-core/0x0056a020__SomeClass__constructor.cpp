// FUNC_NAME: SomeClass::constructor
void __thiscall SomeClass::constructor(void *this) {
    int *thisPtr = (int *)this;

    // +0x04: unknown int field (set to 0)
    thisPtr[1] = 0;
    // +0x1c: unknown int field (set to 0)
    thisPtr[7] = 0;
    // +0x120: unknown int field (set to 0)
    thisPtr[0x48] = 0;
    // +0x224: unknown int field (set to 0)
    thisPtr[0x89] = 0;
    // +0x328: unknown int field (set to 0)
    thisPtr[0xca] = 0;
    // +0x32c: unknown int field (set to 0)
    thisPtr[0xcb] = 0;
    // +0x330: byte flag (set to 1)
    *(bool *)((int)this + 0x330) = 1;
    // +0x331: byte flag (set to 0)
    *(bool *)((int)this + 0x331) = 0;
    // +0x00: vtable pointer (set to a static function table at 0x00e3ab30)
    thisPtr[0] = (int)&PTR_FUN_00e3ab30;
    // +0x334: unknown int field (set to 0)
    thisPtr[0xcd] = 0;
    // +0x338: unknown int field (set to 0)
    thisPtr[0xce] = 0;
    // +0x33c: unknown int field (set to 0)
    thisPtr[0xcf] = 0;
    // +0x340: byte flag (set to 0)
    *(bool *)((int)this + 0x340) = 0;
    // +0x344: unknown int field (set to 0)
    thisPtr[0xd1] = 0;
}