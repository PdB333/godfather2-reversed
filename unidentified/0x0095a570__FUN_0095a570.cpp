//FUNC_NAME: SomeClass::initialize
// Function address: 0x0095a570
// Role: Initializes the object, optionally calling a cleanup/destructor if a flag is set.
// The base class constructor at 0x00959ff0 is always called first.
// If param_2 (byte) has bit 0 set, a conditional destructor/cleanup at 0x005c4480 is invoked on this.

undefined4 __thiscall SomeClass::initialize(SomeClass* this, byte flags)
{
    // Call base class constructor or common initialization routine
    baseClassConstructor(); // FUN_00959ff0

    // If the lowest bit of flags is set, perform additional cleanup/destruction
    if ((flags & 1) != 0) {
        conditionalDestructor(this); // FUN_005c4480
    }

    return this;
}