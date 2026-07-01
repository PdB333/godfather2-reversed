// FUNC_NAME: Singleton::getInstance

// Global state for lazy singleton initialization
static bool s_singletonInitialized = false; // _DAT_0112ddb4
static char s_singletonObject[0x14];         // DAT_0112dda0 (size unknown, at least 0x14 from offset difference)

// Forward declaration of singleton constructor (placement new or init function)
void __cdecl initializeSingleton(void* memory, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);

// Returns pointer to the singleton instance; initializes on first call
void* __cdecl Singleton::getInstance()
{
    if (!s_singletonInitialized)
    {
        s_singletonInitialized = true;
        // Arguments: memory location (implied by first zero), possibly flags/size
        // 0x60334 and 0x30000 might be resource ID or allocation parameters
        initializeSingleton(nullptr, 0, 0, 0x60334, 0x30000, 0, 0);
    }
    return (void*)s_singletonObject;
}