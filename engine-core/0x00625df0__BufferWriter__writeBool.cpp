// FUNC_NAME: BufferWriter::writeBool
// Address: 0x00625df0
// Writes a bool value with a type tag (1) into a sequential buffer.
// The buffer pointer is stored at offset +0x08 in the object.
void __thiscall BufferWriter::writeBool(int this, int value) {
    // Get current write pointer from object at offset +0x08
    int* bufferPtr = *(int**)(this + 8);
    // Write type tag for bool (1)
    *bufferPtr = 1;
    // Write bool value (0 or 1)
    bufferPtr[1] = (value != 0) ? 1 : 0;
    // Advance write pointer by 8 bytes (two ints)
    *(int**)(this + 8) = bufferPtr + 2;
}