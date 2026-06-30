// FUNC_NAME: AptSystem::update (0x0059e850)
// Role: Main update loop for the APT (Adobe ActionScript UI) system. Processes pending events, handles input, and releases reference-counted objects.

class AptSystem {
public:
    void update(); // __thiscall
};

// Global flags and managers (from data references)
static bool g_bAptIsInitialized; // DAT_012055b0
static bool g_bShuttingDown; // DAT_0119cad0
static void* g_pAptGlobal; // DAT_0119a9cc (pointer to some global manager)
// ... other globals and function pointers omitted for brevity

// External function declarations (these would map to the called subroutines)
static void fetchEvents(AptEvent* events); // FUN_0059cde0
static bool hasInput(); // FUN_0059ca10
static void processInput(AptSystem* thisPtr); // FUN_0059e710
static void processDefaultEvents(); // FUN_005a2500
static void flushOutput(); // FUN_005af060
static void releaseEventObject(void* obj); // FUN_005a1b40 (decrements ref, maybe frees)

// Event descriptor (size 4 bytes)
struct AptEvent {
    void* object; // pointer to a reference-counted object
    // Possibly other fields, but we only see the pointer
};

// Actual function body
void AptSystem::update() {
    // --- Assert: Apt system must be initialized ---
    if (!g_bAptIsInitialized) {
        // Debug assert: "bAptIsInitialized" at ..\source\Apt\Apt.cpp line 0x198
        // In release builds this might be a no-op or crash
        // Verbose debug output omitted (swi breakpoint)
        // For reconstruction we simply do nothing or log error
    }

    // --- Local event array (63 events) ---
    AptEvent events[63]; // sizeof undefined4 * 63
    memset(events, 0, sizeof(events));

    // Fetch pending events from the system
    fetchEvents(events);

    if (!g_bShuttingDown) {
        // Check if input system is ready
        int* inputManager = *(int**)(*(int**)g_pAptGlobal + 0x2514);
        if (*(int*)(inputManager + 0x60 / 4) != 0) {
            if (hasInput()) {
                processInput(this); // handle input
                goto cleanup;
            }
        }
        // Default processing
        processDefaultEvents();
        *(int*)((char*)g_pAptGlobal + 0x301c) = 0; // clear some flag
    }

cleanup:
    flushOutput();

    // --- Decrement reference counts on event objects and free if zero ---
    for (int i = 62; i >= 0; i--) { // 63 elements, from last to first
        void* obj = events[i].object;
        if (obj != nullptr) {
            // The object's reference count is stored at offset 0 (first int)
            int* refCount = (int*)obj;
            (*refCount)--;
            if (*refCount == 0) {
                releaseEventObject(obj);
                // Free the memory using the global allocator (type 0x30)
                void* allocatorFunc = *(void**)(someGlobal + 0x??); // DAT_0119caf8
                // In original: (*DAT_0119caf8)(obj, 0x30);
                // Here we assume a global function pointer g_freeObject
                g_freeObject(obj, 0x30);
            }
        }
    }
}