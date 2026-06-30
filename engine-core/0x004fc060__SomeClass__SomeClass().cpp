// FUNC_NAME: SomeClass::SomeClass()
void SomeClass::SomeClass()
{
    // Zero out the 8-byte data member (offsets +0x00 and +0x04)
    this->field_0 = 0;
    this->field_4 = 0;

    // Temporary buffer to receive default value from helper function
    // The function at 0x004fc430 fills this buffer and returns a pointer to it.
    // Only the first 8 bytes are used; buffer is 12 bytes possibly for alignment.
    uint8_t defaultBuffer[12];
    uint32_t* pDefault = (uint32_t*)FUN_004fc430(defaultBuffer);

    // Copy the default value into the object
    this->field_0 = pDefault[0];
    this->field_4 = pDefault[1];
}