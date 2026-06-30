// FUNC_NAME: BaseObject::queryInterface
bool __thiscall BaseObject::queryInterface(uint32_t interfaceHash, int* outPtr) {
    // This function checks if the object supports a given interface identified by a 32-bit hash.
    // If supported, sets *outPtr to the this pointer and returns true.
    // Otherwise, sets *outPtr to 0 and returns false (except for specific hashes where it still sets *outPtr).
    if (interfaceHash == 0x55645e11) {
        *outPtr = (int)this;
        return true;
    }
    *outPtr = 0;
    if (interfaceHash < 0xae986324) {
        // Check for two specific lower hashes
        if ((interfaceHash != 0xae986323) && (interfaceHash != 0x197c1972)) {
            // Check for another hash
            if (interfaceHash == 0x38523fc3) {
                *outPtr = (int)this;
                return true;
            }
            return false;
        }
        // Fall through for 0xae986323 and 0x197c1972, they will set outPtr below
    } else {
        // Check for a high-range hash
        if (interfaceHash == 0xf8b45dfb) {
            *outPtr = (int)this;
            return true;
        }
        // If not matched, return false (outPtr already 0)
        return false;
    }
    // For the two hashes that fell through (0xae986323 and 0x197c1972), set outPtr
    *outPtr = (int)this;
    return true;
}