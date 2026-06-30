// FUNC_NAME: BitField::testAndReturnMask
uint BitField::testAndReturnMask(uint mask) {
    int dummy = 0;
    // Call virtual function at vtable offset 0x10 (index 4 on 32-bit)
    // This function checks if 'mask' is active and returns true/false.
    // The 'dummy' output parameter is not used.
    char result = (this->vtable[4])(mask, &dummy);
    // Return the mask if the condition was true, otherwise 0.
    return (result != 0) ? mask : 0;
}