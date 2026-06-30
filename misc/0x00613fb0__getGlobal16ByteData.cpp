// FUNC_NAME: getGlobal16ByteData
// Address: 0x00613fb0
// Copies 16 bytes from a global constant at 0x011f6b50 into the provided buffer.
// This appears to be a helper to retrieve a fixed data structure (e.g., a vector or quaternion).
void getGlobal16ByteData(uint32_t* outBuffer)
{
    outBuffer[0] = *(uint32_t*)0x011f6b50; // +0x00
    outBuffer[1] = *(uint32_t*)0x011f6b54; // +0x04
    outBuffer[2] = *(uint32_t*)0x011f6b58; // +0x08
    outBuffer[3] = *(uint32_t*)0x011f6b5c; // +0x0C
}