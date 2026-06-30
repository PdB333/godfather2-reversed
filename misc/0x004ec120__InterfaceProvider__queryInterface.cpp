// FUNC_NAME: InterfaceProvider::queryInterface
// Function at 0x004ec120: Interface query/dispatch function for EARS object system.
// Checks a requestID against known interface IDs (0x6b583526, 0x3eb08af9, 0xFFD2E5B1),
// retrieves an interface pointer (via direct cast or delegation to an inner object's vtable),
// and optionally writes it to *outPtr. Returns 1 (true) on success, 0 on failure or unrecognized ID.

__thiscall int InterfaceProvider::queryInterface(int this, int requestID, int* outPtr) {
    // 0x6b583526: likely "self" or base interface – return this pointer directly
    if (requestID == 0x6b583526) {
        if (outPtr != nullptr) {
            *outPtr = this;
            return 1; // success
        }
        // Even if outPtr is null, function still returns 1 (but no write)
        // Fall through to return 1 below
    }
    else {
        // 0x3eb08af9: delegate to inner object's vtable (offset 8) if inner object exists
        if (requestID == 0x3eb08af9) {
            int* innerObj = *(int**)(this + 0x20); // +0x20: pointer to inner interface/provider object
            if (innerObj != nullptr) {
                // Call function at vtable+8 for that inner object
                // WARNING: indirect jump assumed; returns int
                int result = (*(code**)(*innerObj + 8))();
                return result;
            }
        }
        else {
            // If outPtr is provided, zero it (clear output)
            if (outPtr != nullptr) {
                *outPtr = 0;
            }
            // Check for third known interface ID (0xFFD2E5B1, signed -0x2d1a4f)
            if (requestID != (int)0xFFD2E5B1) {
                return 0; // unrecognized ID
            }
            // 0xFFD2E5B1: another self/interface – return this pointer
            if (outPtr != nullptr) {
                *outPtr = this;
            }
            // Fall through to return 1 below
        }
    }
    return 1; // success (for recognized non-delegated IDs)
}