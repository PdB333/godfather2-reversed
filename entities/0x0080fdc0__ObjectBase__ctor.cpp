// FUNC_NAME: ObjectBase::ctor
undefined4 __thiscall ObjectBase::ctor(byte allocationFlag) {
    // Initialize base class (likely calls base constructor at address 0x80f7c0)
    baseConstructor();

    // If the allocation flag's lowest bit is set, register or track the memory block
    // (0x130 = 304 bytes, the object's size)
    if ((allocationFlag & 1) != 0) {
        registerMemoryAllocation(this, 0x130);  // e.g., EAMemory::debugRegister
    }

    return this;  // Return pointer to the constructed object (common pattern in EA engines)
}