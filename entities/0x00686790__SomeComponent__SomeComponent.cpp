// FUNC_NAME: SomeComponent::SomeComponent
// Address: 0x00686790
// Role: Constructor for a component class (size 0x74 bytes)
void __thiscall SomeComponent::SomeComponent(byte flag)
{
    // Call base class constructor (subobject initialization)
    BaseClass::BaseClass();

    // If bit 0 of flag is set, deallocate the object's memory.
    // This pattern is used for exception-safe construction or placement new cleanup.
    if (flag & 1) {
        memoryDeallocator(this, 0x74); // 0x74 = sizeof(SomeComponent)
    }
}