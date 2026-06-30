// FUN_00453060: Object::constructorWithFlag
// 0x00453060 - Constructor with optional post-initialization flag (bit 0 of param_2).
// Calls base constructor FUN_004530e0, then conditionally calls FUN_009c8eb0(this) if flag bit 0 is set.
// Returns this pointer (as undefined4) to match calling convention.
void* __thiscall Object::constructorWithFlag(Object* this, byte flag) {
    // Call base class constructor or default initialization
    FUN_004530e0();
    // If the lowest bit of flag is set, perform extra initialization/destruction
    if ((flag & 1) != 0) {
        FUN_009c8eb0(this); // likely a post-construction or cleanup routine
    }
    return this;
}