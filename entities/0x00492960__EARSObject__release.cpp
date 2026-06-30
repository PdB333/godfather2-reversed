// FUNC_NAME: EARSObject::release
void __thiscall EARSObject::release(void) {
    // Call base class cleanup (likely base destructor or common finalization)
    destroyBase();  // FUN_00491d70

    // If the resource pointer at offset +0x220 is non‑null, free it
    if (this->m_pResource != 0) {
        freeResource();  // FUN_006063b0
    }
}