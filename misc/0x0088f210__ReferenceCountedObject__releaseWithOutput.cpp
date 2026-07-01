// FUNC_NAME: ReferenceCountedObject::releaseWithOutput
void __thiscall ReferenceCountedObject::releaseWithOutput(int* outResult, int someHandle)
{
    // Decrement reference count at +0x14
    this->refCount--;

    // Get some value from the handle (e.g., previous reference count or status)
    *outResult = getSomeValue(someHandle);

    // Release resource associated with this object (e.g., free memory at +0x04)
    releaseResource(someHandle, &this->resourceData);

    // Finalize release of the handle
    finalizeRelease(someHandle);
}