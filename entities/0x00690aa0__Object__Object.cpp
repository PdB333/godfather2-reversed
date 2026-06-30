// FUNC_NAME: Object::Object
// Address: 0x00690aa0
// Constructor with optional initialization flag (bit 0)

void* __thiscall Object::Object(uint8_t flags)
{
    // Call base class constructor at 0x00690a00
    FUN_00690a00(this);

    // If bit 0 of flags is set, call additional initialization at 0x009c8eb0
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}