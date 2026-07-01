// FUNC_NAME: ManagerBase::constructor
// Function address: 0x00963050
// Purpose: Constructor for a manager/watcher object, allocating a 0xF0-byte instance and initializing type/callback.

void __thiscall ManagerBase::constructor(ManagerBase* this, code* callback)
{
    // Allocate 0xF0 bytes for the manager object (likely internal data + vtable)
    ManagerBase* instance = (ManagerBase*)allocateMemory(0xf0); // FUN_009c8e50
    if (instance == nullptr) {
        instance = nullptr;
    } else {
        // Initialize instance with parameter 0 (e.g., parent or owner index)
        instance = (ManagerBase*)ManagerBase::Construct(instance, 0); // FUN_00982280
    }

    // Link this manager instance to the parent object (this)
    ManagerBase::setParent(this); // FUN_00981eb0

    // Set base type to 3 (e.g., kManagerType_Standard or similar)
    instance->m_type = 3; // +0x0C

    // Set callback function (defaults to defaultCallback if null)
    if (callback == nullptr) {
        callback = defaultCallback; // FUN_00982b30
    }
    instance->m_callback = callback; // +0x14

    // Finalize registration (e.g., add to global list)
    ManagerBase::registerManager(); // FUN_00982e10
}