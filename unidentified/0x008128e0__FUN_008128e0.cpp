// FUNC_NAME: SomeManager::SomeManager

class SomeManager {
public:
    void *vtable;          // +0x00
    // Padding or additional base vtable? offset +0x04, +0x08
    void *secondaryVtable; // +0x0C (param_1[3])
    void *somePointer;     // +0x10 (param_1[4])
    // Other members...

    SomeManager(byte flags);
};

// Global state
int g_managerInitialized = 0;  // DAT_0112dae4

SomeManager::SomeManager(byte flags) {
    // Set primary vtable (most derived class)
    this->vtable = (void*)&PTR_FUN_00d73018;

    // Set secondary vtable to base class version initially
    this->secondaryVtable = (void*)&PTR_LAB_00d73014;

    // Call base class constructor with flag = 1 (size hint? ) 
    FUN_00403720(1, this);

    // If there is a pointer at offset 0x10, release it (e.g., old data)
    if (this->somePointer != 0) {
        FUN_009c8f10(this->somePointer); // release function
    }

    // Update secondary vtable to derived class version
    this->secondaryVtable = (void*)&PTR_LAB_00d73010;

    // Reset global initialization flag
    g_managerInitialized = 0;

    // Perform initialisation of subsystem
    FUN_004083d0();

    // If the object was heap-allocated (flags & 1), possibly delete it?
    // (This pattern is unusual but seen in some constructors for placement delete)
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this); // operator delete or cleanup
    }
}