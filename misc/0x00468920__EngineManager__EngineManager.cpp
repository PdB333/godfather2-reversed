// FUNC_NAME: EngineManager::EngineManager

// Constructor for the EngineManager singleton.
// Sets up two vtable pointers (primary at +0x00, secondary at +0x04) and stores the
// instance globally (DAT_01223474). Then calls a base initialization routine.
EngineManager* __fastcall EngineManager::EngineManager(EngineManager* this)
{
    // Set secondary vtable pointer (temporary, overwritten)
    this->field_0x04 = (int)&PTR_LAB_00e32038;      // +0x04: temporary pointer (overwritten)
    // Set primary vtable pointer
    this->vtable = (void**)&PTR_FUN_00e32028;        // +0x00: main vtable (class-specific functions)
    // Set final secondary vtable pointer (likely for a base class or secondary interface)
    this->field_0x04 = (int)&PTR_LAB_00e32034;      // +0x04: base/secondary vtable

    // Store singleton instance globally
    g_engineManager = this;                          // DAT_01223474 = this

    // Initialize base components (e.g., parent class constructor, subsystem setup)
    baseClassInitialize(this);                       // FUN_0043e2e0

    return this;
}