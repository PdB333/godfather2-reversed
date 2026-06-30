// FUNC_NAME: TNLConnection::buildDataPacket
// Address: 0x00627b40
// Role: Writes a data packet header (type 4) into the send buffer, with debug logging and overflow check.

#include <cstdint>

// ---- Forward declarations of helper functions (from known patterns) ----
extern bool isDebugLoggingEnabled();                           // FUN_00632b70
extern void getDebugFileLine(char* outFile, int& outLine);     // FUN_00632fb0
extern int  debugPrintf(const char* fmt, ...);                 // FUN_00625d40
extern void handleSendBufferFull();                            // FUN_00627360
extern uint32_t getNextSequenceNumber();                       // FUN_00638920

// Packet window structure (offset from this+0x10)
struct PacketWindow {
    // ... other fields ...
    uint32_t mSendBufferLimit;  // +0x20  (e.g., capacity)
    uint32_t mSendBufferCount;  // +0x24  (e.g., current usage)
};

class TNLConnection {
public:
    // Offset 0x08: pointer to current write position in the send buffer
    uint32_t* mSendBufferWritePtr; 

    // Offset 0x10: pointer to PacketWindow for tracking send buffer state
    PacketWindow* mPacketWindow;

    void __thiscall buildDataPacket();
};

void __thiscall TNLConnection::buildDataPacket() {
    // Debug logging macro expansion
    if (isDebugLoggingEnabled()) {
        char file[68];
        int line;
        getDebugFileLine(file, line);
        if (line > 0) {
            debugPrintf("%s:%d: ", file, line);
            return;   // Debug builds often skip the actual packet write
        }
    }

    // Check if the send buffer is full
    PacketWindow* win = mPacketWindow;
    if (win->mSendBufferLimit <= win->mSendBufferCount) {
        handleSendBufferFull();   // flush or expand buffer
    }

    // Write packet header: type 4 followed by a sequence number
    uint32_t* writePtr = mSendBufferWritePtr;
    *writePtr = 4;                              // packet type identifier
    writePtr[1] = getNextSequenceNumber();       // e.g., timestamp or sequence

    // Advance write pointer by 8 bytes (two uint32_t)
    mSendBufferWritePtr = writePtr + 2;
}