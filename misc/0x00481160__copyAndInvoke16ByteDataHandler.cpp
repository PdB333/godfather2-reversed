// FUNC_NAME: copyAndInvoke16ByteDataHandler
// Address: 0x00481160
// Copies a 16-byte data block from the input pointer to a local stack copy, then calls a handler function on the copy.
// This pattern suggests a safe invocation that avoids aliasing issues or allows modification of a temporary.

#include <cstdint>

// Forward declaration of the actual handler function at 0x00609090
void handle16ByteData(uint64_t data[2]);

void copyAndInvoke16ByteDataHandler(uint64_t* input) {
    uint64_t localCopy[2];          // local copy of the 16-byte input
    localCopy[0] = input[0];        // copy first 8 bytes
    localCopy[1] = input[1];        // copy second 8 bytes
    handle16ByteData(localCopy);    // invoke the real processing function
}