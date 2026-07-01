// FUNC_NAME: UnknownClass::validateData
// Function address: 0x007d3890
// Validates that data pointer and size are non-zero, then runs two checks (FUN_00883670 and FUN_00883720).
// Returns true only if both checks return 0 (no error), otherwise false.
bool UnknownClass::validateData(void* thisPointer, void* data, int size) {
    if (size == 0) {
        return false;
    }
    if (data != nullptr) {
        if (!FUN_00883670(thisPointer, data, size)) {
            if (!FUN_00883720(thisPointer, data, size)) {
                return true;
            }
        }
        return false;
    }
    return false;
}