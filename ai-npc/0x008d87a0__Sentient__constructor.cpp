// FUNC_NAME: Sentient::constructor

int __thiscall Sentient::constructor(Sentient *this, byte flags)
{
    // Call base class constructor (likely EARSObject or Entity)
    baseConstructor();

    // If bit 0 is set, allocate a sub-object of size 0x190 (400)
    if ((flags & 1) != 0)
    {
        // Allocate and initialize a component or child object
        // FUN_0043b960 is likely memory allocation or placement new
        allocateSubObject(this, 400);
    }

    return (int)this;
}