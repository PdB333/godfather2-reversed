// FUNC_NAME: SimObject::SimObject
void __thiscall SimObject::SimObject() {
    // +0x00: vtable pointer
    *reinterpret_cast<void**>(this) = &PTR_FUN_00d8c088;
    // +0x08: pointer to static table (likely function or data)
    reinterpret_cast<void**>(this)[2] = &PTR_LAB_00d8c080;
    // +0x60: another pointer to static table (e.g., method table or string table)
    reinterpret_cast<void**>(this)[0x18] = &PTR_LAB_00d8c070;
    // Call base class constructor (takes this via ecx)
    FUN_004083d0();
    // Call additional initialization (takes this via ecx)
    FUN_00473a60();
}