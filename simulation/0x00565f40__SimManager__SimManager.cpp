// FUNC_NAME: SimManager::SimManager
// Function address: 0x00565f40
// Constructor for SimManager (conjecture based on pattern). 
// Sets initial vtable, calls base initialization, then final vtable.
// param_2 bit 0 indicates if object was heap-allocated (for exception handling).

class SimManager {
public:
    void* vtable; // +0x00
    // Other members...
};

// Global variable used in constructor (likely a singleton flag)
uint32_t g_someGlobal = 0; // 0x012234dc

SimManager* __thiscall SimManager::SimManager(SimManager* this, byte flags) {
    // Set base class vtable
    this->vtable = (void*)&PTR_FUN_00e3a5d0; // Base vtable (likely EARSObject)
    // Call base class constructor/initialization
    FUN_00ae97f0(); // Base constructor call (e.g., EARSObject::EARSObject)
    // Set derived class vtable
    this->vtable = (void*)&PTR_LAB_00e3a5d4; // SimManager vtable
    // Initialize global status
    g_someGlobal = 0;
    // If heap-allocated, call operator delete on exception (compiler-generated cleanup)
    if (flags & 1) {
        FUN_009c8eb0(this); // operator delete or destructor call
    }
    return this;
}