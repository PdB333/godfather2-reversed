// FUNC_NAME: SimManager::constructor
// Address: 0x00898780
// This function is the constructor for the SimManager class (EARS engine singleton manager).
// It sets up the vtable pointer, initializes internal sub-objects (likely a list/array and a string container),
// and registers the instance via a global function (possibly to enable singleton access).

void __thiscall SimManager::constructor(SimManager* this)
{
    // Set vtable for this instance (base class virtual function table)
    *(void**)this = (void*)0x00d77ca0; // PTR_FUN_00d77ca0 - SimManager vtable

    // Set additional function pointers at offsets +0x3C and +0x48
    // These appear to be pointers to static functions or thunks for sub-objects
    *(void**)((char*)this + 0x3C) = 0x00d77c90; // PTR_LAB_00d77c90
    *(void**)((char*)this + 0x48) = 0x00d77c8c; // PTR_LAB_00d77c8c

    // Initialize a sub-object at offset +0x50 (size unknown, likely a string or container)
    // FUN_004086d0 is likely a constructor or initializer for this sub-object
    SimManager::initializeSubObject((char*)this + 0x50); // FUN_004086d0

    // Initialize two more sub-objects at offsets +0x50 and +0x58
    // These share the same initialization function (FUN_00408310), which may be a reset/clear operation
    SimManager::resetSubObject((char*)this + 0x50); // FUN_00408310
    SimManager::resetSubObject((char*)this + 0x58); // FUN_00408310

    // Register this instance globally (likely adds to a singleton list or sets a global pointer)
    SimManager::registerInstance(); // FUN_0046c640
}