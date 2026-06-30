// FUNC_NAME: SystemInitializer::initializeWithFlags
// Function address: 0x006669a0
// Role: Initializes a system with a bitmask of flags, processing each set bit (bits 27-0) by calling a handler.
// The this pointer (in_EAX) points to a structure with fields:
//   +0x00: uint field0 (initialized to 0, then set to 1 if buffer at +0x0C is non-zero)
//   +0x04: uint bufferSize (number of uint32 elements in buffer at +0x0C)
//   +0x08: uint field8 (set to 0)
//   +0x0C: uint* buffer (pointer to a buffer of bufferSize uint32s, first element set to 1)

int SystemInitializer::initializeWithFlags(uint flags)
{
    void* tempBuffer;
    int result;
    int iteration;

    // Allocate a temporary buffer of 0x100 bytes (4 * 0x40)
    tempBuffer = _calloc(4, 0x40);
    iteration = 0;
    if (tempBuffer == nullptr) {
        return -2;
    }

    // Call an initialization function (likely creates the internal structure)
    result = FUN_00665ce0();
    if (result == 0) {
        // Initialize the this object's fields
        this->field8 = 0;          // +0x08
        this->field0 = 0;          // +0x00
        _memset(this->buffer, 0, this->bufferSize * 4); // +0x0C, +0x04
        *(uint32_t*)this->buffer = 1; // Set first element to 1
        this->field0 = (uint32_t)(*(int32_t*)this->buffer != 0); // field0 becomes 1

        // Loop over bits 27 down to 0 of the flags parameter
        do {
            // Call a yield/cancel check function
            result = FUN_0066a660();
            if (result != 0) {
                if (tempBuffer != nullptr) {
                    _memset(tempBuffer, 0, 0); // Note: size 0 is likely a decompilation artifact
                    _free(tempBuffer);
                }
                return result;
            }

            // If the current bit (position 27) of flags is set, process it
            if ((flags & 0x8000000) != 0) {
                result = FUN_00668ce0(); // Process this flag
                if (result != 0) {
                    FUN_00665b40(); // Cleanup on error
                    return result;
                }
            }

            iteration++;
            flags = flags * 2; // Shift left to check next lower bit next iteration
        } while (iteration < 28); // Check all 28 bits (0x1C)

        // Free the temporary buffer
        if (tempBuffer != nullptr) {
            _memset(tempBuffer, 0, 0);
            _free(tempBuffer);
        }
        result = 0;
    }
    return result;
}