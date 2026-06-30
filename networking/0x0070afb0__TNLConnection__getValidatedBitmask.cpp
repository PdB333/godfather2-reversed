// FUNC_NAME: TNLConnection::getValidatedBitmask
uint TNLConnection::getValidatedBitmask(uint bitmask) {
    // local variable used for potential output from virtual call, but unused in this function
    uint dummy = 0;

    // Call virtual function at vtable+0x10 (likely isConditionValid or testMask)
    // It takes (bitmask, &dummy) and returns a char (bool)
    char result = (this->vtable[4])(bitmask, &dummy);

    // If result is non-zero (true), return original bitmask; else return 0
    return (result != 0) ? bitmask : 0;
}