// FUNC_NAME: SomeComponent::SomeComponent(bool allocFlag)
__thiscall SomeComponent::SomeComponent(bool allocFlag) {
    // Set primary vtable (class SomeComponent)
    this->vtable = reinterpret_cast<SomeComponentVTable*>(0x00d5d840); // +0x00
    // Set additional vtable pointers for multiple inheritance (offset 0x3C and 0x48)
    this->field_0x3C = reinterpret_cast<SomeInterfaceVTable*>(0x00d5d830); // param_1[0xF]
    this->field_0x48 = reinterpret_cast<AnotherInterfaceVTable*>(0x00d5d82c); // param_1[0x12]
    // Call base class constructor
    BaseComponent::BaseComponent(); // FUN_0046c640
    // If heap-allocated, deallocate memory (custom memory management pattern)
    // Note: This flag (bit 0) indicates whether memory should be freed after construction.
    if (allocFlag & 1) {
        deallocateMemory(this, sizeof(SomeComponent)); // FUN_0043b960, size 0x90
    }
    return this;
}