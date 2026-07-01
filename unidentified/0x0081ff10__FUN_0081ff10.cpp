// FUNC_NAME: SomeComponent::constructor
// Function address: 0x0081ff10
// Role: Constructor for a component or manager class, initializes vtable and several fields to zero.

undefined4 * __thiscall SomeComponent::SomeComponent(undefined4 *this, undefined4 initParam)
{
    // Call base class constructor or initializer with initParam
    FUN_00833b10(initParam);

    // Set vtable pointer (+0x00)
    *this = &PTR_FUN_00d73364;

    // Set function pointers at offsets +0x3C and +0x48
    this[0xf] = &PTR_LAB_00d73354;   // +0x3C: some function pointer or callback
    this[0x12] = &PTR_LAB_00d73350;  // +0x48: another function pointer

    // Initialize five consecutive integers at offsets +0xE4 through +0xF4 to zero
    this[0x39] = 0;  // +0xE4
    this[0x3a] = 0;  // +0xE8
    this[0x3b] = 0;  // +0xEC
    this[0x3c] = 0;  // +0xF0
    this[0x3d] = 0;  // +0xF4

    // Additional initialization call
    FUN_0081fe60(initParam);

    return this;
}