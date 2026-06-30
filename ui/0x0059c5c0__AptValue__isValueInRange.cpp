// FUNC_NAME: AptValue::isValueInRange
// Address: 0x0059c5c0
// This method checks if the object's type field (first uint, lower 15 bits) is in range [12,19]
// and if an additional bit (bit15) or an external flag allows it.
bool AptValue::isValueInRange(char includeFlag) {
    // If this is null, run EA internal assertion (debug check)
    if (this == nullptr) {
        // Assertion code from _AptValue.h line 0x1d2
        if (gAssertEnabled) {
            // Call debug output and possibly break
            // ...
        }
    }

    // Extract lower 15 bits (type ID) from the first field
    uint32_t type = this->typeField & 0x7FFF;

    // Check if type is in [12,19] and either includeFlag is set or bit15 of typeField is set
    if (type > 0xB && type < 0x14 && (includeFlag != '\0' || ((this->typeField >> 15) & 1) != 0)) {
        return true;
    }
    return false;
}