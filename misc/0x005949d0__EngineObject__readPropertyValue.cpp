// FUNC_NAME: EngineObject::readPropertyValue
// Address: 0x005949d0
// Member function (this in EDI) consuming one integer argument, likely a property ID or packed value.
// Reads a float from the argument (via FUN_00595490), optionally transforms it if a flag is set,
// then initializes a local 28-byte buffer and passes it to a virtual function at vtable+0x14.

void __thiscall EngineObject::readPropertyValue(uint32_t param1)
{
    float value;
    // Convert param1 to float (FUN_00595490 likely returns float10 internally)
    value = this->convertToFloat(param1); // FUN_00595490

    // Check flag at this+0x4 bit 0
    if (this->flags & 0x1)                // byte at this+4, bit 0
    {
        value = this->convertToFloat(value); // Second call
        this->convertToFloat(value);          // Third call, result discarded
    }

    // Allocate temporary 28-byte buffer
    uint8_t tempBuffer[28];

    // Initialize buffer (FUN_0059bb50) – likely constructs a temporary data object
    this->initTempBuffer(tempBuffer);

    // Call virtual function at vtable offset 0x14 (index 5)
    // Typically this would be a method like processData or applyValue
    (this->vtable[0x14 / 4])(tempBuffer); // (**(code **)(*this + 0x14))(tempBuffer)
}