// FUNC_NAME: EngineCore::~EngineCore
// Address: 0x00486360 - Destructor: Releases global subsystem references, deletes child object, and signals shutdown.

void __thiscall EngineCore::~EngineCore(EngineCore* this)
{
    // Set vtable pointer to derived class vtable (pre-destruction)
    this->m_pVtable = (int*)&PTR_FUN_00e3379c;              // +0x00
    // Set secondary vtable to initial shutdown vtable
    this->m_pVtable3 = (int*)&PTR_LAB_00e337ac;            // +0x0C

    // Release global subsystem references (likely decrement refcount and unregister)
    SUB_release(&DAT_0120eca8);   // g_pSubsystem1
    SUB_release(&DAT_0120ecb8);   // g_pSubsystem2
    SUB_release(&DAT_01206778);   // g_pSubsystem3
    SUB_release(&DAT_012067b4);   // g_pSubsystem4

    // Decrement reference counts (or final release)
    SUB_decrementRef(&DAT_0120eca8);   // g_pSubsystem1
    SUB_decrementRef(&DAT_0120ecb8);   // g_pSubsystem2
    SUB_decrementRef(&DAT_0120ecb0);   // g_pSubsystem5
    SUB_decrementRef(&DAT_01206778);   // g_pSubsystem3
    SUB_decrementRef(&DAT_012067b4);   // g_pSubsystem4

    // Delete attached child object if present
    if (this->m_pChild != NULL)                              // +0x10
    {
        SUB_deleteOrRelease(this->m_pChild);                // FUN_009c8f10
    }

    // Update secondary vtable to destroyed state (prevents virtual calls during destruction)
    this->m_pVtable3 = (int*)&PTR_LAB_00e337b0;            // +0x0C

    // Global flag indicating engine shutdown complete (0 = not shutting down)
    g_bEngineShutdown = 0;                                   // _DAT_01223498

    // Final cleanup sequence
    SUB_shutdownCleanup();                                   // FUN_004083d0
}