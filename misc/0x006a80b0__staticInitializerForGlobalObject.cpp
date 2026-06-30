// FUNC_NAME: staticInitializerForGlobalObject
// This is a static initializer that calls the constructor for a global object (at 0x012069c4).
// The callee (0x004086d0) is likely a constructor method for a singleton or global instance.
void staticInitializerForGlobalObject(void) {
    // Call the constructor for the global object referenced by the data pointer.
    constructGlobalObject(&gGlobalObject);
}