// FUNC_NAME: SomeManager::constructor
// Function address: 0x004c9210
// Role: Constructor for a manager class (likely singleton). Sets vtable pointers, calls base constructor, initializes global flag.
// Note: The second vtable pointer (offset +4) is set to a label, possibly for a secondary interface or RTTI.
// Global DAT_01223404 is set to 0 (maybe indicating not yet fully initialized or a flag).

class SomeManager {
public:
    // Vtable pointer at offset 0
    // Secondary pointer at offset 4 (possibly RTTI or secondary vtable)
    // Base class constructor called at FUN_004083d0
    // If param_2 & 1, calls FUN_009c8eb0 (likely a cleanup or deallocation function)

    // Constructor
    // param_2: bit 0 indicates whether to call cleanup function (e.g., for heap-allocated objects)
    void* constructor(byte allocFlag) {
        // Set initial vtable to base class
        *(void**)this = (void*)&PTR_FUN_00e36614;
        // Set secondary pointer
        *(void**)((char*)this + 4) = (void*)&PTR_LAB_00e36618;

        // Call base class constructor
        FUN_004083d0();

        // Update vtable to derived class
        *(void**)this = (void*)&PTR_LAB_00e36628;

        // Initialize global flag to 0
        DAT_01223404 = 0;

        // If allocFlag bit 0 is set, call cleanup function (e.g., operator delete on failure)
        if ((allocFlag & 1) != 0) {
            FUN_009c8eb0(this);
        }

        return this;
    }
};

// Global variable (likely a singleton flag or state)
int DAT_01223404; // +0x0