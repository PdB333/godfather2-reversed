// FUNC_NAME: EARSObject::EARSObject

undefined4* __thiscall EARSObject::EARSObject(undefined4* this, byte allocFlag) {
    // Set vtable pointer (base class)
    *this = (undefined4*)&PTR_FUN_00e3343c;           // +0x00: base vtable
    
    // Set additional vtable pointers (likely for multiple inheritance / interfaces)
    this[0x0f] = (undefined4*)&PTR_LAB_00e33458;     // +0x3C: second vtable
    this[0x12] = (undefined4*)&PTR_LAB_00e33468;     // +0x48: third vtable
    this[0x14] = (undefined4*)&PTR_LAB_00e3346c;     // +0x50: fourth vtable (overwritten below)
    this[0x14] = (undefined4*)&PTR_LAB_00e33470;     // +0x50: overwritten with another vtable
    
    // Clear global flag
    DAT_0122348c = 0;                                 // Global state initialization
    
    // Call sub-initialization routine
    sub_46C640();
    
    // If allocFlag indicates this was allocated, call a destructor-like function
    // via a function pointer stored at offset 0x2d4 of a global object
    if ((allocFlag & 1) != 0) {
        (**(code**)(**(int**)(DAT_01223410 + 0x2d4) + 4))(this, 0);
    }
    
    return this;
}