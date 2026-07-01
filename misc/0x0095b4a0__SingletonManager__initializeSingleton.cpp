// FUNC_NAME: SingletonManager::initializeSingleton
// Address: 0x0095b4a0
// Role: Initializes a global singleton object, stores a parameter, and triggers a virtual method.

// Assumed structure: SingletonManager is a class with a vtable and a field at offset 0x1b.
// The global pointer gSingleton points to an instance of this class.

extern SingletonManager* gSingleton; // DAT_011305b4 - global pointer to singleton instance

void __thiscall SingletonManager::initializeSingleton(int param_1)
{
    // Call base class constructor or some other initialization routine
    FUN_005c1ad0();

    // Call another initialization function with zero
    FUN_0095b320(0);

    // Store the parameter at offset 0x1b within the singleton object
    // (likely an integer field, though offset 0x1b is byte-aligned; possibly a mis-decompiled offset)
    *(int*)((char*)gSingleton + 0x1b) = param_1;

    // Invoke a virtual function at vtable offset 0x28 (i.e., vtable index 10)
    // This is likely a post-initialization callback
    void (**vtable)(void) = (void (**)(void))(*gSingleton);
    vtable[0x28 / 4]();
}