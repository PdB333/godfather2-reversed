// FUNC_NAME: ObjectBase::Constructor
// Address: 0x00814d50
// Role: Constructor. Calls base initializer at 0x00814ce0. If flag bit 0 is set, calls 0x009c8eb0 (e.g., registration or additional setup).

ObjectBase* __thiscall ObjectBase::Constructor(ObjectBase* this, uint8_t flags) {
    // Base class initialization (e.g., vtable setup, member zeroing)
    baseConstructor(); // FUN_00814ce0

    // Optional post-construction step (common pattern in EARS for dynamic allocation or registration)
    if (flags & 1) {
        postConstructorSetup(this); // FUN_009c8eb0
    }

    return this;
}