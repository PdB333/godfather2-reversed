// FUNC_NAME: SomeManager::initializeInterfaces
void __fastcall SomeManager::initializeInterfaces(void* thisPtr)
// Address: 0x005d8930
// Called to initialize manager's singleton interfaces and perform setup.
// Offsets: +0x10, +0x14 seem to be interface pointers.
{
    // Retrieve and store first interface pointer (e.g., from a singleton getter).
    undefined4 firstInterface = getFirstInterface(); // FUN_0060a380
    *(undefined4*)((int)thisPtr + 0x10) = firstInterface;

    // Retrieve and store second interface pointer from a global data pointer.
    undefined4 secondInterface = getSecondInterface(&gGlobalPointer); // FUN_0060a2e0, PTR_DAT_00f1747c
    *(undefined4*)((int)thisPtr + 0x14) = secondInterface;

    // Perform additional initialization (e.g., logging, registration).
    performInitialization(); // FUN_006127d0
}