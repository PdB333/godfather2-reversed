// Address: 0x006fd5a0
// Role: Processes incoming network packets, validates packet header, handles decryption, and dispatches to handler based on connection state
// Note: Global @DAT_0112a9f4 is likely a pointer to a singleton NetSession or NetworkManager instance

// Structure representing a connection slot (size 0x58)
struct ConnectionSlot {
    int state;       // +0x00 (0=Uninitialized, 1=Connected, 6=??)
    // ... other members up to 0x58
};

// External global pointer to network manager singleton
extern uint g_networkManager; // DAT_0112a9f4

// External function: decrypt/validate packet (const uint key, int** pPacket, uint* pSize)
// Returns 1 on success, 0 on failure
extern bool __stdcall FUN_006a8be0(uint key, int** pPacket, uint* pSize);

// External function: process the decrypted/validated packet data
// Returns result code (0 = fail, non-zero = success)
extern uint __thiscall FUN_006fcd00(int* packet, uint packetSize);

// ---------- Reconstructed function ----------

uint __thiscall NetSession::processIncomingPacket(uint bufferSize, int* packetBuffer, uint packetSize)
{
    // Return early if no packet buffer is provided
    if (packetBuffer == nullptr) {
        return 0;
    }

    uint currentSize = packetSize;
    uint outputSize = bufferSize; // output size will be updated by decrypt function if needed

    // Check for known packet header magic (0xCAE87632) and version (1)
    // Only attempt decryption if packet is large enough to contain a header
    if ((packetSize > 0xF) && 
        (packetBuffer[0] == 0xCAE87632) && 
        (packetBuffer[1] == 1))
    {
        int* decryptedPacket = packetBuffer;
        uint newSize = outputSize; // capacity for decrypted data

        // Attempt to decrypt/validate the packet (key = 0x30b00adf)
        if (!FUN_006a8be0(0x30b00adf, &decryptedPacket, &newSize)) {
            return 0; // decryption failed
        }

        // Update pointers and sizes to use the decrypted data
        packetBuffer = decryptedPacket;
        currentSize = newSize;
    }

    // If we still have a valid packet after decryption, check if we are in a suitable connection state
    if (packetBuffer != nullptr) {
        // Offset 0x208 in the global network manager is the current connection index
        int connectionIndex = *(int*)(g_networkManager + 0x208);
        if (connectionIndex != -1) {
            // Offset 0x78 in the global is the start of an array of ConnectionSlot structures (each 0x58 bytes)
            ConnectionSlot* slot = (ConnectionSlot*)(g_networkManager + 0x78 + connectionIndex * 0x58);
            if (slot != nullptr) {
                // Only allow packet processing if connection state is 0, 1, or 6
                int state = slot->state; // +0x00
                if (state == 0 || state == 1 || state == 6) {
                    // Pass the decrypted packet to the actual handler
                    return FUN_006fcd00(packetBuffer, currentSize);
                }
            }
        }
    }

    // Packet rejected (no buffer, wrong state, etc.)
    return 0;
}