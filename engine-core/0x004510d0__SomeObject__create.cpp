// FUNC_NAME: SomeObject::create
SomeObject* __thiscall SomeObject::create(byte flag)
{
    // +0x00: base initialize method (likely sets up vtable or default members)
    baseInit();
    // If bit 0 of flag is set, perform additional initialization (e.g., allocate resources)
    if ((flag & 1) != 0) {
        specialInit(this); // +0x00: this pointer passed for additional setup
    }
    return this;
}