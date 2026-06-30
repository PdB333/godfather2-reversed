// FUN_00485600: initializeCurrentThread
// This function initializes thread-local storage for the current thread.
// It accesses the TLS array via FS:[0x2C] (Windows x86) and checks if the
// per-thread context at slot[0] is already initialized (field at +0x34).
// If not, logs an error and returns. Otherwise, it stores a global counter
// sum into field +0x08 and proceeds with thread-specific initialization.

void initializeCurrentThread()
{
    // Global thread tracking variables (addresses approximated)
    extern int g_threadCounter;        // DAT_01205418 - current thread count or base ID
    extern int g_threadCounterOffset;  // DAT_01205410 - additional offset for sum

    // Fetch TLS array pointer from FS segment (offset 0x2C)
    // This is the per-thread TLS slot array (array of void*)
    void** tlsArray = (void**)__readfsdword(0x2C);

    // The first TLS slot (index 0) points to a per-thread context structure
    struct ThreadContext
    {
        int field_0x08;   // +0x08 - stores computed value
        int field_0x34;   // +0x34 - initialization flag
    }* threadContext = (ThreadContext*)tlsArray[0];

    // Check if the context is already initialized
    if (threadContext->field_0x34 == 0)
    {
        // Log initialization failure (error handler)
        extern int g_errorToken;       // DAT_00e2e298
        FUN_00ab5130(&g_errorToken);
        return;
    }

    // Store the sum of two global counters into the thread context
    threadContext->field_0x08 = g_threadCounter + g_threadCounterOffset;

    // Initialize thread-specific resources using the current counter
    FUN_004de510(g_threadCounter);

    // Signal that initialization is complete
    FUN_00ab51e0(1);
}