// FUNC_NAME: SimManager::constructor
// Address: 0x00915570
// Role: Constructor for SimManager class. Sets up vtable pointers, initializes global flag, calls base class constructor, and optionally calls destructor if heap-allocated flag is set.

// Global flag indicating whether SimManager has been initialized
static int g_simManagerInitialized = 0; // DAT_01130018

// Vtable pointers (from data section)
extern void* PTR_FUN_00d84558; // Main vtable for SimManager
extern void* PTR_LAB_00d84530; // Secondary vtable (offset +0x04)
extern void* PTR_LAB_00d8452c; // Tertiary vtable (offset +0x14)
extern void* PTR_LAB_00d84528; // Another vtable (overwrites previous at +0x14)

// Forward declarations of callees
void __thiscall SimManager::baseConstructor(); // FUN_00957d90 - base class constructor
void __thiscall SimManager::destructor(); // FUN_005c4480 - destructor (called if flag set)

// Constructor
void* __thiscall SimManager::constructor(SimManager* this, byte flag) {
    // Set up vtable pointers
    this->vtable = &PTR_FUN_00d84558; // +0x00: main vtable
    this->field_0x04 = &PTR_LAB_00d84530; // +0x04: secondary vtable
    this->field_0x14 = &PTR_LAB_00d8452c; // +0x14: tertiary vtable (first assignment)
    this->field_0x14 = &PTR_LAB_00d84528; // +0x14: overwritten with another vtable

    // Reset global initialization flag
    g_simManagerInitialized = 0;

    // Call base class constructor
    SimManager::baseConstructor();

    // If the object was heap-allocated (flag & 1), call destructor
    // This is a common pattern for placement new or cleanup on exception
    if ((flag & 1) != 0) {
        SimManager::destructor(this);
    }

    return this;
}