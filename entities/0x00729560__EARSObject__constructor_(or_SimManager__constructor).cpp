// FUNC_NAME: EARSObject::constructor (or SimManager::constructor)
// Address: 0x00729560
// Role: Base class constructor for an EARS engine object, initializes vtable pointers, synchronization objects, and derived state.

void __thiscall EARSObject::constructor(EARSObject* this) {
    // Set vtable to base class vtable (first vtable slot)
    this->vtable = &BASE_VTABLE; // PTR_FUN_00d624f8
    // Set second vtable slot (for multiple inheritance or interface)
    this->vtable2 = &BASE_VTABLE2; // PTR_LAB_00d624e8

    // Initialize first critical section or mutex (global data)
    CriticalSection::initialize(&g_CriticalSection1); // DAT_0112ad8c -> FUN_004086d0
    // Initialize second and third critical sections (global data)
    Mutex::initialize(&g_Mutex1); // DAT_0112ad7c -> FUN_00408310
    Mutex::initialize(&g_CriticalSection1); // DAT_0112ad8c -> FUN_00408310 (duplicate? Likely different mutex)

    // Call base class constructor (possibly for ObjectBase or Entity)
    BaseClass::constructor(); // FUN_00729460

    // Free a dynamically allocated sub-object if exists (offset 0x1C = this[7])
    if (this->subObject != nullptr) { // param_1[7] is at offset 0x1C
        subObject->release(); // FUN_009c8f10 - release/destroy
    }

    // Additional initialization
    initializeInternal(); // FUN_00729130
    finalizeInitialization(); // FUN_004083d0

    // Switch vtable to derived class vtable (after construction)
    this->vtable = &DERIVED_VTABLE; // PTR_LAB_00d624e4

    // Clear a global initialization flag
    g_InitializationComplete = 0; // DAT_0112ad18 = 0

    return;
}