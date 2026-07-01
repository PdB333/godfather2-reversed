// FUNC_NAME: SomeComponent::SomeComponent
// Address: 0x007e7890
// Role: Constructor for SomeComponent, calls base class constructor and optionally initializes with a flag byte.

// Note: Base constructor at 0x007e7670, conditional initialization at 0x00624da0.

__thiscall SomeComponent::SomeComponent(byte flags)
{
    // Call base class constructor (likely BaseComponent or similar)
    BaseComponent::BaseComponent();

    // If bit 0 of flags is set, perform additional initialization
    if ((flags & 0x1) != 0) {
        this->initializeExtra(flags);  // FUN_00624da0 - actual name unknown
    }

    return this;
}