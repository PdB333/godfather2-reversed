// FUNC_NAME: SomeClass::initializeFromData
void SomeClass::initializeFromData(const uint64_t* sourceData)
{
    // Copy 5 uint64_t values into member fields at offsets +0x30 to +0x50
    // and one uint32_t at +0x58
    this->field_0x30 = sourceData[0];
    this->field_0x38 = sourceData[1];
    this->field_0x40 = sourceData[2];
    this->field_0x48 = sourceData[3];
    this->field_0x50 = sourceData[4];
    this->field_0x58 = *(uint32_t*)(sourceData + 5);

    // Extract specific 32-bit values from the 64-bit fields for a function call
    uint32_t arg1 = *(uint32_t*)((uint8_t*)this + 0x44); // second 4 bytes of field_0x40
    uint32_t arg2 = *(uint32_t*)((uint8_t*)this + 0x34); // second 4 bytes of field_0x30
    uint32_t arg3 = *(uint32_t*)((uint8_t*)this + 0x40); // first 4 bytes of field_0x40
    uint32_t arg4 = *(uint32_t*)((uint8_t*)this + 0x3C); // second 4 bytes of field_0x38
    uint32_t arg5 = *(uint32_t*)((uint8_t*)this + 0x48); // first 4 bytes of field_0x48

    // Call engine function to create/allocate something
    uint32_t result = FUN_00b03980(arg1, arg2, arg3, arg4, arg5);

    // Call the function pointer stored at offset +0x50 (first 4 bytes of field_0x50)
    typedef void (*CallbackFunc)(uint32_t);
    CallbackFunc callback = (CallbackFunc)(*(uint32_t*)((uint8_t*)this + 0x50));
    callback(result);

    // Release/destroy the result
    FUN_00b0c100(result);

    // Allocate a sub-object and store it at +0xC
    void* subObj = FUN_00ad8d50();
    this->field_0x0C = subObj;
    if (subObj != nullptr)
    {
        // Call the first virtual function of the sub-object (likely constructor/init)
        (*(void (**)(void))subObj)();
    }
}