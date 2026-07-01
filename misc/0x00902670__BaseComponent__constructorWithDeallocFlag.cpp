// FUNC_NAME: BaseComponent::constructorWithDeallocFlag
// Role: Constructor that calls base constructor and optionally deallocates the object if flag bit 0 is set.
// This pattern is seen in EA EARS engine for conditional memory management (e.g., placement new vs heap allocation).
// Class size is 0x8c (140 bytes).

undefined4 __thiscall BaseComponent::constructorWithDeallocFlag(undefined4 this, byte flag)
{
    // Call base class constructor (likely initializes fields at +0x00 to +0x??)
    BaseComponent::baseConstructor(); // FUN_009025e0

    // If the low bit of flag is set, deallocate this object with size 0x8c
    if ((flag & 1) != 0) {
        operatorDelete(this, 0x8c); // FUN_0043b960 – sized deallocation
    }

    // Return the constructed object
    return this;
}