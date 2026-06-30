// FUNC_NAME: CGameSystem::CGameSystem

void __fastcall CGameSystem::CGameSystem(CGameSystem* this)
{
    // Set base class vtable pointers (likely for multiple inheritance)
    this->vtable0 = (void**)&PTR_FUN_00e31e98;      // +0x00
    this->vtable1 = (void**)&PTR_LAB_00e31ea4;      // +0x04
    // Call base constructor (e.g., CBaseSystem::CBaseSystem)
    FUN_0043e380(this);
    // Update vtable pointers to derived class layout
    this->vtable1 = (void**)&PTR_LAB_00e31ea8;      // +0x04
    this->vtable0 = (void**)&PTR_LAB_00e30ea0;      // +0x00
    // Initialize global flag indicating system is not yet ready
    g_bSystemInitialized = 0;                        // _DAT_01223468
}