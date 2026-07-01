// FUNC_NAME: RefCountedObject::~RefCountedObject
void __fastcall RefCountedObject::~RefCountedObject(RefCountedObject* this)
{
    short asyncOpCount;

    // Replace vtable with a special "destructing" vtable to prevent further virtual calls
    // +0x08: vtable pointer
    this->vtable = &PTR_DESTRUCTION_VTABLE;  // PTR_FUN_00d6ffac

    // Wait for all pending asynchronous operations to complete
    // +0x1A: short count of pending async operations
    while (this->asyncOpCount != 0) {
        // Yield to scheduler or process pending tasks
        yieldToScheduler();  // FUN_00408090
    }

    // If a deallocation function table exists and the object hasn't been flagged as already released
    // +0x10: pointer to a struct containing a release function at offset 0
    // +0x20: byte flags, bit 0 set indicates already released
    if (this->deallocFuncTable != nullptr && !(this->flags & 0x01)) {
        // Call the release function (typically the first entry in the table) with parameter 1
        // Parameter 1 might indicate immediate deallocation or final release
        this->deallocFuncTable->release(1);  // (**(code**)*this->deallocFuncTable)(1)
    }
}