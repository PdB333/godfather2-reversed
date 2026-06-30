// FUNC_NAME: EARSObject::checkFlags
uint EARSObject::checkFlags(uint flagMask) {
    uint dummy = 0;                              // placeholder for optional output
    // Virtual call at vtable offset 0x10 (index 4): bool testFlag(uint mask, uint* outValue)
    char result = this->testFlag(flagMask, &dummy);
    // Return flagMask if flag is set, else 0
    return -(uint)(result != '\0') & flagMask;
}