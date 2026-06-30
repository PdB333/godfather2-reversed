// FUNC_NAME: parsePacketFromStream
// Function at 0x006423c0: Parses an incoming packet stream, handling marker characters '@', '=', and 0x1b (binary string).
// Parameters:
//   unused (ECX) - unused, likely a remnant of __fastcall
//   stream (EDX) - pointer to a StreamBuffer structure (char* data at +0x10)
//   packetType - packet type identifier (passed to handler)
//   someFlags - additional flags (passed to handler)

struct StreamBuffer {
    char unknown[0x10]; // padding up to +0x10
    char* data; // +0x10: current read position in buffer
};

// Forward declarations for subroutines
void flushStreamBuffer(void); // 0x006421b0: resets/clears stream internal state
void handlePacket(int* packetType, int zero); // 0x00642070: dispatches packet to registered handler

void __fastcall parsePacketFromStream(void* unused, StreamBuffer* stream, int packetType, int someFlags)
{
    char* dataPos = stream->data;
    char firstChar = *dataPos;

    // Handle packet type markers
    if (firstChar == '@' || firstChar == '=') {
        dataPos++;               // Skip the marker character
    }
    else if (firstChar == 0x1b) { // Escape character -> binary string packet
        dataPos = "binary string"; // Fixed string placeholder (likely replaced by actual binary data in real code)
    }

    // Copy packetType and someFlags to local stack (for handler)
    int localPacketType = packetType;
    int localFlags = someFlags;
    // Note: original local_10 was stream pointer (unused after initialization)

    flushStreamBuffer();                // Prepare stream for next packet
    handlePacket(&localPacketType, 0);  // Process the packet with its type information
}