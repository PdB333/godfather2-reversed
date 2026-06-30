// FUNC_NAME: UnknownClass::initTwoFields
// Function at 0x00534490: initializes two DWORD fields at object offsets 0x00 and 0x04,
// then overwrites them with values returned from FUN_00534560 (which uses a 12-byte buffer).
void __thiscall UnknownClass::initTwoFields(void)
{
    // Temporary buffer (12 bytes) passed to external function
    uint8_t buffer[12];

    // Clear both fields
    this->field0 = 0;  // +0x00
    this->field4 = 0;  // +0x04

    // Call external function that returns a pointer to two DWORDs
    uint32_t* data = (uint32_t*)FUN_00534560(buffer);
    this->field0 = data[0];  // +0x00
    this->field4 = data[1];  // +0x04
}