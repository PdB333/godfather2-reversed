// FUNC_NAME: SomeManager::constructor

// Constructor for a manager class. Initializes members, releases any existing sub-object,
// sets a global flag to 0, and optionally deletes itself if the flag parameter has bit 0 set.
// Address: 0x008f1b60

class SomeManager {
public:
    // Vtable pointers (from data refs)
    // +0x00: vtable pointer (initially set to PTR_FUN_00d80f30, then changed to PTR_LAB_00d80f2c)
    // +0x04: pointer to a sub-object (released and set to 0)
    // +0x08: some integer field (set to 0)
    // +0x0C: another integer field (set to 0)

    // Global flag indicating whether the manager is initialized
    static int g_initializedFlag; // DAT_011299b8

    // Constructor
    // param_2: if bit 0 is set, calls a deallocation function (likely operator delete) on this
    void* constructor(byte deleteOnFailure) {
        // Set initial vtable (base class or initial interface)
        this->vtable = &PTR_FUN_00d80f30;

        // Initialize field at +0x08 to 0
        this->field_0x08 = 0;

        // Release any existing sub-object pointed to by field at +0x04
        if (this->subObject) {
            releaseSubObject(this->subObject); // FUN_009c8f10
        }
        this->subObject = nullptr;

        // Initialize field at +0x0C to 0
        this->field_0x0C = 0;

        // Set final vtable (derived class or final interface)
        this->vtable = &PTR_LAB_00d80f2c;

        // Reset global initialization flag
        g_initializedFlag = 0;

        // If the deleteOnFailure flag is set, deallocate this object
        if (deleteOnFailure & 1) {
            deallocateObject(this); // FUN_009c8eb0
        }

        return this;
    }

private:
    // Placeholder for vtable pointer
    void* vtable;
    // Placeholder for sub-object pointer (offset +0x04)
    void* subObject;
    // Placeholder for integer field at +0x08
    int field_0x08;
    // Placeholder for integer field at +0x0C
    int field_0x0C;

    // Helper functions (callees)
    void releaseSubObject(void* obj); // FUN_009c8f10
    void deallocateObject(void* obj); // FUN_009c8eb0
};

// Global definition
int SomeManager::g_initializedFlag = 0; // DAT_011299b8