// FUNC_NAME: Animated::Animated
// Function at 0x0053c6d0 - constructor for Animated class, initializes two fields to zero
void __thiscall Animated::Animated(Animated *this)
{
    FUN_00612e00(); // base class constructor or global initializer
    *(int *)((char *)this + 0x10) = 0; // +0x10: some flag or pointer
    *(int *)((char *)this + 0x14) = 0; // +0x14: some flag or counter
}