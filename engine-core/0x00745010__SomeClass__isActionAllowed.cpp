// FUNC_NAME: SomeClass::isActionAllowed
bool SomeClass::isActionAllowed() {
    // Get pointer to sub-object at offset +0x68
    SubObject* subObj = *reinterpret_cast<SubObject**>(reinterpret_cast<uint8_t*>(this) + 0x68);
    
    if (subObj != nullptr) {
        // Check global condition via static function
        if (isGlobalConditionMet()) {
            // Read flags word at subObject +0x78
            uint16 flags = *reinterpret_cast<uint16*>(reinterpret_cast<uint8_t*>(subObj) + 0x78);
            // Extract low byte of flags - bits 4 and 6 are relevant
            uint8 flagsLow = static_cast<uint8>(flags & 0xFF);
            // Bit 4 must be clear (0) and bit 6 must be set (1)
            if (((flagsLow >> 4) & 1) == 0 && ((flagsLow >> 6) & 1) != 0) {
                return true;
            }
        }
    }
    return false;
}