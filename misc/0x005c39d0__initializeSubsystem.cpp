// FUNC_NAME: initializeSubsystem

// Global subsystem handle (NULL when not initialized)
static void* g_subsystemHandle = NULL;

// External functions (defined elsewhere)
// Allocates memory block of given size and flags
void* allocateMemory(int size, int flags); // FUN_005c4410

// Creates subsystem instance and returns a handle
void* createSubsystem(); // FUN_005c3070

// Performs post-initialization steps
void postInitSubsystem(); // FUN_005c31d0

void initializeSubsystem(void)
{
    // Skip if already initialized
    if (g_subsystemHandle != NULL) {
        return;
    }

    // Try to allocate memory for the subsystem (size 200, no flags)
    void* memory = allocateMemory(200, 0);
    if (memory != NULL) {
        // Allocation succeeded; create the subsystem and store its handle globally
        g_subsystemHandle = createSubsystem();
        postInitSubsystem();
        return;
    }

    // Allocation failed; mark as uninitialized
    g_subsystemHandle = NULL;
    postInitSubsystem();
}