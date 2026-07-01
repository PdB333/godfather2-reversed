//FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::destructor(EARSObject* this)
{
    // Call virtual function at vtable offset 0x28 (likely finalize/release)
    (*(void (__thiscall**)(EARSObject*))(*(uint32_t*)DAT_01129a74 + 0x28))(this);

    // Clear low 2 bits of flags at offset 0x66
    *(uint16_t*)((uint8_t*)this + 0x66) &= 0xFFFC;

    // Global cleanup/deallocation function
    FUN_005c1880();
}