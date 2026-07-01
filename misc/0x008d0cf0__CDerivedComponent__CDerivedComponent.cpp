// FUNC_NAME: CDerivedComponent::CDerivedComponent
// Address: 0x008d0cf0
// Constructor for a derived component with multiple interface vtables. 
// Sets up base class, vtable, and two additional function pointer tables at offsets +0x3C (0x0F*4) and +0x48 (0x12*4).
// Then calls a subsystem initializer with argument 8 (flags/type).

undefined4* __thiscall CDerivedComponent::CDerivedComponent(undefined4* this, undefined4 param_2)
{
    // Call base class constructor (likely CBaseComponent)
    CBaseComponent::CBaseComponent(param_2);

    // Set main vtable pointer (Ghidra data symbol: PTR_FUN_00d7cf4c)
    *this = &vtable_CDerivedComponent; // +0x00

    // Set secondary vtable at offset +0x3C (60 bytes)
    this[0x0F] = &vtable_AdditionalInterface1; // +0x3C

    // Set tertiary vtable at offset +0x48 (72 bytes)
    this[0x12] = &vtable_AdditionalInterface2; // +0x48

    // Initialize or allocate subsystem; argument 8 possibly indicates a specific subsystem ID
    InitSubsystem(8);

    return this;
}