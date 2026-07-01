// FUNC_NAME: GlobalObjectInitializer
// Function at 0x008b26e0: Initializes a global singleton object (likely an EARS manager) at address 0x01218040.
void GlobalObjectInitializer(void) {
    // Call the initialization routine for the global data block
    InitGlobalObject(&DAT_01218040);
}