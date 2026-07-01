// FUNC_NAME: SwitchProfileManager::SwitchProfileManager

// Constructor for SwitchProfileManager class.
// Sets up vtable, initializes base, creates a thread named "SwitchProfileManagerThread".
// Stores the instance pointer in global gSwitchProfileManagerInstance.

class SwitchProfileManager {
public:
    // Virtual table pointer (first member)
    void* vtable;

    // Constructor
    SwitchProfileManager() {
        // Store this instance globally
        gSwitchProfileManagerInstance = this;

        // Set vtable pointer
        this->vtable = &SwitchProfileManager_vtable;

        // Call base class constructor (likely EARS::Framework::Object or similar)
        FUN_00ab54d0();

        // Get some value (maybe thread priority or stack size)
        uint32_t threadParam = FUN_00ab5470();

        // Create the thread with a callback at LAB_00907dc0, parameters 0,0, and threadParam
        FUN_00ab7410(&LAB_00907dc0, 0, 0, threadParam);

        // Set the thread name for debugging
        FUN_00ab56e0("SwitchProfileManagerThread");
    }
};

// Global instance pointer
SwitchProfileManager* gSwitchProfileManagerInstance = nullptr; // +0x112ff68

// External functions (likely from EARS framework)
extern void FUN_00ab54d0(); // Base class constructor
extern uint32_t FUN_00ab5470(); // Get thread creation parameter
extern void FUN_00ab7410(void* callback, int param1, int param2, uint32_t param3); // Create thread
extern void FUN_00ab56e0(const char* threadName); // Set thread name

// Vtable for SwitchProfileManager (defined elsewhere)
extern void* SwitchProfileManager_vtable; // +0x00d82fdc

// Thread entry point (likely a static member function or free function)
extern void LAB_00907dc0(); // Thread callback