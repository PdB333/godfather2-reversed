// FUNC_NAME: SingletonManager::setInstance (static method, replaces global singleton with cleanup/init calls)
// Function address: 0x0056ffa0
// Likely part of a manager class that uses a singleton pattern.
// Calls virtual functions at vtable offsets 0xC (on old instance) and 0x8 (on new instance).
// The global pointer DAT_0120556c stores the current instance.

// Global singleton pointer (at 0x0120556c)
static SomeObject* s_globalSingleton = nullptr;

void SingletonManager::setInstance(SomeObject* newInstance)
{
    // If there is an existing singleton, call its cleanup/shutdown function (vtable+0xC)
    if (s_globalSingleton != nullptr) {
        (*(void (**)())(*(int*)s_globalSingleton + 0xC))();
    }

    // Store the new instance
    s_globalSingleton = newInstance;

    // If new instance is valid, call its initialization function (vtable+0x8)
    if (newInstance != nullptr) {
        (*(void (**)())(*(int*)newInstance + 0x8))();
    }
}