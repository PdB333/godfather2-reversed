// FUNC_NAME: SomeManager::SomeManager
// Address: 0x00690070
// Role: Constructor for a manager class (likely singleton). Initializes vtable, allocates sub-object, and logs a debug value.

class SomeManager {
public:
    // Vtable pointer at offset 0x00
    void* vtable;

    // Constructor
    SomeManager() {
        // Store global pointer to this instance
        g_pSomeManager = this;

        // Set vtable pointer
        this->vtable = (void*)&PTR_FUN_00d5c8d4;

        // Allocate a sub-object of size 0x1c (28 bytes)
        void* subObj = operator new(0x1c);
        if (subObj != nullptr) {
            // Initialize sub-object (likely another constructor)
            FUN_0068ff10(subObj); // Assumed to be a constructor taking subObj as this
        }

        // Debug/logging: send a magic value (0xff00c3c3) with message ID 0x13
        uint32_t debugValue = 0xff00c3c3;
        FUN_0049af40(0x13, &debugValue);
    }
};

// Global pointer to the singleton instance
SomeManager* g_pSomeManager = nullptr; // DAT_011299d0