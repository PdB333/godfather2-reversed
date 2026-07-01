// FUNC_NAME: GlobalsManager::reinitialize
void __thiscall GlobalsManager::reinitialize(void)
{
    // Reset global singleton objects (likely queue or pool)
    resetObject(&g_globalA);  // FUN_004086d0
    resetObject(&g_globalB);  // FUN_004086d0
    // Initialize them again
    initObject(&g_globalA);   // FUN_00408310
    initObject(&g_globalB);   // FUN_00408310
    // Reset another global
    resetObject(&g_globalC);  // FUN_004086d0
    // Initialize member objects at offsets +0xe8 and +0xe0
    initObject(reinterpret_cast<void*>(reinterpret_cast<uint32_t>(this) + 0xe8)); // FUN_00408310
    initObject(reinterpret_cast<void*>(reinterpret_cast<uint32_t>(this) + 0xe0)); // FUN_00408310
    // Finalize/complete the reinitialization
    finalizeSubsystem();      // FUN_005c1820
}