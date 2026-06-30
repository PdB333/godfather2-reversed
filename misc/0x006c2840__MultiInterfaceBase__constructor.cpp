// FUNC_NAME: MultiInterfaceBase::constructor
// Address: 0x006c2840
// Role: Constructor for a class with multiple inheritance (multiple vtable pointers) and zero-initialized fields
// Calls base constructor at 0x004737b0 then FUN_006c1360

// The object layout (all offsets in bytes):
// +0x00: primary vtable (PTR_FUN_00d5ef08)
// +0x3C: second vtable (PTR_LAB_00d5eef8)   (param_1[0xF])
// +0x48: third vtable  (PTR_LAB_00d5eef4)   (param_1[0x12])
// +0x50: fourth vtable (PTR_LAB_00d5eef0)   (param_1[0x14])
// +0x58: uint32 field (initially 0)         (param_1[0x16])
// +0x5C: uint32 field (initially 0)         (param_1[0x17])
// +0x60: uint32 field (initially 0)         (param_1[0x18])
// +0x64: uint32 field (initially 0)         (param_1[0x19])

MultiInterfaceBase* __thiscall MultiInterfaceBase::constructor(MultiInterfaceBase* this) {
    // Base class constructor
    BaseClass::constructor(this);  // FUN_004737b0

    // Set the vtable pointers for multiple interfaces
    this->vtablePrimary      = &PTR_FUN_00d5ef08;   // +0x00
    *reinterpret_cast<void**>(reinterpret_cast<uint32_t>(this) + 0x3C) = &PTR_LAB_00d5eef8;  // +0x3C
    *reinterpret_cast<void**>(reinterpret_cast<uint32_t>(this) + 0x48) = &PTR_LAB_00d5eef4;  // +0x48
    *reinterpret_cast<void**>(reinterpret_cast<uint32_t>(this) + 0x50) = &PTR_LAB_00d5eef0;  // +0x50

    // Zero-initialize fields
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(this) + 0x58) = 0;
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(this) + 0x5C) = 0;
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(this) + 0x60) = 0;
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint32_t>(this) + 0x64) = 0;

    // Post-initialization
    FUN_006c1360(this);  // derived class-specific setup

    return this;
}