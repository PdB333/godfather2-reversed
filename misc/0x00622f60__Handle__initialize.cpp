// FUNC_NAME: Handle::initialize

// Function at 0x00622f60: Constructor/initializer for a Handle object that wraps a shared object.
// param_1: pointer to a pre-allocated Handle object (this)
// param_2: pointer to a SharedObject with vtable
// param_3: optional pointer to a manager/context for registration (may be null)
// Returns: this pointer

int Handle::initialize(int *thisPtr, SharedObject *sharedObj, void *manager) {
    SharedObject *obj = sharedObj;  // piVar2
    int handle;                     // uVar1

    // First retain call on shared object
    obj->retain();

    if (manager != nullptr) {
        // Register the shared object with the manager
        handle = registerWithManager(manager, obj);
        
        // Link the handle reference to the manager's record
        linkToManager(obj, handle);
    }

    // Store the shared object pointer into the Handle
    thisPtr[0x14 / 4] = (int)obj;  // +0x14

    // Redundant retain call (possibly a no-op or debug assert)
    obj->retain();

    if (manager != nullptr) {
        // Register again with the stored pointer (same object)
        handle = registerWithManager(manager, (SharedObject *)thisPtr[0x14 / 4]);
        thisPtr[0x18 / 4] = handle;  // +0x18

        // Release call on shared object (with manager context)
        obj->release(manager, 0);

        // Finalize/unlock
        obj->unlock();
    } else {
        thisPtr[0x18 / 4] = 0;       // +0x18
        obj->unlock();
    }

    return (int)thisPtr;
}