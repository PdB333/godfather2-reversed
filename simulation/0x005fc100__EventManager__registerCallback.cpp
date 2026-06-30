// FUNC_NAME: EventManager::registerCallback
void __thiscall EventManager::registerCallback(void* object, int callbackId) {
    void* container = ???; // in_EAX: likely a static instance of EventManager or a member of this
    // Note: in_EAX is used as a base pointer; assume it's a member variable of the class, e.g., this->container
    // Actually, the decompiler shows in_EAX as uninitialized, but it's likely the this pointer for EventManager.
    // We'll cast to EventManager* and access fields.

    EventManager* manager = (EventManager*)in_EAX; // or reinterpret from this if this is a static method?
    // Based on the code, in_EAX seems to be a separate object, not the same as param_1.

    // Call virtual function at vtable+8 on the object (presumably a callback initializer)
    (*(void (**)(void*))(*((int*)object) + 8))(object);

    int handle;
    if (callbackId == 0) {
        handle = 0;
    } else {
        handle = FUN_004265d0(callbackId, object); // Generate handle from callbackId and object pointer
    }

    FUN_005fc4a0(object, handle); // Attach or register the object with the given handle

    // Store object and handle into the manager's fields (offsets +0x08 and +0x0C)
    manager->field_0x08 = object;   // offset +0x08: pointer to callback object
    manager->field_0x0C = handle;   // offset +0x0C: handle value

    // Call virtual function at vtable+8 again (no arguments in decompiled, but likely same as before)
    (*(void (**)(void))(*((int*)object) + 8))();   // Note: no argument here, possibly an overload

    if (callbackId != 0) {
        // Recompute handle using stored object pointer
        handle = FUN_004265d0(callbackId, manager->field_0x08);
        manager->field_0x0C = handle;

        // Call virtual function at vtable+4 with callbackId and 0
        (*(void (**)(int, int))(*((int*)object) + 4))(callbackId, 0);
        // Call virtual function at vtable+0xC (cleanup or finalize)
        (*(void (**)(void))(*((int*)object) + 12))();
    } else {
        manager->field_0x0C = 0;
        // Call virtual function at vtable+0xC
        (*(void (**)(void))(*((int*)object) + 12))();
    }
}