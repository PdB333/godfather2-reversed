// FUNC_NAME: EARSObject::EARSObject (constructor at 0x00842ad0)
void __thiscall EARSObject::EARSObject(EARSObject* this) {
    // Base constructor call (FUN_00598d80)
    BaseClass::BaseClass();

    if (this != 0) {
        // Set vtable pointer (PTR_LAB_00d74620)
        this->vtable = &EARSObject_vtable;
    } else {
        // Static instance initialization (ppuRam00000000)
        g_pEARSObjectSingleton = &EARSObject_vtable;
    }
}