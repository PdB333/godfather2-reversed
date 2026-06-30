// FUNC_NAME: releaseGlobalSingletonOrDestructor
void __thiscall releaseGlobalSingletonOrDestructor(int *thisPtr)
{
    // Check if this object's vtable/magic matches the global singleton identifier
    // DAT_0120e93c is likely a static address (e.g., vtable of global singleton)
    if (*thisPtr == (int)&DAT_0120e93c) {
        // Nullify or clean up the global singleton reference
        FUN_004086d0(&DAT_0120e93c);  // Probably sets global pointer to null or resets
    }
    // Call base class destructor / release chain
    FUN_0046efc0(thisPtr);  // Likely frees memory or calls ~Base()
}