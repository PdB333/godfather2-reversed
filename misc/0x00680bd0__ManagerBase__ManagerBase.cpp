// FUNC_NAME: ManagerBase::ManagerBase
int __thiscall ManagerBase::ManagerBase(ManagerBase *this, byte flags) {
    // Set vtable pointer at offset +0x20
    if (this != 0) {
        *(void**)((char*)this + 0x20) = (void*)&PTR_LAB_00d580c8;
    }
    // Reset static singleton flag
    DAT_011298b4 = 0;
    // Perform base initialization
    FUN_007edfb0();
    // If bit0 of flags set, run additional setup
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this);
    }
    return (int)this;
}