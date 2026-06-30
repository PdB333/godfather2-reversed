// FUNC_NAME: SystemSingleton::getSingletonPtr
// Address: 0x00491f40
// Role: Returns the address of the global singleton pointer after initializing the subsystem.
// The global DAT_01216520 is a pointer to the singleton's vtable/interface table.
// FUN_00491c40 performs the actual construction/initialization of the singleton object.

static void** g_pSingletonVTable = nullptr; // +0x0: Global vtable pointer for the singleton

void** __cdecl SystemSingleton::getSingletonPtr()
{
    // Call the initialization function (likely allocates and constructs the singleton)
    SystemSingleton::initialize();

    // Set the global vtable pointer to the static table
    g_pSingletonVTable = &PTR_LAB_00e34750;

    // Return the address of the global pointer (so callers can access the singleton indirectly)
    return &g_pSingletonVTable;
}