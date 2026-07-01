// FUNC_NAME: BaseClass::initializeVtables
void __thiscall BaseClass::initializeVtables(BaseClass* this) {
    // Global pointer used during construction to track this object
    g_pCurrentConstructingObject = reinterpret_cast<uint32_t*>(this) + 1; // offset +0x04 (secondary vtable slot)

    // Set secondary vtable to interface1
    *g_pCurrentConstructingObject = reinterpret_cast<uint32_t>(&vtable_BaseInterface1); // 0x00d74698

    // Set primary vtable at offset 0
    *reinterpret_cast<uint32_t*>(this) = reinterpret_cast<uint32_t>(&vtable_BaseClass); // 0x00d74758

    // Overwrite secondary vtable with the actual derived interface vtable
    *g_pCurrentConstructingObject = reinterpret_cast<uint32_t>(&vtable_BaseInterface2); // 0x00d746f8
}