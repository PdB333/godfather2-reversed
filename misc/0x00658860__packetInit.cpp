// FUNC_NAME: packetInit
// Function at 0x00658860
// Initializes a packet structure with zeros and sets a field, increments a global sequence counter.
// Seems to be a utility for preparing a network packet (calls htonl for byte ordering but with 0).
void packetInit(void* pPacket, uint32_t param) {
    // Static global sequence counter (incremented each packet)
    static uint32_t g_packetSequenceCounter = 0;
    g_packetSequenceCounter++;

    // pPacket is assumed to point to a structure of at least 20 bytes
    // Offsets are in bytes (since unaff_ESI is undefined2*, multiply by 2):
    // +0: short (2 bytes)
    // +2: short (2 bytes)
    // +4: dword (4 bytes) -> set to param
    // +8: dword (4 bytes) -> zeroed
    // +12: dword (4 bytes) -> zeroed
    // +16: dword (4 bytes) -> zeroed
    short* pShort = (short*)pPacket;
    uint32_t* pDword = (uint32_t*)pPacket;

    pShort[0] = 0;                 // offset 0
    pShort[1] = 0;                 // offset 2
    pDword[2] = 0;                 // offset 8? Actually offset 8 in byte units: pDword[2] = offset 8
    pDword[3] = 0;                 // offset 12
    pDword[1] = 0;                 // offset 4 (cleared before assignment below? wait, order in original: set after htonl)
    // The original code calls htonl(0) – presumably a no-op, maybe for alignment or debug
    htonl(0);
    pDword[1] = param;             // offset 4: set to param (overwrites the zero)
}