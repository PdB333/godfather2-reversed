// FUNC_NAME: EARSObject::getConditionalValue
// Address: 0x00504320
// Role: Returns a value from an internal method only if the flag is non-zero, otherwise 0. Used for conditional access.

int EARSObject::getConditionalValue(int flag) {
    if (flag != 0) {
        return getInternalValue(); // internal method at 0x00505720
    }
    return 0;
}