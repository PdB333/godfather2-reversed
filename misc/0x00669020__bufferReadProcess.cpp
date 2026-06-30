// FUNC_NAME: bufferReadProcess

/**
 * Function at 0x00669020
 * Allocates a 256-byte buffer (4 * 0x40), initializes a 3-field structure (size=0, capacity=0x40, unknown=0),
 * then passes input parameters and the structure to FUN_00668ce0. If successful, calls FUN_00668850 with the structure and param_3.
 * Finally calls FUN_00665b40 (likely cleanup) and returns result.
 * Returns -2 on allocation failure.
 * This appears to be a small helper for reading/processing data through a temporary buffer.
 */
int __cdecl bufferReadProcess(void *input1, void *input2, void *input3)
{
    struct ReadBufferDesc {
        int currentSize;   // +0x00: current data size
        int capacity;      // +0x04: buffer capacity (0x40 = 64?)
        int flags;         // +0x08: flags/offset
    };

    // Allocate 4 elements of 0x40 bytes each = 256 bytes
    void *buffer = _calloc(4, 0x40);
    if (buffer == NULL) {
        return -2;
    }

    // Initialize the descriptor
    ReadBufferDesc desc;
    desc.currentSize = 0;
    desc.capacity = 0x40;  // 64 bytes per element? or buffer size?
    desc.flags = 0;

    // Step 1: read data into buffer via input1, input2
    int result = FUN_00668ce0(input1, input2, &desc);
    if (result == 0) {
        // Step 2: process the buffer with param_3
        result = FUN_00668850(&desc, input3);
    }

    // Cleanup
    FUN_00665b40();
    return result;
}