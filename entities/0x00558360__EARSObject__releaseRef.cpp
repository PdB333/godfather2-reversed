// FUNC_NAME: EARSObject::releaseRef
// Function address: 0x00558360
// Role: Release/reference count decrement and cleanup for an EARS object with child and callback data

void EARSObject::releaseRef()
{
    // +0x00: vtable pointer (implied)
    // +0x04: childObject (pointer to another object)
    // +0x1C: some flag indicating global resource ownership
    // +0x20: refData (pointer to a reference counting block)

    // Call base class release (likely decrements base ref count)
    baseRelease(); // FUN_00558770(this)

    // If the global cleanup flag is set, perform a global resource release
    if (this->globalCleanupFlag != 0) { // +0x1C
        globalCleanupFunction(); // FUN_009f01a0() - no arguments, static/global
    }

    // Handle reference counting / callback data block
    RefCountData* refData = this->refData; // +0x20
    if (refData != nullptr && refData->someShort != 0) { // short at offset 0x04 of refData
        // Decrement the second short (offset 0x06) – likely a usage/strong count
        refData->usageCount--; // short at offset 0x06
        if (refData->usageCount == 0) {
            // When usage reaches zero, invoke the callback with argument 1 (delete self?)
            // First dword of refData is a function pointer (e.g., custom deleter)
            refData->deleter(1); // (**(code**)*refData)(1)
        }
    }

    // Release and free the child object if present
    if (this->childObject != nullptr) { // +0x04
        childObject->release();  // FUN_00559ca0  (child's own release)
        childObject->free();     // FUN_009c8eb0  (likely operator delete or Free)
    }
}