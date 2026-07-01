// FUNC_NAME: SomeClass::SomeClass
// Address: 0x008d12d0
// Role: Constructor with an initialization flag. Calls a base class constructor (0x008d1030)
// and conditionally performs additional setup (0x009c8eb0) when (flag & 1) is set.

SomeClass* __thiscall SomeClass::SomeClass(SomeClass* this, byte flag)
{
    // Base class initialization (likely EARSObject or framework base)
    baseConstructor(this);

    // If flag bit 0 is set, execute extended initialization
    if ((flag & 1) != 0) {
        postInit(this);
    }

    return this;
}