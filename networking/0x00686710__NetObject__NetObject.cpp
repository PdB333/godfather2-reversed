// FUNC_NAME: NetObject::NetObject
// Function address: 0x00686710
// Role: Constructor for NetObject (or similar multi-base class). Sets up multiple vtable pointers (offsets 0x00, 0x3C, 0x48),
// calls base class constructor (FUN_008b2820), and conditionally performs a deallocation call (likely operator delete) based on a flag.
// The flag (param_2) bit 0 indicates heap allocation; if set, the object is freed after construction? This pattern is unusual
// but may be related to pool or placement new cleanup.

NetObject* NetObject::NetObject(uint8_t allocFlags) {
    // Set primary vtable (offset 0x00)
    this->vtable = reinterpret_cast<void**>(PTR_FUN_00d589e4);
    // Set secondary vtable for first base class (offset 0x3C = 15 * 4)
    *reinterpret_cast<void***>(reinterpret_cast<uint8_t*>(this) + 0x3C) = reinterpret_cast<void**>(PTR_LAB_00d589d4);
    // Set tertiary vtable for another base class (offset 0x48 = 18 * 4)
    *reinterpret_cast<void***>(reinterpret_cast<uint8_t*>(this) + 0x48) = reinterpret_cast<void**>(PTR_LAB_00d589d0);
    // Call base constructor (likely Core::Object or similar)
    BaseClass::BaseClass(); // 0x008b2820
    // If allocated from heap (allocFlags & 1), perform cleanup (probably operator delete with size 0x68)
    if (allocFlags & 1) {
        operator delete(this, 0x68); // 0x0043b960
    }
    return this;
}