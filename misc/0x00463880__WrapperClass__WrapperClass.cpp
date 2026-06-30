// FUNC_NAME: WrapperClass::WrapperClass
WrapperClass::WrapperClass(void *innerObj, int handle) {
    // Global singleton pointer
    g_wrapperInstance = this;

    // Vtable initialization
    this->vtable = &g_WrapperVtable; // +0x00

    // Store parameters
    this->handle = handle;           // +0x04
    this->innerObject = innerObj;    // +0x08

    // Temporary buffer for function result (likely a resource ID or handle)
    uint32_t resultBuffer[3] = {0, 0, 0};

    // Get resource/instance ID from the inner object
    this->resourceId = sub_4265d0(resultBuffer, innerObj); // +0x18
    this->innerObject2 = innerObj; // +0x1C (duplicate pointer)

    // Call virtual function at offset +8 on the inner object (index 2)
    // This likely initializes or starts something
    (**(code**)(int*)innerObj + 8)();

    // Zero out some flags/counters
    this->field_C = 0;   // +0x0C
    this->field_14 = 0;  // +0x14
    this->field_10 = 0;  // +0x10

    // Call same virtual function again (double initialization?)
    (**(code**)(int*)this->innerObject + 8)();

    // Release handle if non-null (possible cleanup)
    if (this->handle != 0) {
        sub_463b90(this->handle);
    }

    return this;
}