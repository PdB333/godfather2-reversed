// FUNC_NAME: ByteBuffer::writeByte
void ByteBuffer::writeByte(char value) {
    if (state < 2) {               // +0x08: state (0=empty,1=initialized,2=full?)
        if (buffer != nullptr) {   // +0x00: buffer pointer
            // Call cleanup/destructor for old buffer
            (bufferDestructor)(buffer); // +0x0C: function pointer
        }
        buffer = FUN_009c8e50(2);  // Allocate buffer of size 2
        state = 1;                  // Mark as initialized
        bufferDestructor = thunk_FUN_009c8eb0; // Set destructor
    }
    buffer[0] = value;              // Write the byte at offset 0
    buffer[1] = 0;                  // Null-terminate? (or second byte = 0)
    count = 1;                      // +0x04: number of bytes written (set to 1)
}