// FUNC_NAME: SomeClass::releaseSubComponents
void SomeClass::releaseSubComponents()
{
    // Release sub-object at offset 0xB0 (index 0x2c)
    UnknownObject* subObj2 = *(UnknownObject**)((uint8_t*)this + 0xB0);
    if (subObj2 != nullptr) {
        // Call virtual function at vtable+4 (ReleaseSub with flag 0)
        subObj2->Release(0);
        // vtable+4 is typically the second virtual function
    }

    // Release sub-object at offset 0xAC (index 0x2b)
    UnknownObject* subObj1 = *(UnknownObject**)((uint8_t*)this + 0xAC);
    if (subObj1 != nullptr) {
        subObj1->Release(0);
    }

    // Call virtual function at vtable+0xC on this object
    // Likely a finalizer / self-destruct step (e.g., ReleaseSelf, Destroy)
    this->FinalRelease();

    // Global cleanup hook (e.g., debug tracking, memory stats)
    GlobalCleanupHook();
}