// FUNC_NAME: SomeManager::initializeOnce
// Address: 0x005e8670
// Role: One-time initialization check and call. If the flag at +0x490 is not set, calls an initialization function (FUN_005e8300) and sets the flag.

void __thiscall SomeManager::initializeOnce(void) {
    // +0x490: byte flag indicating whether initialization has been performed
    if (*(char *)(this + 0x490) == '\0') {
        // Call the actual initialization routine (assumed to be a member function or global)
        FUN_005e8300(this);
        // Set the flag to indicate initialization completed
        *(char *)(this + 0x490) = 1;
    }
}