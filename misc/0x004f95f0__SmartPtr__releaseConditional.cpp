// FUNC_NAME: SmartPtr::releaseConditional
// This function implements a conditional release with ref counting.
// The counter structure contains a vtable pointer at +0 and a reference count at +4.
// param_managedObj: pointer to the managed object (passed as this to the virtual checks)
// param_counter: pointer to the reference counter structure
bool SmartPtr::releaseConditional(void* managedObj, int* counter) {
    if (counter == nullptr) {
        return false;
    }

    // Virtual function at vtable+8: query if the object can be released now
    bool canRelease = (*(code**)(*counter + 8))(managedObj) != 0;

    // Decrement the reference count (offset +4)
    int* refCount = counter + 1;
    (*refCount)--;

    if (*refCount == 0) {
        // Call destructor via vtable+4
        (*(code**)(*counter + 4))();
    }

    return canRelease;
}