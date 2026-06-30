// FUNC_NAME: htonl
// Function at 0x005bff00: Converts a 32-bit integer to big-endian byte order (network byte order) and returns a pointer to a static buffer containing the 4 bytes followed by a null terminator.
// Used for network packet serialization in TNL networking layer.

static char s_networkByteBuffer[5]; // +0x00: buffer for big-endian representation

char* htonl(unsigned int value)
{
    // Store bytes in big-endian order: most significant byte first
    s_networkByteBuffer[0] = (char)(value >> 24); // MSB
    s_networkByteBuffer[1] = (char)(value >> 16);
    s_networkByteBuffer[2] = (char)(value >> 8);
    s_networkByteBuffer[3] = (char)(value);       // LSB
    s_networkByteBuffer[4] = 0;                   // Null terminator (unused but present)

    return s_networkByteBuffer;
}