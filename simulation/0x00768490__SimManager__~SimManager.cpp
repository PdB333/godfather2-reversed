// FUNC_NAME: SimManager::~SimManager
// Address: 0x00768490
// Role: Destructor for SimManager class, cleans up base class, a pointer member, and performs final cleanup.

void __fastcall SimManager::~SimManager(SimManager* this) {
    // Set vtable to base class vtable to ensure proper virtual dispatch during base destructor
    this->vtable = (void**)&PTR_LAB_00d65aa8; // +0x00: vtable pointer set to base vtable

    // Call base class destructor (likely EARS::Framework::BaseManager::~BaseManager)
    baseClassDestructor(this); // FUN_00716310

    // Restore vtable to this class's vtable (maybe for subsequent cleanup calls)
    this->vtable = (void**)&PTR_LAB_00d63090; // +0x00: vtable pointer set back to derived vtable

    // If the member pointer at offset 0x68 (index 0x1a) is non-null, delete it
    if (this->somePointer != 0) { // +0x68: pointer to a subobject (e.g., a resource container)
        deleteOrReleasePointer(&(this->somePointer)); // FUN_004daf90: takes address of pointer, frees and nulls
    }

    // Perform any final engine-wide cleanup
    finalCleanup(); // FUN_0080ea60: possibly shutting down subsystem

    return;
}