// FUNC_NAME: PacketStream::readPacketType
// Function address: 0x006761b0
// Reads a 10‑byte packet header from the stream and determines the type.
// Returns 1 if it is a data packet ("ttcf" or "true"), 0 otherwise.
// For handshake/disconnect types ("OTTO" or null with subtype 1/2) it performs connection cleanup.

struct PacketStream {
    uint8_t* m_bufferData;      // +0x00
    int32_t  m_readPosition;    // +0x04
    int32_t  m_packetStart;     // +0x0C (offset of current packet in the buffer)
};

// Forward declarations of helper functions (unknown names, given descriptive placeholders)
int   allocatePacketBuffer(uint8_t* out);          // FUN_00672e60
void* getPacketPool();                             // FUN_00673070
void  initializePacket();                          // FUN_00675350
void  deallocateMemory(void* ptr);                 // DAT_01206694 (likely operator delete)
void  resetPool();                                 // FUN_00672fd0

int __thiscall PacketStream::readPacketType()
{
    int      packetStart = m_packetStart;          // unaff_ESI[3]
    uint32_t* header = (uint32_t*)(m_bufferData + packetStart);
    m_readPosition = packetStart;                  // unaff_ESI[1] = iVar4

    uint32_t firstWord  = *header;                 // first 4 bytes (little-endian)
    uint32_t secondWord = header[1];               // next 4 bytes
    uint16_t thirdWord  = *(uint16_t*)(header + 2);// last  2 bytes

    // Extract individual bytes from first word for type checking
    uint8_t b0 = (uint8_t) firstWord;
    uint8_t b1 = (uint8_t)(firstWord >> 8);
    uint8_t b2 = (uint8_t)(firstWord >> 16);
    uint8_t b3 = (uint8_t)(firstWord >> 24);

    // Claim 10 bytes (header length)
    m_readPosition = packetStart + 10;

    // ---- Determine packet type ----
    if (b0 == '\0')
    {
        // Disconnect type: second byte must be 1 or 2, third and fourth zero
        if (((b1 != 1) && (b1 != 2)) || (b2 != 0))
            goto unhandled;
        if (b3 != 0)
            goto unhandled;

        // Rewind for cleanup
        m_readPosition = packetStart;

        // Trigger connection/disconnect cleanup
        {
            uint8_t  local_10[4];  // temporary buffer, uninitialized
            int      iVar4 = allocatePacketBuffer(local_10);
            void*    puVar3 = getPacketPool();
            *(uint32_t*)puVar3 = 0;
            initializePacket();

            // Decrement a reference/use count
            *(uint32_t*)(*(uint32_t*)(iVar4 + 0xC) + ((int32_t*)puVar3)[-2] * 4) = 0;
            *(int32_t*)(iVar4 + 4) = *(int32_t*)(iVar4 + 4) - 1;

            deallocateMemory((uint8_t*)puVar3 - 4);
            resetPool();
            deallocateMemory(*(void**)(iVar4 + 0xC));
            deallocateMemory((void*)iVar4);
        }

        // Fall through to the common code below (will hit the 't' check,
        // but b0 is '\0', so it will go to unhandled)
    }
    else if (b0 == 'O')
    {
        // Handshake "OTTO" type
        if ((b1 != 'T') || (b2 != 'T'))
            goto unhandled;
        if (b3 != 'O')
            goto unhandled;

        // Same cleanup as disconnect
        m_readPosition = packetStart;

        {
            uint8_t  local_10[4];
            int      iVar4 = allocatePacketBuffer(local_10);
            void*    puVar3 = getPacketPool();
            *(uint32_t*)puVar3 = 0;
            initializePacket();

            *(uint32_t*)(*(uint32_t*)(iVar4 + 0xC) + ((int32_t*)puVar3)[-2] * 4) = 0;
            *(int32_t*)(iVar4 + 4) = *(int32_t*)(iVar4 + 4) - 1;

            deallocateMemory((uint8_t*)puVar3 - 4);
            resetPool();
            deallocateMemory(*(void**)(iVar4 + 0xC));
            deallocateMemory((void*)iVar4);
        }
    }

    // Re‑read the first word?  (In original: local_c = uVar1; then check cVar2)
    // The original decompilation resets this before the final test.
    // b0 is still the original first byte, so we just use it directly.
    if (b0 == 't')
    {
        // Check for "ttcf" or "true" data packets
        if (b1 == 't')
        {
            if ((b2 == 'c') && (b3 == 'f'))
            {
                // Valid "ttcf" packet
                m_readPosition = packetStart;   // rewind to packet start (peek only)
                return 1;
            }
        }
        else if ((b1 == 'r') && (b2 == 'u') && (b3 == 'e'))
        {
            // Valid "true" packet
            m_readPosition = packetStart;       // rewind to packet start (peek only)
            return 1;
        }
    }

unhandled:
    m_readPosition = packetStart;   // rewind for any non‑matching type
    return 0;
}